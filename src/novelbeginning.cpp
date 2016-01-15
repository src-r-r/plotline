#include "novelbeginning.h"

QString *NovelBeginning::getIncitingIncident() const
{
    return incitingIncident;
}

void NovelBeginning::setIncitingIncident(QString *value)
{
    incitingIncident = value;
}

QString *NovelBeginning::getInternalInitialConflict() const
{
    return internalInitialConflict;
}

void NovelBeginning::setInternalInitialConflict(QString *value)
{
    internalInitialConflict = value;
}

QString *NovelBeginning::getExternalInitialConflict() const
{
    return externalInitialConflict;
}

void NovelBeginning::setExternalInitialConflict(QString *value)
{
    externalInitialConflict = value;
}

void NovelBeginning::setBackstory(QString *value)
{
    backstory = value;
}

QString *NovelBeginning::getBackstory() const
{
    return backstory;
}

NovelBeginning::NovelBeginning()
{

}

