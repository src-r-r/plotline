#include "characterparser.h"

ParsedCharacterSet::ParsedCharacterSet(QObject *parent)
{

}

ParsedCharacterSet::~ParsedCharacterSet()
{

}

ParsedCharacterSet ParsedCharacterSet::parse(Novel *novel, const QString &string)
{
    QList<Character *> characters = novel->characters();
    int lastIndex = 0,
            index = 0;
    QString label;

    ParsedCharacterSet set = ParsedCharacterSet();

    for (Character *c : characters){
        label = QString("@") + c->label();
        while (-1 < (index = string.indexOf(label, lastIndex))){
            set.insert(index, c);
            lastIndex = index + label.length();
        }
    }

    return set;
}

