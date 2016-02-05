#include <QTest>
#include <QtCore>
#include <QtDebug>
#include <QGuiApplication>
#include <QMainWindow>

#include "tst_revision.h"
#include "tst_character.cpp"
#include "tst_chapter.cpp"
#include "tst_novel.cpp"
#include "tst_scene.cpp"
#include "tst_plotline.h"
#include "testcharacterparser.h"

int main(int argc, char *argv[])
{

    QObject *tests[] = {

        new TestCharacter(),
        new TestRevision(),
        new TestScene(),
        new TestChapter(),
        new TestNovel(),
        new TestPlotline(),
        new TestCharacterParser(),

        NULL
    };

    QGuiApplication a(argc, argv);

    int nFailed = 0;

    for (int i = 0; tests[i]; ++i)
        nFailed += QTest::qExec(tests[i], argc, argv);

    QString border = QString("+++++++++++++++++ ");

    if (nFailed > 0)
        qWarning() << border << QString(nFailed)  << " tests failed. "
                 << border;
    else
        qDebug() << border << " All tests passed " << border;

    return a.exec();
}
