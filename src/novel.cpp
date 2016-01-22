#include "novel.h"

const QString Novel::JSON_WORKING_TITLE = QString("workingTitle"),
    Novel::JSON_GENRE = QString("genre"),
    Novel::JSON_SETTING = QString("setting"),
    Novel::JSON_TENSE = QString("tense"),
    Novel::JSON_POV = QString("pointOfView"),
    Novel::JSON_SCENES = QString("scenes"),
    Novel::JSON_CHARACTERS = QString("characters"),
    Novel::JSON_CHAPTERS = QString("chapters"),
    Novel::JSON_PLOTLINES = QString("plotlines");

Novel::Novel(const QString &workingTitle,
             const QString &genre,
             const QString &setting,
             const Novel::Tense tense,
             const Novel::PointOfView pov,
             const QList<Character *> characters,
             const QList<Scene *> scenes,
             const QList<Chapter *> chapters,
             const QList<Plotline *> plotlines,
             int id,
             QObject *parent)
    : QObject(parent), Serializable(id)
{
    this->mWorkingTitle = workingTitle;
    this->mGenre = genre;
    this->mTense = tense;
    this->mSetting = setting;
    this->mPointOfView = pov;
    this->mCharacters = characters;
    this->mScenes = scenes;
    this->mChapters = chapters;
    this->mPlotlines = plotlines;
}

QString Novel::getWorkingTitle() const
{
    return mWorkingTitle;
}

void Novel::setWorkingTitle(const QString &value)
{
    mWorkingTitle = value;
}

QString Novel::getGenre() const
{
    return mGenre;
}

void Novel::setGenre(const QString &value)
{
    mGenre = value;
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
    return mSetting;
}

void Novel::setSetting(const QString &value)
{
    mSetting = value;
}

QList<Scene *> Novel::getScenes() const
{
    return mScenes;
}

Scene *Novel::getScene(int id) const
{
    for (Scene *s : mScenes)
        if (s->getId() == id)
            return s;
    return 0;
}

void Novel::setScenes(const QList<Scene *> &value)
{
    mScenes = value;
}

QList<Chapter *> Novel::getChapters() const
{
    return mChapters;
}

void Novel::setChapters(const QList<Chapter *> &value)
{
    mChapters = value;
}

Novel::PointOfView Novel::getPointOfView() const
{
    return mPointOfView;
}

void Novel::setPointOfView(const Novel::PointOfView &pointOfView)
{
    mPointOfView = pointOfView;
}

QList<Plotline *> Novel::getPlotlines() const
{
    return mPlotlines;
}

void Novel::setPlotlines(const QList<Plotline *> &plotlines)
{
    mPlotlines = plotlines;
}

QList<Character *> Novel::getCharacters() const
{
    return mCharacters;
}

/**
 * @brief Novel::getCharacter
 * Get a character based on a character ID
 * @param id the character ID
 * @return The character whose ID is id, or NULL if not found.
 */
Character *Novel::getCharacter(int id) const
{
    for (Character *c : mCharacters)
        if (c->getId() == id)
            return c;
    return 0;
}

/**
 * @brief Novel::getCharacter
 * Find a character based on a character label.
 * @param label The label for the character (e.g. "JoDo")
 * @return The character found, or 0 if no character is found.
 */
Character *Novel::getCharacter(const QString label) const
{
    for (Character *c : mCharacters)
        if (c->getLabel() == label)
            return c;
    return 0;
}

void Novel::setCharacters(const QList<Character *> &characters)
{
    mCharacters = characters;
}

QJsonObject Novel::serialize() const
{
    QJsonObject novel = QJsonObject();

    QJsonArray jScenes = QJsonArray(),
            jChapters = QJsonArray(),
            jCharacters = QJsonArray(),
            jPlotlines = QJsonArray();

    for (Scene *s : mScenes)
        jScenes.append(s->serialize());

    for (Chapter *c : mChapters)
        jChapters.append(c->serialize());

    for (Character *a : mCharacters)
        jCharacters.append(a->serialize());

    for (Plotline *p : mPlotlines)
        jPlotlines.append(p->serialize());

    novel[JSON_ID] = QJsonValue(getId());
    novel[JSON_WORKING_TITLE] = mWorkingTitle;
    novel[JSON_SETTING] = mSetting;
    novel[JSON_GENRE] = mGenre;
    novel[JSON_POV] = QJsonValue(mPointOfView);
    novel[JSON_TENSE] = QJsonValue(mTense);
    novel[JSON_CHARACTERS] = jCharacters;
    novel[JSON_SCENES] = jScenes;
    novel[JSON_CHAPTERS] = jChapters;
    novel[JSON_PLOTLINES] = jPlotlines;
    return novel;
}

Novel *Novel::deserialize(const QJsonObject &object)
{

    if (object.isEmpty())
        return 0;

    QString workingTitle = QString(),
            genre = QString(), setting = QString();
    Novel::Tense tense;
    Novel::PointOfView pointOfView;
    QList<Scene *> scenes = QList<Scene *>();
    QList<Chapter *> chapters = QList<Chapter *>();
    QList<Character *> characters = QList<Character *>();
    QList<Plotline *> plotlines = QList<Plotline *>();

    int id = Serializable::deserialize(object);

    QStringList notFound = QStringList();

    if (object.contains(JSON_WORKING_TITLE))
        workingTitle = object[JSON_WORKING_TITLE].toString();
    else
        notFound << JSON_WORKING_TITLE;

    if (object.contains(JSON_GENRE))
        genre = object[JSON_GENRE].toString();
    else
        notFound << JSON_GENRE;

    if (object.contains(JSON_SETTING))
        setting = object[JSON_SETTING].toString();
    else
        notFound << JSON_SETTING;

    if (object.contains(JSON_TENSE))
        tense = (Tense) object[JSON_TENSE].toInt();
    else
        notFound << JSON_TENSE;

    if (object.contains(JSON_POV))
        pointOfView = (PointOfView) object[JSON_POV].toInt();
    else
        notFound << JSON_POV;


    Novel *novel = new Novel(workingTitle, genre, setting, tense,
                             pointOfView);


    if (object.contains(JSON_CHARACTERS))
        characters = Character::deserialize(novel, object[JSON_CHARACTERS].toArray());
    else
        notFound << JSON_CHARACTERS;

    novel->setCharacters(characters);

    if (object.contains(JSON_PLOTLINES))
        plotlines = Plotline::deserialize(novel, object[JSON_PLOTLINES].toArray());
    else
        notFound << JSON_PLOTLINES;
    novel->setPlotlines(plotlines);

    if (object.contains(JSON_SCENES))
        scenes = Scene::deserialize(novel, object[JSON_SCENES].toArray());
    else
        notFound << JSON_SCENES;
    novel->setScenes(scenes);

    if (object.contains(JSON_CHAPTERS))
        chapters = Chapter::deserialize(novel, object[JSON_CHAPTERS].toArray());
    else
        notFound << JSON_CHAPTERS;
    novel->setChapters(chapters);

    if (!notFound.empty()){
        qWarning() << "The following fields could not be found: "
                   << notFound.join(", ");
    }

    novel->setId(id);

    return novel;
}
