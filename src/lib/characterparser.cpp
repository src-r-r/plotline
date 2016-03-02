#include "characterparser.h"

ParsedCharacterSet::ParsedCharacterSet(QObject *parent)
    : QHash<int, Character *>()
{
    Q_UNUSED(parent);
}

ParsedCharacterSet::~ParsedCharacterSet()
{

}

ParsedCharacterSet ParsedCharacterSet::parse(Novel *novel, const QString &string)
{
    int index = 0;
    QString label;
    Character *character = 0;

    ParsedCharacterSet set = ParsedCharacterSet();

    QRegularExpression labelX = Character::LABEL_X;

    QRegularExpressionMatchIterator matches = labelX.globalMatch(string);

    QRegularExpressionMatch match;
    while (matches.hasNext()){
        match = matches.next();
        label = match.captured(1);
        index = match.capturedStart(1);
        character = novel->characterByLabel(label);
        if (character)
            set.insert(index-1, character);
    }


    return set;
}

