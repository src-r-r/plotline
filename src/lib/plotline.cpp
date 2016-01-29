#include "plotline.h"

const QString Plotline::J_CHARACTERS = "characters",
    Plotline::J_SCENES = "scenes",
    Plotline::J_SYNOPSIS = "synopsis",
    Plotline::J_BRIEF = "brief",
    Plotline::J_COLOR = "color";

Plotline::Plotline(const QString &brief,
                   const QString &synopsis,
                   const QList<Scene *> &scenes,
                   const QList<Character *> &characters,
                   const QColor &color,
                   Novel *novel,
                   int id,
                   QObject *parent)
    : QObject(parent), Serializable(id)
{
    this->mBrief = brief;
    this->mSynopsis = synopsis;
    this->mColor = color;
    this->mScenes = scenes;
    this->mNovel = novel;
    this->mCharacters = characters;
}


QString Plotline::getBrief() const
{
    return mBrief;
}

void Plotline::setBrief(const QString &brief)
{
    mBrief = brief;
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

void Plotline::addCharacter(Character *character, const int before)
{
    if (before > 0)
        mCharacters.insert(before, character);
    else
        mCharacters.append(character);
}

void Plotline::removeCharacter(Character *character)
{
    this->mCharacters.removeAll(character);
}

void Plotline::removeCharacter(const QString &label)
{
    for (Character *c : mCharacters)
        if (c->getLabel() == label)
            mCharacters.removeAll(c);
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

    QJsonArray jCharacters = QJsonArray();
    for (Character *c : mCharacters)
        jCharacters.append(QJsonValue(c->getId()));

    QJsonArray jScenes = QJsonArray();
    for (Scene *s : mScenes)
        jScenes.append(QJsonValue(s->getId()));

    plotline[J_CHARACTERS] = jCharacters;
    plotline[J_SCENES] = jScenes;
    plotline[J_BRIEF] = mBrief;
    plotline[J_SYNOPSIS] = mSynopsis;
    plotline[J_COLOR] = mColor.name();

    return plotline;
}

Plotline *Plotline::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QString brief = QString(), synopsis = QString();
    QList<Character *> characters;
    QList<Scene *> scenes;
    QColor color = QColor();

    if (object.contains(J_BRIEF))
        brief = object[J_BRIEF].toString();

    if (object.contains(J_SYNOPSIS))
        synopsis = object[J_SYNOPSIS].toString();

    if (object.contains(J_CHARACTERS))
        for (QJsonValue val : object[J_CHARACTERS].toArray())
            characters.append(novel->getCharacter(val.toInt()));

    if (object.contains(J_SCENES))
        for (QJsonValue val : object[J_SCENES].toArray())
            scenes.append(novel->getScene(val.toInt()));

    if (object.contains(J_COLOR))
        color = QColor(object[J_COLOR].toString());

    Plotline *plotline = new Plotline(brief, synopsis, scenes, characters,
                                      color, novel, id);

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
