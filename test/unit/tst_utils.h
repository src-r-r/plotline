#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QObject>
#include <QtTest>
#include "utils.h"

class TestUtils : public QObject
{
    Q_OBJECT
public:
    explicit TestUtils(QObject *parent = 0);

signals:

public slots:

private Q_SLOTS:

    void test_findCharReverse();
    void test_reflowParagraph();

};

#endif // TESTUTILS_H
