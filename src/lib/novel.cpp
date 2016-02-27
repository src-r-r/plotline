#include "novel.h"

const QString Novel::JSON_WORKING_TITLE = QString("workingTitle"),
    Novel::JSON_GENRE = QString("genre"),
    Novel::JSON_SETTING = QString("setting"),
    Novel::JSON_TENSE = QString("tense"),
    Novel::JSON_POV = QString("pointOfView"),
    Novel::JSON_AUTHOR = "author",
    Novel::JSON_SCENES = QString("scenes"),
    Novel::JSON_CHARACTERS = QString("characters"),
    Novel::JSON_CHAPTERS = QString("chapters"),
    Novel::JSON_PLOTLINES = QString("plotlines"),
    Novel::JSON_REVISIONS = QString("revisions"),
    Novel::JSON_CURRENT_REVISION = QString("currentRevision");

Novel::Novel(const QString &workingTitle,
             const QString &genre,
             const QString &setting,
             const Novel::Tense tense,
             const Novel::PointOfView pov,
             Author *author,
             const QList<Character *> characters,
             const QList<Scene *> scenes,
             const QList<Chapter *> chapters,
             const QList<Plotline *> plotlines,
             const QStringList &revisions,
             int currentRevision,
             QUuid id,
             QObject *parent)
    : QObject(parent), Serializable(id)
{
    this->mWorkingTitle = workingTitle;
    this->mGenre = genre;
    this->mTense = tense;
    this->mSetting = setting;
    this->mPointOfView = pov;
    this->mAuthor = (author == 0) ? new Author() : author;
    mAuthor->setNovel(this);
    this->mCharacters = characters;
    this->mScenes = scenes;
    this->mChapters = chapters;
    this->mPlotlines = plotlines;
    mRevisions = revisions;
    if (mRevisions.empty())
        mRevisions.append(QString());
    this->mCurrentRevision = currentRevision < 0 ? revisions.count() -1
                                                 : currentRevision;

    // Ensure all chapters have the adequate number of revisions.
    for (Chapter *c : mChapters)
        while (c->revisions().count() < mRevisions.count())
            c->addRevision();
}

Novel::~Novel()
{
    delete mAuthor;
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

QList<Scene *> Novel::scenes() const
{
    return mScenes;
}

Scene *Novel::scene(QUuid id) const
{
    for (Scene *s : mScenes)
        if (s->id() == id)
            return s;
    return 0;
}

void Novel::moveScenes(int from, int to)
{
    mScenes.move(from, to);
}

void Novel::setScenes(const QList<Scene *> &value)
{
    mScenes = value;
}

void Novel::addScene(Scene *scene, int i)
{
    scene->setNovel(this);
    if (i < 0 || i > mScenes.count())
        mScenes.append(scene);
    else
        mScenes.insert(i, scene);
}

void Novel::removeScene(Scene *scene)
{
    mScenes.removeAll(scene);
}

void Novel::removeScene(QUuid id)
{
    removeScene(scene(id));
}

QList<Chapter *> Novel::chapters() const
{
    return mChapters;
}

Chapter *Novel::chapterByNumber(int number)
{
    return mChapters[number];
}

Chapter *Novel::chapter(QUuid id) const
{
    for (Chapter *c : mChapters)
        if (c->id() == id)
            return c;
    return 0;
}

void Novel::setChapters(const QList<Chapter *> &value)
{
    mChapters = value;
    for (Chapter *c : mChapters)
        while (c->revisions().count() < mRevisions.count())
            c->addRevision();
}

void Novel::addChapter(Chapter *chapter, int loc)
{
    // Add revisions to the chapter.
    chapter->setNovel(this);
    while(chapter->revisions().count() < mRevisions.count())
        chapter->addRevision();
    if (loc < 0 || loc >= mCharacters.count())
        mChapters.append(chapter);
    else
        mChapters.insert(loc, chapter);
}

Revision *Novel::chapterRevision(int chapter, int revision)
{
    return this->chapterByNumber(chapter)->revisions()[revision];
}

void Novel::removeChapter(Chapter *chapter)
{
    mChapters.removeAll(chapter);
}

void Novel::removeChapterAt(int index, bool doDelete)
{
    Chapter *chapter = mChapters[index];
    mChapters.removeAt(index);
    if (doDelete)
        delete chapter;
}

void Novel::moveChapter(int from, int to)
{
    mChapters.move(from, to);
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

Plotline *Novel::plotline(QUuid id) const
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
    plotline->setNovel(this);
}

void Novel::removePlotline(Plotline *plotline)
{
    if (0 != plotline)
        mPlotlines.removeAll(plotline);
}

void Novel::removePlotline(const QUuid id)
{
    removePlotline(plotline(id));
}

QList<Character *> Novel::characters()
{
    return this->mCharacters;
}


QList<Character *> Novel::characters(const QRegularExpression &exp) const
{
    QList<Character *> result;
    for (Character *c : mCharacters)
        if (c->label().contains(exp))
            result << c;
    return result;
}

QList<Character *> Novel::characters(const QString &label) const
{
    return characters(QRegularExpression(label));
}

QList<Character *> Novel::charactersByName(const QRegularExpression &exp) const
{
    QList<Character *> result;
    for (Character *c : mCharacters)
        if (c->name().contains(exp))
            result << c;
    return result;
}

QList<Character *> Novel::charactersByName(const QString &name) const
{
    return charactersByName(QRegularExpression(name));
}

/**
 * @brief Novel::getCharacter
 * Get a character based on a character ID
 * @param id the character ID
 * @return The character whose ID is id, or NULL if not found.
 */
Character *Novel::character(const QUuid &id) const
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
Character *Novel::characterByLabel(const QString label) const
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
void Novel::addCharacter(Character *character, const int i)
{
    if (i < 0)
        this->mCharacters.append(character);
    else
        this->mCharacters.insert(i, character);
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
            jPlotlines = QJsonArray(),
            jRevisions = QJsonArray();

    for (Scene *s : mScenes)
        jScenes.append(s->serialize());

    for (Chapter *c : mChapters)
        jChapters.append(c->serialize());

    for (Character *a : mCharacters)
        jCharacters.append(a->serialize());

    for (Plotline *p : mPlotlines)
        jPlotlines.append(p->serialize());

    for (QString s : mRevisions)
        jRevisions.append(s);

    novel[JSON_ID] = id().toString();
    novel[JSON_WORKING_TITLE] = mWorkingTitle;
    novel[JSON_SETTING] = mSetting;
    novel[JSON_GENRE] = mGenre;
    novel[JSON_POV] = QJsonValue(mPointOfView);
    novel[JSON_TENSE] = QJsonValue(mTense);
    if (mAuthor != 0)
        novel[JSON_AUTHOR] = mAuthor->serialize();
    novel[JSON_CHARACTERS] = jCharacters;
    novel[JSON_SCENES] = jScenes;
    novel[JSON_CHAPTERS] = jChapters;
    novel[JSON_PLOTLINES] = jPlotlines;
    novel[JSON_REVISIONS] = QJsonValue(jRevisions);
    novel[JSON_CURRENT_REVISION] = QJsonValue(mCurrentRevision);
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

    QStringList revisions;

    int currentRevision=0;

    QUuid id = Serializable::deserialize(object);

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

    if (object.contains(JSON_REVISIONS))
        for (QJsonValue v : object[JSON_REVISIONS].toArray())
            revisions << v.toString();
    else
        notFound << JSON_REVISIONS;

    if (object.contains(JSON_CURRENT_REVISION))
        currentRevision = object[JSON_CURRENT_REVISION].toInt();
    else
        notFound << JSON_CURRENT_REVISION;

    Novel *novel = new Novel(workingTitle, genre, setting, tense,
                             pointOfView, 0, characters, scenes, chapters,
                             plotlines, revisions, currentRevision);

    if (object.contains(JSON_AUTHOR))
        novel->setAuthor(Author::deserialize(novel, object[JSON_AUTHOR].toObject()));
    else
        notFound << JSON_AUTHOR;

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

Novel *Novel::readFrom(const QString &filePath, QString *errorStr)
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
    else if (errorStr != 0){
        QPair<int, int> offset = multilineOffset(QString(jsonData),
                                                 error->offset);
        (*errorStr) = tr("\"") + QString(error->errorString()) + tr("\"");
        (*errorStr) += tr(" at line ") + QVariant(offset.first).toString() +
                tr(" column ") +  QVariant(offset.second).toString();
    }

    qCritical() << "Failed to parse" << filePath << ":"
                << error->errorString();

    return 0;
}

QStringList Novel::revisions() const
{
    return mRevisions;
}

void Novel::addRevision(const QString &comment)
{
    mRevisions.append(comment);
    // Also copy the chapter contents.
    for (Chapter *c : mChapters)
        c->addRevision();
}

void Novel::addRevisions(const QStringList &comments)
{
    for (QString comment : comments){
        mRevisions.append(comment);
        for (Chapter *c : mChapters)
            c->addRevision();
    }
}

void Novel::removeRevision(const int index)
{
    if (index < 0)
        mRevisions.removeAt(mCurrentRevision);
    else
        mRevisions.removeAt(index);
}

void Novel::setRevisions(const QStringList &revisions)
{
    mRevisions = revisions;
    for (Chapter *c : mChapters)
        while (c->revisions().count() < mRevisions.count())
            c->addRevision();
}

void Novel::setRevisionComment(const int index, const QString &comment)
{
    mRevisions[index] = comment;
}

void Novel::setRevisionComment(const QString &comment)
{
    setRevisionComment(mCurrentRevision, comment);
}

QString Novel::revisionComment(const int index) const
{
    if (index < 0)
        return mRevisions[mCurrentRevision];
    return mRevisions[index];
}

int Novel::revisionCount() const
{
    return mRevisions.count();
}

void Novel::goToLatestRevision()
{
    setCurrentRevision(revisionCount()-1);
}

int Novel::currentRevision() const
{
    return mCurrentRevision;
}

void Novel::setCurrentRevision(int currentRevison)
{
    mCurrentRevision = currentRevison;
    // Also syncronize the chapters.
    for (Chapter *c : mChapters)
        c->setCurrentRevision(mCurrentRevision);
}

Author *Novel::author() const
{
    return mAuthor;
}

void Novel::setAuthor(Author *author)
{
    mAuthor = author;
}
