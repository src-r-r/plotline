#ifndef TST_NOVEL_H
#define TST_NOVEL_H

#include <QString>
#include <QtTest>
#include "novel.h"

class TestNovel : public QObject
{
    Q_OBJECT

public:
    TestNovel(QObject *parent = 0);

private Q_SLOTS:
    void testConstructor();
    void testSetters();
    void testSerialize();
    void testDeserialize();
    void testGetCharacters();
    void testRevisions();
};

#endif // TST_NOVEL_H

