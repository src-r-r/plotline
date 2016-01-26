#ifndef TESTREVISION_H
#define TESTREVISION_H

#include <QTest>
#include <QtDebug>
#include "revision.h"

class TestRevision : public QObject
{
    Q_OBJECT
public:
    explicit TestRevision(QObject *parent = 0);

signals:

private Q_SLOTS:

    void testConstructor();
    void testSerialize();
    void testDeserialize();
};

#endif // TESTREVISION_H
