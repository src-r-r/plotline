#include "author.h"

const QString Author::J_NAME = "name",
    Author::J_PENNAME = "penName",
    Author::J_EMAIL = "email",
    Author::J_ADDRESS = "address",
    Author::J_PHONE = "phone";

Author::Author(const QString &name, const QString &penName,
               const QString &email, const QString &address,
               const QString &phone, Novel *novel, int id, QObject *parent)
    : QObject(parent), Serializable(id)
{
    mName = name;
    mPenName = penName;
    mEmail = email;
    mAddress = address;
    mPhone = phone;
    mNovel = novel;
}

QJsonObject Author::serialize() const
{
    QJsonObject obj;

    obj[JSON_ID] = id();
    obj[J_NAME] = mName;
    obj[J_PENNAME] = mPenName;
    obj[J_EMAIL] = mEmail;
    obj[J_ADDRESS] = mAddress;
    obj[J_PHONE] = mPhone;

    return obj;
}

Author *Author::deserialize(Novel *novel, const QJsonObject &object)
{
    return new Author(object.value(J_NAME).toString(),
                      object.value(J_PENNAME).toString(),
                      object.value(J_EMAIL).toString(),
                      object.value(J_ADDRESS).toString(),
                      object.value(J_PHONE).toString(),
                      novel,
                      object.value(JSON_ID).toInt());
}

QString Author::name() const
{
    return mName;
}

void Author::setName(const QString &name)
{
    mName = name;
}

QString Author::penName() const
{
    return mPenName;
}

void Author::setPenName(const QString &penName)
{
    mPenName = penName;
}

QString Author::email() const
{
    return mEmail;
}

void Author::setEmail(const QString &email)
{
    mEmail = email;
}

QString Author::address() const
{
    return mAddress;
}

void Author::setAddress(const QString &address)
{
    mAddress = address;
}

QString Author::phone() const
{
    return mPhone;
}

void Author::setPhone(const QString &phone)
{
    mPhone = phone;
}

Novel *Author::novel() const
{
    return mNovel;
}

void Author::setNovel(Novel *novel)
{
    mNovel = novel;
}

