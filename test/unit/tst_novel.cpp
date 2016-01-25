#include "tst_novel.h"

TestNovel::TestNovel(QObject *parent) : QObject(parent)
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

void TestNovel::testSerialize()
{
    QString title = QString("Novel Title");
    QString setting = QString("Novel Setting");
    QString genre = QString("Novel Genre");
    Novel::Tense tense = Novel::Present;
    Novel::PointOfView pointOfView = Novel::FirstPersonPlural;

    QList<Character *> characters = QList<Character *>();
    characters << new Character(QString("Theodore Roosevelt"))
               << new Character(QString("Abraham Lincoln"))
               << new Character(QString("Benjamin Franklin"));

    QList<Scene *> scenes = QList<Scene *>();
    scenes << new Scene(QString("Healine 1"), QString("Action 1"))
           << new Scene(QString("Healine 2"), QString("Action 2"))
           << new Scene(QString("Healine 3"), QString("Action 3"));

    QList<Chapter *> chapters = QList<Chapter *>();
    chapters << new Chapter(QString("Chapter 1"))
             << new Chapter(QString("Chapter 2"))
             << new Chapter(QString("Chapter 2"));

    QList<Plotline *> plotlines = QList<Plotline *>();
    plotlines << new Plotline(QString("Plotline 1"))
              << new Plotline(QString("Plotline 2"))
              << new Plotline(QString("Plotline 3"));

    Novel *novel = new Novel(title, genre, setting, tense, pointOfView,
                             characters, scenes, chapters, plotlines);

    QJsonObject jNovel = novel->serialize();
    QTRY_COMPARE(jNovel["workingTitle"].toString(), title);
    QTRY_COMPARE(jNovel["genre"].toString(), genre);
    QTRY_COMPARE(jNovel["setting"].toString(), setting);
    Q_ASSERT(jNovel["tense"].toInt() == tense);
    Q_ASSERT(jNovel["pointOfView"].toInt() == pointOfView);
    Q_ASSERT(jNovel["characters"].toArray().size() == characters.size());
    Q_ASSERT(jNovel["scenes"].toArray().size() == scenes.size());
    Q_ASSERT(jNovel["chapters"].toArray().size() == chapters.size());
    Q_ASSERT(jNovel["plotlines"].toArray().size() == plotlines.size());

    // Just for grins, see what the object looks like.

    qDebug() << QJsonDocument(jNovel).toJson();
}

void TestNovel::testDeserialize()
{

    QFile *json = new QFile(QString("../../Plotline/test/fixtures/novel-deserialize.json"));
    json->open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(json->readAll());
    json->close();

    Novel *novel = Novel::deserialize(doc.object());

    QTRY_COMPARE(novel->getWorkingTitle(), QString("My Novel"));
    Q_ASSERT(novel->getChapters().size() == 3);
    Q_ASSERT(novel->getScenes().size() == 3);
    QVERIFY(novel->getCharacter("AbLi") != 0);
    QVERIFY(novel->getCharacter("AbLi")->getId() > 0);
    QVERIFY(novel->getScenes()[0]->getCharacters().size() == 3);
    QVERIFY(novel->getScenes()[0]->getPointsOfView().size() == 1);
    QVERIFY(novel->getScenes()[1]->getCharacters().size() == 2);
    QVERIFY(novel->getScenes()[1]->getPointsOfView().size() == 1);
    QVERIFY(novel->getScenes()[2]->getCharacters().size() == 2);
    QVERIFY(novel->getScenes()[2]->getPointsOfView().size() == 2);
    QVERIFY(novel->getChapters()[0]->getScenes().size() == 1);
    QVERIFY(novel->getChapters()[1]->getScenes().size() == 1);
    QVERIFY(novel->getChapters()[2]->getScenes().size() == 2);
}
