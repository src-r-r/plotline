#include "serializable.h"

const QString Serializable::JSON_ID = "id";

Serializable::Serializable(QUuid id)
{
    if (id.isNull()){
        mId = QUuid::createUuid();
    } else {
        mId = id;
    }
}

QUuid Serializable::deserialize(const QJsonObject &object)
{
    QJsonValue value = object.value(JSON_ID);
    if (!value.isNull())
        return QUuid(value.toString());
    return QUuid::createUuid();
}

QUuid Serializable::id() const
{
    return mId;
}

void Serializable::setId(const QUuid id)
{
    mId = id;
}

