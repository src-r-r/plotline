#include "tst_revision.h"

TestRevision::TestRevision(QObject *parent) : QObject(parent)
{

}

void TestRevision::testConstructor()
{
    Revision *revision = new Revision("Revision Content");
    QTRY_COMPARE(revision->content(), QString("Revision Content"));

    Chapter *chapter = new Chapter(QString("Chapter"));

    revision = new Revision(QString("Revision Content"), chapter);
    QTRY_COMPARE(revision->content(), QString("Revision Content"));
    QTRY_COMPARE(revision->chapter(), chapter);

    revision = new Revision(QString("Revision Content"), chapter,
                                      false);
    Q_ASSERT(revision->isComplete() == false);
    revision->toggleComplete();
    Q_ASSERT(revision->isComplete() == true);
}

void TestRevision::testSerialize()
{
    Revision *revision = new Revision(QString("Revision Content"), 0,
                                      true, 2);
    QJsonObject obj = revision->serialize();
    Q_ASSERT(obj.contains("content"));
    QTRY_COMPARE(obj["content"].toString(), QString("Revision Content"));
    Q_ASSERT(!obj.contains("chapter"));
    Q_ASSERT(obj["isComplete"].toBool() == true);
    Q_ASSERT(obj["id"].toInt() == 2);
}

void TestRevision::testDeserialize()
{
    QFile *json = new QFile(QString("../../../Plotline/test/unit/fixtures/revision-deserialize.json"));
    json->open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(json->readAll());
    json->close();

    Novel *novel = new Novel(QString("My Novel"));
    Chapter *chapter = new Chapter();

    Revision *revision = Revision::deserialize(novel, chapter, doc.object());
    QTRY_COMPARE(revision->content(), QString("Revision Content"));
    Q_ASSERT(revision->id() == 2);
    Q_ASSERT(revision->isComplete() == true);
}

void TestRevision::testChapterRevisions()
{
    QString cont1 = "This is my first chapter and first revision!",
            cont2 = "This is my first chapter, but not my first revision.";
    Chapter *chapter = new Chapter();
    chapter->setContent(cont1, 0);
    chapter->addRevision();
    QVERIFY(!chapter->content(0).isEmpty());
    QCOMPARE(chapter->content(0), chapter->content(1));

    chapter->setContent(cont2, 1);
    QCOMPARE(chapter->content(1), cont2);
}

void TestRevision::testNovelDeserialize()
{
    Novel *novel = Novel::readFrom("../../../Plotline/test/unit/fixtures/revision-bug-test.json");
    if (!novel) QFAIL("Novel is null!");
    Q_ASSERT(novel->revisions().count() == 3);
    for (Chapter *c : novel->chapters()){
        qDebug() << "Assert Chapter" << c->number() << "has 3 revisions.";
        Q_ASSERT(c->revisions().count() == 3);
    }

    // Verify that ch2r2 is an exact copy of ch2r1
    Chapter *ch = novel->chapters()[1];
    QVERIFY(!ch->content(2).isEmpty());
    QCOMPARE(ch->content(2), ch->content(1));
    QCOMPARE(ch->content(2), ch->latestContent());

    Chapter *ch3 = new Chapter("Chapter Three");
    novel->addChapter(ch3);
    Q_ASSERT(ch3->revisions().count() == 3);
}

