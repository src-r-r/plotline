#include "chapter.h"

Chapter::Chapter(const QString &title, const QString &content,
                 const QList<Scene> &scenes,
                 QObject *parent) : Completable(parent)
{
    mTitle = title;
    mContent = content;
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

QList<Scene> Chapter::getScenes() const
{
    return mScenes;
}

void Chapter::setScenes(const QList<Scene> &scenes)
{
    mScenes = scenes;
}

Chapter::Chapter(const Chapter &c) : Completable(c)
{
    this->mTitle = c.mTitle;
    this->mContent = c.mContent;
    this->mScenes = c.mScenes;
}
