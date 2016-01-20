#include <QString>
#include <QtTest>
#include <QList>
#include <QDebug>
#include <iostream>
#include <stdlib.h>
#include "../src/character.h"

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
};

void TestCharacter::initTestCase()
{

}

void TestCharacter::cleanupTestCase()
{

}

TestCharacter::TestCharacter(QObject *parent) : QObject(parent)
{

}

void TestCharacter::testConstructor()
{
    Character *character = new Character(
        QString("David Caine")
    );

    QTRY_COMPARE(character->getLabel(), QString("DaCa"));
    delete character;

    character = new Character(
                QString("Matthew"));
    QTRY_COMPARE(character->getLabel(), QString("Ma"));
    delete character;

    character = new Character(
                QString("Galactron of the 4th World Order"));
    QTRY_COMPARE(character->getLabel(), QString("GaOfTh4tWoOr"));

    character = new Character(
                QString("Samuel Ricker"),
                QString("Sammy"), QString("SaRk"));
    QTRY_COMPARE(character->getLabel(), QString("SaRk"));
}

//#include "tst_character.moc"
