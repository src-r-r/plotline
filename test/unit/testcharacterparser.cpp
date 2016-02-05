#include "testcharacterparser.h"

TestCharacterParser::TestCharacterParser(QObject *parent) : QObject(parent)
{

}

void TestCharacterParser::testParser()
{
    Novel *novel = new Novel("Test Novel");

    Character *c1 = new Character("Bob McCalin"),
            *c2 = new Character("Sue Robinson"),
            *c3 = new Character("Henry Scott");

    novel->addCharacter(c1);
    novel->addCharacter(c2);
    novel->addCharacter(c3);

    QString string = QString("This scene will include @BoMc and @SuRo ") +
                     QString("but will not include @HeS (Henry Scott) ") +
                     QString("because someone made a typo.");

    ParsedCharacterSet set = ParsedCharacterSet::parse(novel, string);

    int i1 = string.indexOf("@BoMc"),
            i2 = string.indexOf("@SuRo"),
            i3 = string.indexOf("@HeS");

    Q_ASSERT(set.contains(i1));
    Q_ASSERT(set.contains(i2));
    Q_ASSERT(!set.contains(i3));

    Q_ASSERT(set.value(i1) == c1);
    Q_ASSERT(set.value(i2) == c2);
}

