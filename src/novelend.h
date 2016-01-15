#ifndef NOVELEND_H
#define NOVELEND_H

#include "novelpart.h"

class NovelEnd : public NovelPart
{
private:
    QString
        *internalClimax,
        *externalClimax,
        *resolution,
        *characterGrowth;
public:
    NovelEnd();

    QString *getInternalClimax() const;
    void setInternalClimax(QString *value);

    QString *getExternalClimax() const;
    void setExternalClimax(QString *value);

    QString *getResolution() const;
    void setResolution(QString *value);

    QString *getCharacterGrowth() const;
    void setCharacterGrowth(QString *value);

signals:

public slots:
};

#endif // NOVELEND_H
