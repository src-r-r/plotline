#include "chapter.h"

const QString Chapter::JSON_TITLE = QString("title"),
    Chapter::JSON_REVISIONS = QString("revisions"),
    Chapter::JSON_SCENES = QString("scenes");

Novel *Chapter::novel() const
{
    return mNovel;
}

void Chapter::setNovel(Novel *novel)
{
    mNovel = novel;
}

QList<Revision *> Chapter::getRevisions() const
{
    return mRevisions;
}

void Chapter::setRevisions(const QList<Revision *> &revisions)
{
    mRevisions = revisions;
}

Chapter::Chapter(const QString &title, const QList<Revision *> &revisions,
                 const QList<Scene *> &scenes,
                 Novel *novel,
                 int id,
                 QObject *parent) : QObject(parent), Serializable(id)
{
    mTitle = title;
    mRevisions = revisions;
    mNovel = novel;
    mScenes = scenes;
}

QString Chapter::title() const
{
    return mTitle;
}

void Chapter::setTitle(const QString &title)
{
    mTitle = title;
}

QList<Scene *> Chapter::getScenes() const
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
        jScenes.append(s->getId());

    for (Revision *r : mRevisions)
        jRevisions.append(QJsonValue(r->serialize()));

    chapter[JSON_TITLE] = mTitle;
    chapter[JSON_SCENES] = jScenes;
    chapter[JSON_REVISIONS] = jRevisions;

    return chapter;
}

Chapter *Chapter::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QString title = QString();
    QList<Revision *> revisions = QList<Revision *>();
    QList<Scene *> scenes = QList<Scene *>();

    if (object.contains(JSON_TITLE))
        title = object[JSON_TITLE].toString();
    if (object.contains(JSON_REVISIONS))
        revisions = Revision::deserialize(novel, 0,
                                          object[JSON_REVISIONS].toArray());
    if (object.contains(JSON_SCENES))
        scenes = Scene::deserialize(novel, object[JSON_SCENES].toArray());

    Chapter *chapter = new Chapter(title, revisions, scenes, novel, id);
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
