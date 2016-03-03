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
    QString content;
    if (!mRevisions.empty())
        content = mRevisions.last()->content();
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

void Chapter::setContent(const QString &content, const int revision)
{
    int n = revision < 0 ? currentRevision() : revision;
    mRevisions[n]->setContent(content);
}

void Chapter::setIsComplete(const bool complete, const int revision)
{
    if(revision == -1)
        mRevisions[currentRevision()]->setIsComplete(complete);
    mRevisions[revision]->setIsComplete(complete);
}

/**
 * @brief Chapter::canMarkCompleted
 * Can a revision be marked as completed? true if either the previous revision
 * was marked as completed or this is the first revision.
 * @param revision Revision number, or -1 for the current revision.
 * @return true if the revision can be marked, false otherwise.
 */
bool Chapter::canMarkCompleted(const int revision) const
{
    int r = revision < 0 ? currentRevision() : revision;
    return (r == 0 || revisions()[r-1]->isComplete());
}

Chapter::Chapter(const QString &title, const QList<Revision *> &revisions,
                 const QList<Scene *> &scenes,
                 Novel *novel,
                 int currentRevision,
                 QUuid id,
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
        jScenes.append(s->id().toString());

    for (Revision *r : mRevisions)
        jRevisions.append(QJsonValue(r->serialize()));

    chapter[JSON_ID] = QJsonValue(id().toString());
    chapter[JSON_TITLE] = mTitle;
    chapter[JSON_SCENES] = jScenes;
    chapter[JSON_REVISIONS] = jRevisions;
    chapter[JSON_CURRENT_REVISION] = QJsonValue(mCurrentRevision);

    return chapter;
}

Chapter *Chapter::deserialize(Novel *novel, const QJsonObject &object)
{
    QUuid id = Serializable::deserialize(object);

    QString title = QString();
    QList<Revision *> revisions = QList<Revision *>();
    QList<Scene *> scenes = QList<Scene *>();
    int currentRevision = 0;

    if (object.contains(JSON_TITLE))
        title = object[JSON_TITLE].toString();
    if (object.contains(JSON_REVISIONS))
        revisions = Revision::deserialize(novel, 0,
                                          object[JSON_REVISIONS].toArray());
    if (object.contains(JSON_SCENES)){
        QJsonArray sceneIds = object[JSON_SCENES].toArray();
        for (QJsonValue sceneId : sceneIds){
            QUuid id2 = sceneId.toVariant().toUuid();
            Scene *scene = novel->scene(id2);
            if (!scene)
                qWarning() << "[#] deserialize chapter: no scene " << id2;
            else
                scenes.append(scene);
        }
    }

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
