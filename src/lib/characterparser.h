#ifndef CHARACTERPARSER_H
#define CHARACTERPARSER_H

#include <QtCore>

class Character;
class Novel;

class ParsedCharacterSet : public QHash<int, Character *>
{

public:
    ParsedCharacterSet(QObject *parent = 0);
    ~ParsedCharacterSet();

    static ParsedCharacterSet parse(Novel *novel, const QString &string);

signals:

public slots:
};

#include "character.h"
#include "novel.h"

#endif // CHARACTERPARSER_H
