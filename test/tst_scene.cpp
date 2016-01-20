#include <QString>
#include <QtTest>
#include "../src/scene.h"

class TestScene : public QObject
{
    Q_OBJECT

public:
    TestScene();

private Q_SLOTS:
    void testConstructor();
};

TestScene::TestScene()
{

}

void TestScene::testConstructor()
{
}

#include "tst_scene.moc"

