#include "tst_utils.h"

TestUtils::TestUtils(QObject *parent) : QObject(parent)
{

}

void TestUtils::test_findCharReverse()
{

    QString test = "Can you @find this @tag in a string?";
    int pos = test.indexOf("@tag") + QString("@tag").length()-1;
    int expected = test.indexOf("@tag");
    int i = findCharReverse("@#", test, pos, " ");

    qDebug() << "Position:" << pos
             << ", expected:" << expected
             << ", result:" << i;
    Q_ASSERT(i == expected);

    test = "There should be nothing found here.";
    pos = 14;
    expected = -1;
    i = findCharReverse("@#", test, pos, " ");
    Q_ASSERT(i == expected);

    test = "This @tag should not be found.";
    pos = test.indexOf("not");
    expected = -1;
    i = findCharReverse("@#", test, pos, " ");
    Q_ASSERT(i == expected);

}

