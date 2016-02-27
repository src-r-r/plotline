#include "tst_chapter.h"

TestChapter::TestChapter(QObject *parent) : QObject(parent)
{

}

void TestChapter::initTestCase(){
    mTestCharacters = new QList<Character *>();

    mTestScenes = new QList<Scene *>();

}

void TestChapter::testConstructor()
{
    Chapter *chapter = new Chapter();

    chapter = new Chapter(QString("My First Chapter"));
    QTRY_COMPARE(chapter->title(), QString("My First Chapter"));

    // Test it with revisisons.

    delete chapter;
}

void TestChapter::testSetScenes()
{
    Chapter *chapter1 = new Chapter(QString("My First Chapter"));

    Scene *s1 = new Scene(
                QString("First test scene."),
                QString("This is my first test scene. Are you excited?")
                ),
            *s2 = new Scene (
                QString("2nd Test Scene"),
                QString("This is my second test scene! Now I'm really excited.")),
            *s3 = new Scene (
                QString("3rd test scene."),
                QString("Okay, enough for now. 3 should be enough."));

    QList<Scene *> ch1Scenes = QList<Scene *>();
    ch1Scenes.append(s1);
    ch1Scenes.append(s2);
    ch1Scenes.append(s3);
    chapter1->setScenes(ch1Scenes);

    Q_ASSERT(chapter1->scenes().size() == 3);
}

void TestChapter::testAddRevision()
{
    Chapter *c = new Chapter("Chapter");
    Revision *r1 = c->addRevision();

    Q_ASSERT(c->revisions().length() == 1);
    Q_ASSERT(c->revisions()[0]->content().isNull());

    QString s1 = "Hte quick brown fox jumps over teh lazy dog.",
            s2 = "The quick brown fox jumps over the lazy dog.";

    r1->setContent(s1);
    Revision *r2 = c->addRevision();

    Q_ASSERT(c->revisions().length() == 2);
    QTRY_COMPARE(c->revisions()[0]->content(), s1);
    QTRY_COMPARE(c->revisions()[1]->content(), s1);

    r2->setContent(s2);
    QTRY_COMPARE(c->revisions()[1]->content(), s2);
}

void TestChapter::cleanupTestCase()
{
    delete mTestCharacters;
    delete mTestScenes;
}

void TestChapter::testSerialize()
{
    Chapter *chapter1 = new Chapter(QString("My First Chapter"));

    Scene *s1 = new Scene(
                QString("First test scene."),
                QString("This is my first test scene. Are you excited?")
                ),
            *s2 = new Scene (
                QString("2nd Test Scene"),
                QString("This is my second test scene! Now I'm really excited.")),
            *s3 = new Scene (
                QString("3rd test scene."),
                QString("Okay, enough for now. 3 should be enough."));
    QList<Scene *> ch1Scenes = QList<Scene *>();
    ch1Scenes.append(s1);
    ch1Scenes.append(s2);
    ch1Scenes.append(s3);
    chapter1->setScenes(ch1Scenes);

    QJsonObject jChapter = chapter1->serialize();
    Q_ASSERT(jChapter.contains(QString("title")));
    Q_ASSERT(jChapter.contains(QString("scenes")));

    QTRY_COMPARE(jChapter["title"].toString(), QString("My First Chapter"));

    QJsonDocument doc = QJsonDocument(jChapter);
}

void TestChapter::testDeserialize()
{

    Novel *novel = new Novel(QString("My Novel"), QString("My Genre"));

    Scene *s1 = new Scene(
                QString("First test scene."),
                QString("This is my first test scene. Are you excited?")
                ),
            *s2 = new Scene (
                QString("2nd Test Scene"),
                QString("This is my second test scene! Now I'm really excited.")),
            *s3 = new Scene (
                QString("3rd test scene."),
                QString("Okay, enough for now. 3 should be enough."));
    s1->setId(QUuid::createUuid());
    s2->setId(QUuid::createUuid());
    s3->setId(QUuid::createUuid());
    QList<Scene *> ch1Scenes = QList<Scene *>();
    ch1Scenes.append(s1);
    ch1Scenes.append(s2);
    ch1Scenes.append(s3);
    novel->setScenes(ch1Scenes);

    QFile *json = new QFile(QString("../../../Plotline/test/unit/fixtures/chapter-deserialize.json"));
    Q_ASSERT(json->open(QFile::ReadOnly) == true);
    QByteArray jsonContent = json->readAll();
    qDebug() << "Parsing content" << jsonContent;
    QJsonParseError *error = new QJsonParseError();
    QJsonDocument doc = QJsonDocument::fromJson(jsonContent, error);
    json->close();

    if (doc.isEmpty() || doc.isNull()){
        qDebug() << error->errorString();
        qFatal("Could not open json file.");
    }

    Chapter *chapter = Chapter::deserialize(novel, doc.object());

    QTRY_COMPARE(chapter->title(), QString("My First Chapter"));
    Q_ASSERT(chapter->scenes().size() == 3);
    QTRY_COMPARE(chapter->scenes()[0], s1);
    QTRY_COMPARE(chapter->scenes()[1], s2);
    QTRY_COMPARE(chapter->scenes()[2], s3);
}
