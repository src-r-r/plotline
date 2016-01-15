#ifndef NOVELBEGINNING_H
#define NOVELBEGINNING_H

#include <QtCore>
#include <novelpart.h>

class NovelBeginning : public NovelPart
{
private:
    QString *incitingIncident,
        *internalInitialConflict,
        *externalInitialConflict,
        *backstory;
public:
    NovelBeginning();

    QString *getIncitingIncident() const;
    void setIncitingIncident(QString *value);

    QString *getInternalInitialConflict() const;
    void setInternalInitialConflict(QString *value);

    QString *getExternalInitialConflict() const;
    void setExternalInitialConflict(QString *value);

    QString *getBackstory() const;
    void setBackstory(QString *value);

signals:

public slots:
};

#endif // NOVELBEGINNING_H
