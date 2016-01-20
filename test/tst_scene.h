#ifndef TST_SCENE_H
#define TST_SCENE_H

#include <QString>
#include <QtTest>
#include "../src/scene.h"

class TestScene : public QObject
{
    Q_OBJECT

public:
    TestScene(QObject *parent = 0);

private Q_SLOTS:
    void testConstructor();
};

#endif // TST_SCENE_H

