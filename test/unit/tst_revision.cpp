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
    Q_ASSERT(revision->getId() == 2);
    Q_ASSERT(revision->isComplete() == true);
}

