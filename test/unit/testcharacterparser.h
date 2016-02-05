#ifndef TESTCHARACTERPARSER_H
#define TESTCHARACTERPARSER_H

#include <QObject>
#include <QTest>

#include "characterparser.h"

class TestCharacterParser : public QObject
{
    Q_OBJECT
public:
    explicit TestCharacterParser(QObject *parent = 0);

signals:

public slots:


private Q_SLOTS:

    void testParser();
};

#endif // TESTCHARACTERPARSER_H
