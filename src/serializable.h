#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QtCore>

class Serializable
{
private:

    static int sCurrentId;
    // Yes, this is kind of awkard (this will generate a new ID for every
    // SERIALIZABLE instance instead of every subclass instance, but this
    // will take the work-load off the subclasses.

    static const QString JSON_ID;
    int mId;

public:
    Serializable(int id = -1);

    virtual QJsonObject serialize() const = 0;
    static int deserialize(const QJsonObject &object);

    int getId() const;
    void setId(const int id);
};

#endif // SERIALIZABLE_H
