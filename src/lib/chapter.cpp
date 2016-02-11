#include "chapter.h"

const QString Chapter::JSON_TITLE = QString("title"),
    Chapter::JSON_REVISIONS = QString("revisions"),
    Chapter::JSON_SCENES = QString("scenes"),
    Chapter::JSON_CURRENT_REVISION = QString("current_revision");

Novel *Chapter::novel() const
{
    return mNovel;
}

void Chapter::setNovel(Novel *novel)
{
    mNovel = novel;
}

QList<Revision *> Chapter::revisions() const
{
    return mRevisions;
}

/**
 * @brief Chapter::addRevision
 * Add a new revision to the chapter, copying over the last revision's content.
 * @return The created revision.
 */
Revision *Chapter::addRevision()
{
    Revision *r = 0;
    QString content = mRevisions.empty() ? QString() :
                                           mRevisions.last()->content();
    r = new Revision(content);
    mRevisions.append(r);
    return r;
}

void Chapter::removeRevision(int i)
{
    mRevisions.removeAt(i);
}

QString Chapter::content(int revision) const
{
    return mRevisions[revision]->content();
}

QString Chapter::currentContent() const
{
    if (mRevisions.empty() || mCurrentRevision < 0
            || mCurrentRevision > mRevisions.count()) return QString();
    return content(mCurrentRevision);
}

QString Chapter::latestContent() const
{
    if (mRevisions.empty()) return QString();
    return content(mRevisions.count()-1);
}

int Chapter::currentRevision() const
{
    return mCurrentRevision;
}

void Chapter::setCurrentRevision(int currentRevision)
{
    qDebug() << "Setting chapter" << novel()->chapters().indexOf(this)
             << "revision:" << currentRevision;
    if (currentRevision > mRevisions.count()){
        qWarning() << "Current revision" << currentRevision
                   << ">" << mRevisions.count();
        mCurrentRevision = mRevisions.count();
    } else {
        mCurrentRevision = currentRevision;
    }
}

Chapter::Chapter(const QString &title, const QList<Revision *> &revisions,
                 const QList<Scene *> &scenes,
                 Novel *novel,
                 int currentRevision,
                 int id,
                 QObject *parent) : QObject(parent), Serializable(id)
{
    mTitle = title;
    mRevisions = revisions;
    if (mRevisions.empty())
        addRevision();
    mNovel = novel;
    mScenes = scenes;
    if (currentRevision < 0)
        mCurrentRevision = mRevisions.count()-1;
    else
        mCurrentRevision = currentRevision;
}

Chapter::~Chapter()
{
    qDeleteAll(mRevisions);
}

QString Chapter::title() const
{
    return mTitle;
}

void Chapter::setTitle(const QString &title)
{
    mTitle = title;
}

QList<Scene *> Chapter::scenes() const
{
    return mScenes;
}

void Chapter::setScenes(const QList<Scene *> &scenes)
{
    mScenes = scenes;
}

QJsonObject Chapter::serialize() const {
    QJsonObject chapter = QJsonObject();

    QJsonArray jScenes = QJsonArray(),
            jRevisions = QJsonArray();

    for (Scene *s : mScenes)
        jScenes.append(s->id());

    for (Revision *r : mRevisions)
        jRevisions.append(QJsonValue(r->serialize()));

    chapter[JSON_ID] = QJsonValue(id());
    chapter[JSON_TITLE] = mTitle;
    chapter[JSON_SCENES] = jScenes;
    chapter[JSON_REVISIONS] = jRevisions;
    chapter[JSON_CURRENT_REVISION] = QJsonValue(mCurrentRevision);

    return chapter;
}

Chapter *Chapter::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QString title = QString();
    QList<Revision *> revisions = QList<Revision *>();
    QList<Scene *> scenes = QList<Scene *>();
    int currentRevision = 0;

    if (object.contains(JSON_TITLE))
        title = object[JSON_TITLE].toString();
    if (object.contains(JSON_REVISIONS))
        revisions = Revision::deserialize(novel, 0,
                                          object[JSON_REVISIONS].toArray());
    if (object.contains(JSON_SCENES))
        scenes = Scene::deserialize(novel, object[JSON_SCENES].toArray());

    if (object.contains(JSON_CURRENT_REVISION))
        currentRevision = object[JSON_CURRENT_REVISION].toInt();

    Chapter *chapter = new Chapter(title, revisions, scenes, novel,
                                   currentRevision, id);
    for (Revision *r : revisions)
        r->setChapter(chapter);

    return chapter;
}

QList<Chapter *> Chapter::deserialize(Novel *novel, const QJsonArray &object)
{

    QList<Chapter *> chapters = QList<Chapter *>();
    for (QJsonValue value : object)
        chapters << Chapter::deserialize(novel, value.toObject());

    return chapters;
}

/**
 * @brief Chapter::number Get the chapter number (1-based).
 * @return The chapter number 1....n
 */
int Chapter::number()
{
    return mNovel->chapters().indexOf(this)+1;
}
