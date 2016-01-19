#include "novel.h"


Novel::Novel(const QString &workingTitle,
             const QString &genre,
             const QString &setting,
             const Novel::Tense tense,
             const Novel::PointOfView pov,
             QObject *parent)
    : QObject(parent)
{
    this->workingTitle = workingTitle;
    this->genre = genre;
    this->mTense = tense;
    this->setting = setting;
    this->mPointOfView = pov;
}

QString Novel::getWorkingTitle() const
{
    return workingTitle;
}

void Novel::setWorkingTitle(const QString &value)
{
    workingTitle = value;
}

QString Novel::getGenre() const
{
    return genre;
}

void Novel::setGenre(const QString &value)
{
    genre = value;
}

Novel::Tense Novel::getTense() const
{
    return mTense;
}

void Novel::setTense(const Novel::Tense value)
{
    mTense = value;
}

QString Novel::getSetting() const
{
    return setting;
}

void Novel::setSetting(const QString &value)
{
    setting = value;
}

QList<Scene> Novel::getScenes() const
{
    return scenes;
}

void Novel::setScenes(const QList<Scene> &value)
{
    scenes = value;
}

QList<Chapter> Novel::getChapters() const
{
    return chapters;
}

void Novel::setChapters(const QList<Chapter> &value)
{
    chapters = value;
}

Novel::PointOfView Novel::getPointOfView() const
{
    return mPointOfView;
}

void Novel::setPointOfView(const Novel::PointOfView &pointOfView)
{
    mPointOfView = pointOfView;
}

Novel::Novel(const Novel &novel) : QObject(novel.parent())
{
    this->workingTitle = novel.workingTitle;
    this->genre = novel.genre;
    this->mTense = novel.mTense;
    this->mPointOfView = novel.mPointOfView;
    this->scenes = novel.scenes;
    this->chapters = novel.chapters;
}
