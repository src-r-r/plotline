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

    novel.insert(JSON_WORKING_TITLE, this->mWorkingTitle);
    novel.insert(JSON_SETTING, this->mSetting);
    novel.insert(JSON_POV, this->mPointOfView);
    novel.insert(JSON_TENSE, this->mTense);

    QJsonArray jScenes = QJsonArray(),
            jChapters = QJsonArray(),
            jCharacters = QJsonArray();

    for (Scene *s : mScenes)
        jScenes.append(s->serialize());

    for (Chapter *c : mChapters)
        jChapters.append(c->serialize());

    for (Character *a : mCharacters)
        jCharacters.append(a->serialize());

    novel.insert(JSON_CHARACTERS, jCharacters);
    novel.insert(JSON_SCENES, jScenes);
    novel.insert(JSON_CHAPTERS, jChapters);
    return novel;
}

Novel *Novel::deserialize(const QJsonObject &object)
{
    QJsonValue vWorkingTitle = object.value(JSON_WORKING_TITLE),
            vGenre = object.value(JSON_GENRE),
            vSetting = object.value(JSON_SETTING),
            vTense = object.value(JSON_TENSE),
            vPov = object.value(JSON_POV),
            vScenes = object.value(JSON_SCENES),
            vCharacters = object.value(JSON_CHARACTERS),
            vChapters = object.value(JSON_CHAPTERS),
            vPlotlines = object.value(JSON_PLOTLINES);

    QString workingTitle = QString(),
            genre = QString(), setting = QString();
    Novel::Tense tense;
    Novel::PointOfView pointOfView;
    QList<Scene *> scenes = QList<Scene *>();
    QList<Chapter *> chapters = QList<Chapter *>();
    QList<Character *> characters = QList<Character *>();
    QList<Plotline *> plotlines = QList<Plotline *>();

    int id = Serializable::deserialize(object);

    if (!vWorkingTitle.isNull() && vWorkingTitle.isString())
        workingTitle = vWorkingTitle.toString();

    if (!vGenre.isNull() && vGenre.isString())
        genre = vGenre.toString();

    if (!vSetting.isNull() && vSetting.isString())
        setting = vSetting.toString();

    if (!vTense.isNull() && vTense.isDouble())
        tense = (Tense) vTense.toInt();

    if (!vPov.isNull() && vPov.isDouble())
        pointOfView = (PointOfView) vPov.toInt();


    Novel *novel = new Novel(workingTitle, genre, setting, tense,
                             pointOfView);

    if (!vScenes.isNull() && vScenes.isArray())
        scenes = Scene::deserialize(novel, vScenes.toArray());

    if (!vChapters.isNull() && vChapters.isArray())
        chapters = Chapter::deserialize(novel, vChapters.toArray());

    if (!vCharacters.isNull() && vCharacters.isArray())
        characters = Character::deserialize(novel, vCharacters.toArray());

    if (!vPlotlines.isNull() && vPlotlines.isArray())
        plotlines = Plotline::deserialize(novel, vPlotlines.toArray());

    novel->setPlotlines(plotlines);
    novel->setScenes(scenes);
    novel->setChapters(chapters);
    novel->setCharacters(characters);
    novel->setId(id);

    return novel;
}
