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
    QTRY_COMPARE(chapter->getTitle(), QString("My First Chapter"));

    chapter = new Chapter(QString("My First Chapter"), QString("Once upon a time..."));
    QTRY_COMPARE(chapter->getTitle(), QString("My First Chapter"));
    QTRY_COMPARE(chapter->getContent(), QString("Once upon a time..."));

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

    Q_ASSERT(chapter1->getScenes().size() == 3);
}

void TestChapter::cleanupTestCase()
{
    delete mTestCharacters;
    delete mTestScenes;
}

void TestChapter::testSerialize()
{
    Chapter *chapter1 = new Chapter(QString("My First Chapter"));
    chapter1->setContent(QString("Once upon a time..."));

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
    QList<QString> keys = {QString("content"), QString("title"),
                           QString("scenes")};
    for (QString key : keys)
        Q_ASSERT(jChapter.contains(key));

    QTRY_COMPARE(jChapter["content"].toString(), QString("Once upon a time..."));
    QTRY_COMPARE(jChapter["title"].toString(), QString("My First Chapter"));
    QTRY_COMPARE(jChapter["content"].toString(), QString("Once upon a time..."));

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
    s1->setId(2);
    s2->setId(3);
    s3->setId(4);
    QList<Scene *> ch1Scenes = QList<Scene *>();
    ch1Scenes.append(s1);
    ch1Scenes.append(s2);
    ch1Scenes.append(s3);
    novel->setScenes(ch1Scenes);

    qDebug() << "Current directory: " << QDir::current().absolutePath();

    QFile *json = new QFile(QString("../../Plotline/test/fixtures/chapter-deserialize.json"));
    json->open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(json->readAll());
    json->close();

    Chapter *chapter = Chapter::deserialize(novel, doc.object());

    QTRY_COMPARE(chapter->getContent(), QString("Once upon a time..."));
    QTRY_COMPARE(chapter->getTitle(), QString("My First Chapter"));
