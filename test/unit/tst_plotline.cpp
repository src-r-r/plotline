#include "tst_plotline.h"

TestPlotline::TestPlotline(QObject *parent) : QObject(parent)
{

}

void TestPlotline::testSerialize()
{

}

void TestPlotline::testDeserialize()
{

}

void TestPlotline::testConstructor()
{
    QList<Scene *> scenes = QList<Scene *>();
    QList<Character *> characters = QList<Character *>();
    scenes << new Scene(QString("Headline 1"), QString("Action 1"))
           << new Scene(QString("Headline 2"), QString("Action 2"))
           << new Scene(QString("Headline 3"), QString("Action 3"));

    characters << new Character(QString("Theodore Roosevelt"))
               << new Character(QString("Abraham Lincoln"))
               << new Character(QString("Benjamin Franklin"));

    QColor color = QColor("#ffaabb");

    Plotline *p = new Plotline(QString("Something happens"),
                               QString("Synopsis 1"),
                               scenes,
                               characters,
                               color,
                               0,
                               12);

    QTRY_COMPARE(p->synopsis(), QString("Synopsis 1"));
    QTRY_COMPARE(p->brief(), QString("Something happens"));
    QTRY_COMPARE(p->characters(), characters);
    Q_ASSERT(p->id() == 12);
    QTRY_COMPARE(p->getColor(), QColor("#ffaabb"));
    QTRY_COMPARE(p->getScenes(), scenes);

}
