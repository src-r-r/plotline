#include "chapter.h"

const QString Chapter::JSON_TITLE = QString("title"),
    Chapter::JSON_CONTENT = QString("content"),
    Chapter::JSON_SCENES = QString("scenes");

Novel *Chapter::getNovel() const
{
    return mNovel;
}

void Chapter::setNovel(Novel *novel)
{
    mNovel = novel;
}

Chapter::Chapter(const QString &title, const QString &content,
                 const QList<Scene *> &scenes,
                 Novel *novel,
                 int id,
                 QObject *parent) : Completable(parent), Serializable(id)
{
    mTitle = title;
    mContent = content;
    mNovel = novel;
    mScenes = scenes;
}

QString Chapter::getTitle() const
{
    return mTitle;
}

void Chapter::setTitle(const QString &title)
{
    mTitle = title;
}

QString Chapter::getContent() const
{
    return mContent;
}

void Chapter::setContent(const QString &content)
{
    mContent = content;
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

    QJsonArray jScenes = QJsonArray();

    for (Scene *s : mScenes)
        jScenes.append(s->getId());

    chapter.insert(JSON_TITLE, mTitle);
    chapter.insert(JSON_CONTENT, mContent);
    chapter.insert(JSON_SCENES, jScenes);

    return chapter;
}

Chapter *Chapter::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QJsonValue jTitle = object.value(JSON_TITLE),
            jContent = object.value(JSON_CONTENT),
            jScenes = object.value(JSON_SCENES);
    QString title = QString(), content = QString();
    QList<Scene *> scenes = QList<Scene *>();

    if (!jTitle.isNull() && jTitle.isString())
        title = jTitle.toString();

    if (!jContent.isNull() && jContent.isString())
        content = jContent.toString();

    if (!jScenes.isNull() && jScenes.isArray())
        for (QJsonValue jScene : jScenes.toArray())
            if (jScene.toInt() >= 0)
                scenes.append(novel->getScene(jScene.toInt()));

    Chapter *chapter = new Chapter(title, content, scenes, novel, id);
    return chapter;
}

QList<Chapter *> Chapter::deserialize(Novel *novel, const QJsonArray &object)
{

    QList<Chapter *> chapters = QList<Chapter *>();
    for (QJsonValue value : object)
        if (value.isObject())
            chapters.append(Chapter::deserialize(novel, value.toObject()));

    return chapters;
}
