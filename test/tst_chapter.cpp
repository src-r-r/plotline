#include <QString>
#include <QtTest>
#include "../src/chapter.h"

class TestChapter : public QObject
{
    Q_OBJECT

public:
    TestChapter();

private Q_SLOTS:
    void testConstructor();
};

void TestChapter::testConstructor()
{

}


QTEST_APPLESS_MAIN(TestChapter)

#include "tst_chapter.moc"
