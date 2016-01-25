#ifndef TESTPLOTLINE_H
#define TESTPLOTLINE_H

#include <QObject>
#include <QtTest>
#include "plotline.h"

class TestPlotline : public QObject
{
    Q_OBJECT
public:
    explicit TestPlotline(QObject *parent = 0);

signals:

private Q_SLOTS:
    void testConstructor();
    void testSerialize();
    void testDeserialize();
};

#endif // TESTPLOTLINE_H
