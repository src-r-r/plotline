#include "plotline.h"

const QString Plotline::J_CHARACTERS = "characters",
    Plotline::J_SCENES = "scenes",
    Plotline::J_SYNOPSIS = "synopsis",
    Plotline::J_COLOR = "color";

Plotline::Plotline(const QString &synopsis,
                   const QList<Scene *> &scenes,
                   const QList<Character *> &characters,
                   const QColor &color,
                   Novel *novel,
                   int id,
                   QObject *parent)
    : QObject(parent), Serializable(id)
{
    this->mSynopsis = synopsis;
    this->mColor = color;
    this->mScenes = scenes;
    this->mNovel = novel;
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

QList<Character *> Plotline::getCharacters() const
{
    return mCharacters;
}

void Plotline::setCharacters(const QList<Character *> &characters)
{
    this->mCharacters = characters;
}

QList<Scene *> Plotline::getScenes() const
{
    return this->mScenes;
}

void Plotline::setScenes(const QList<Scene *> &scenes)
{
    mScenes = scenes;
}

Novel *Plotline::getNovel()
{
    return this->mNovel;
}

void Plotline::setNovel(Novel *novel)
{
    this->mNovel = novel;
}

QJsonObject Plotline::serialize() const{
    QJsonObject plotline = QJsonObject();

    return plotline;
}

Plotline *Plotline::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QString synopsis = QString();
    QList<Character *> characters;
    QList<Scene *> scenes;
    QColor color = QColor();

    Plotline *plotline = new Plotline(synopsis, scenes, characters, color,
                                      novel, id);

    return plotline;
}

QList<Plotline *> Plotline::deserialize(Novel *novel, const QJsonArray &object)
{

    QList<Plotline *> plotlines = QList<Plotline *>();

    for (QJsonValue value : object)
        if (value.isObject())
            plotlines.append(Plotline::deserialize(novel, value.toObject()));

    return plotlines;
}
