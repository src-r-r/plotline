#include "plotline.h"

Plotline::Plotline(const QString &synopsis,
                   const QList<Scene> &scenes,
                   const QList<Character> &characters,
                   const QColor &color,
                   QObject *parent)
    : QObject(parent)
{
    this->mSynopsis = synopsis;
    this->mColor = color;
    this->mScenes = scenes;
    this->mCharacters = characters;
}


QColor Plotline::getColor() const
{
    return mColor;
}

void Plotline::setColor(const QColor &color)
{
    this->mColor = color;
}

QString Plotline::getSynopsis() const
{
    return mSynopsis;
}

void Plotline::setSynopsis(const QString &synopsis)
{
    this->mSynopsis = synopsis;
}

QList<Character> Plotline::getCharacters() const
{
    return mCharacters;
}

void Plotline::setCharacters(const QList<Character> &characters)
{
    this->mCharacters = characters;
}

QList<Scene> Plotline::getScenes() const
{
    return this->mScenes;
}

void Plotline::setScenes(const QList<Scene> &scenes)
{
    mScenes = scenes;
}
