#ifndef TST_CHARACTER_H
#define TST_CHARACTER_H

#include <QString>
#include <QtTest>
#include <QList>
#include <QDebug>
#include <iostream>
#include <stdlib.h>
#include "../src/character.h"
#include "../src/novel.h"

class TestCharacter : public QObject
{
    Q_OBJECT

public:
    TestCharacter(QObject *parent = 0);

private:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testConstructor();

    void testSerialize();
    void testDeserialize();
};

#endif // TST_CHARACTER_H

