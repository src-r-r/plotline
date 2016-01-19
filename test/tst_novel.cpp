#include <QString>
#include <QtTest>
#include "../src/novel.h"

class TestNovel : public QObject
{
    Q_OBJECT

public:
    TestNovel();

private Q_SLOTS:
    void testConstructor();
    void testSetters();
};

TestNovel::TestNovel()
{
}

void TestNovel::testConstructor()
{
    QVERIFY2(true, "Failure");

    QString title = QString("The Three Little Pigs");
    QString genre = QString("Fairy Tale");
    QString setting = QString("Contryside");
    Novel::Tense tense = Novel::Future;
    Novel::PointOfView pov = Novel::ThirdPersonPlural;

    Novel *novel = new Novel(title);
    QTRY_COMPARE(novel->getWorkingTitle(), QString("The Three Little Pigs"));
    QTRY_COMPARE(novel->getPointOfView(), Novel::ThirdPersonSingular);
    QTRY_COMPARE(novel->getTense(), Novel::Past);

    novel = new Novel(title, genre);
    QTRY_COMPARE(novel->getWorkingTitle(), QString("The Three Little Pigs"));
    QTRY_COMPARE(novel->getGenre(), QString("Fairy Tale"));
    QTRY_COMPARE(novel->getPointOfView(), Novel::ThirdPersonSingular);
    QTRY_COMPARE(novel->getTense(), Novel::Past);

    novel = new Novel(title, genre, setting, tense, pov);
    QTRY_COMPARE(novel->getPointOfView(), Novel::ThirdPersonPlural);
    QTRY_COMPARE(novel->getTense(), Novel::Future);

    delete novel;
}

void TestNovel::testSetters()
{
    QString title = QString("The Three Little Pigs");
    QString genre = QString("Fairy Tale");
    QString setting = QString("Contryside");
    Novel::Tense tense = Novel::Past;
    Novel::PointOfView pov = Novel::ThirdPersonSingular;

    Novel *novel = new Novel(title, genre, setting, tense, pov);

    novel->setGenre(QString("Western"));
    QTRY_COMPARE(novel->getGenre(), QString("Western"));

    novel->setSetting(QString("Outer Space"));
    QTRY_COMPARE(novel->getSetting(), QString("Outer Space"));

    novel->setPointOfView(Novel::SecondPersonSingular);
    QTRY_COMPARE(novel->getPointOfView(), Novel::SecondPersonSingular);

    novel->setTense(Novel::Future);
    QTRY_COMPARE(novel->getTense(), Novel::Future);
}

QTEST_APPLESS_MAIN(TestNovel)

#include "tst_novel.moc"
