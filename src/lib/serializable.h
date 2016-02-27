#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QtCore>
#include <QtGlobal>

class Serializable
{
private:

    static int sCurrentId;
    // Yes, this is kind of awkard (this will generate a new ID for every
    // SERIALIZABLE instance instead of every subclass instance, but this
    // will take the work-load off the subclasses.

    QUuid mId;
protected:

    static const QString JSON_ID;

public:
    Serializable(QUuid id = QUuid());

    virtual QJsonObject serialize() const = 0;
    static QUuid deserialize(const QJsonObject &object);

    QUuid id() const;
    void setId(const QUuid id);
};

#endif // SERIALIZABLE_H
