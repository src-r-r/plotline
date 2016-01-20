#include <QTest>
#include <QtCore>
#include <QDebug>

#include "tst_character.cpp"
#include "tst_chapter.cpp"
#include "tst_novel.cpp"
#include "tst_scene.cpp"

int main(int argc, char *argv[])
{

    QObject *tests[] = {

        new TestCharacter(),
        new TestScene(),
        new TestChapter(),
        new TestNovel(),

        NULL
    };

    int nFailed = 0;

    for (int i = 0; tests[i]; ++i)
        nFailed += QTest::qExec(tests[i]);

    QString border = QString("+++++++++++++++++ ");

    if (nFailed > 0)
        qWarning() << border << QString(nFailed)  << " tests failed. "
                 << border;
    else
        qDebug() << border << " All tests passed " << border << endl;
}
