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

Novel::~Novel()
{
    qDeleteAll(mCharacters);
    qDeleteAll(mScenes);
    qDeleteAll(mChapters);
    qDeleteAll(mPlotlines);
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
        if (s->id() == id)
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

QList<Plotline *> Novel::plotlines() const
{
    return mPlotlines;
}

Plotline *Novel::plotline(int id) const
{
    for (Plotline *p : mPlotlines)
        if (p->id() == id)
            return p;
    return 0;
}

void Novel::setPlotlines(const QList<Plotline *> &plotlines)
{
    mPlotlines = plotlines;
}

void Novel::addPlotline(Plotline *plotline, int before)
{
    if (before > 0)
        mPlotlines.insert(before, plotline);
    else
        mPlotlines.append(plotline);
}

QList<Character *> Novel::characters() const
{
    return this->mCharacters;
}

/**
 * @brief Novel::getCharacter
 * Get a character based on a character ID
 * @param id the character ID
 * @return The character whose ID is id, or NULL if not found.
 */
Character *Novel::character(int id) const
{
    for (Character *c : mCharacters)
        if (c->id() == id)
            return c;
    return 0;
}

/**
 * @brief Novel::getCharacter
 * Find a character based on a character label.
 * @param label The label for the character (e.g. "JoDo")
 * @return The character found, or 0 if no character is found.
 */
Character *Novel::character(const QString label) const
{
    for (Character *c : mCharacters)
        if (c->label() == label)
            return c;
    return 0;
}

/**
 * @brief Novel::addCharacter Add a character to the novel.
 * @param character Character to add.
 */
void Novel::addCharacter(Character *character)
{
    this->mCharacters.append(character);
}

void Novel::setCharacters(const QList<Character *> &characters)
{
    this->mCharacters = characters;
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

    novel[JSON_ID] = QJsonValue(id());
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

QString Novel::writeTo(const QString &filePath)
{
    QJsonObject jNovel = serialize();
    QFile *outFile = new QFile(filePath);
    int opened = outFile->open(QFile::WriteOnly);
    if (!opened)
        return QString();
    outFile->write(QJsonDocument(jNovel).toJson());
    outFile->close();
    return filePath;
}

Novel *Novel::readFrom(const QString &filePath)
{
    QFile *jsonFile = new QFile(filePath);
    bool opened = jsonFile->open(QFile::ReadOnly);

    if (!opened){
        qWarning() << "Could not open" << filePath;
        return 0;
    }

    QByteArray jsonData = jsonFile->readAll();
    jsonFile->close();
    QJsonParseError *error = new QJsonParseError();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, error);
    if (error->error == QJsonParseError::NoError)
        return Novel::deserialize(doc.object());

    qCritical() << "Failed to parse" << filePath << ":"
                << error->errorString();

    return 0;
}
