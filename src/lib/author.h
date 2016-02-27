#ifndef AUTHOR_H
#define AUTHOR_H

#include <QObject>
#include "serializable.h"

class Novel;

class Author : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Author(const QString &name = QString(),
                    const QString &penName = QString(),
                    const QString &email = QString(),
                    const QString &address = QString(),
                    const QString &phone = QString(),
                    Novel *novel = 0,
                    int id = 0,
                    QObject *parent = 0);

    QJsonObject serialize() const;
    static Author *deserialize(Novel *novel, const QJsonObject &object);

    QString name() const;
    void setName(const QString &name);

    QString penName() const;
    void setPenName(const QString &penName);

    QString email() const;
    void setEmail(const QString &email);

    QString address() const;
    void setAddress(const QString &address);

    QString phone() const;
    void setPhone(const QString &phone);

    Novel *novel() const;
    void setNovel(Novel *novel);

private:
    QString mName, mPenName, mEmail, mAddress, mPhone;
    Novel *mNovel;

    static const QString J_NAME, J_PENNAME, J_EMAIL, J_ADDRESS, J_PHONE;

signals:

public slots:
};

#include "novel.h"

#endif // AUTHOR_H
