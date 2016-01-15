#include "novelend.h"

QString *NovelEnd::getInternalClimax() const
{
    return internalClimax;
}

void NovelEnd::setInternalClimax(QString *value)
{
    internalClimax = value;
}

QString *NovelEnd::getExternalClimax() const
{
    return externalClimax;
}

QString *NovelEnd::getResolution() const
{
    return resolution;
}

void NovelEnd::setResolution(QString *value)
{
    resolution = value;
}

QString *NovelEnd::getCharacterGrowth() const
{
    return characterGrowth;
}

void NovelEnd::setCharacterGrowth(QString *value)
{
    characterGrowth = value;
}

NovelEnd::NovelEnd()
{

}

