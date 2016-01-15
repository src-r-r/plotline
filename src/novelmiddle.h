#ifndef NOVELMIDDLE_H
#define NOVELMIDDLE_H

#include "novelpart.h"

class NovelMiddle : public NovelPart
{
private:
    QString
        *internalConflict,
        *externalConflict,
        *internalHigherConflict,
        *externalHigherConflict,
        *inertnalHighestConflict,
        *externalHighestConflict,
        *internalPointOfNoReturn,
        *externalPointOfNoReturn,
        *darkestHour,
        *turningPoint;

public:
    NovelMiddle();

    QString *getInternalConflict() const;
    void setInternalConflict(QString *value);

    QString *getExternalConflict() const;
    void setExternalConflict(QString *value);

    QString *getInternalHigherConflict() const;
    void setInternalHigherConflict(QString *value);

    QString *getExternalHigherConflict() const;
    void setExternalHigherConflict(QString *value);

    QString *getInertnalHighestConflict() const;
    void setInertnalHighestConflict(QString *value);

    QString *getExternalHighestConflict() const;
    void setExternalHighestConflict(QString *value);

    QString *getInternalPointOfNoReturn() const;
    void setInternalPointOfNoReturn(QString *value);

    QString *getExternalPointOfNoReturn() const;
    void setExternalPointOfNoReturn(QString *value);

    QString *getDarkestHour() const;
    void setDarkestHour(QString *value);

    QString *getTurningPoint() const;
    void setTurningPoint(QString *value);

signals:

public slots:
};

#endif // NOVELMIDDLE_H
