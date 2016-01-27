#ifndef TST_CHAPTER_H
#define TST_CHAPTER_H

#include <QString>
#include <QtTest>
#include <QList>
#include <QtDebug>
#include <iostream>
#include <stdlib.h>
#include "chapter.h"

class TestChapter : public QObject
{
    Q_OBJECT

public:
    TestChapter(QObject *parent = 0);

private:
    QList<Character *> *mTestCharacters;
    QList<Scene *> *mTestScenes;

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testConstructor();
    void testSetScenes();
    void testAddRevision();
    void testSerialize();
    void testDeserialize();
};

#endif // TST_CHAPTER_H

