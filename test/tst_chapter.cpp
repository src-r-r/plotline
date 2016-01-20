#include <QString>
#include <QtTest>
#include <QList>
#include <QDebug>
#include <iostream>
#include <stdlib.h>
#include "../src/chapter.h"

class TestChapter : public QObject
{
    Q_OBJECT

public:
    TestChapter();

private:
    QList<Character *> *mTestCharacters;
    QList<Scene *> *mTestScenes;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testConstructor();
    void testSetScenes();
};

TestChapter::TestChapter()
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

#include "tst_chapter.moc"
