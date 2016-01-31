#include "serializable.h"

const QString Serializable::JSON_ID = QString("id");

int Serializable::sCurrentId = 0;

Serializable::Serializable(int id)
{
    if (id < 0){
        ++sCurrentId;
        this->mId = sCurrentId;
    } else {
        this->mId = id;
    }
}

int Serializable::deserialize(const QJsonObject &object)
{
    QJsonValue value = object.value(JSON_ID);
    if (!value.isNull())
        return value.toInt();
    return -1;
}

int Serializable::id() const
{
    return mId;
}

void Serializable::setId(const int id)
{
    mId = id;
}

