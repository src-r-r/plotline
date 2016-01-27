#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <bitset>
#include <QImage>
#include <QPixmap>
#include <QColor>
#include "serializable.h"
#include "scene.h"
#include "utils.h"

class Scene;
class Novel;

class Character : public QObject, public Serializable
{
    Q_OBJECT

private:

    QString mName,
        mNickname,
        mLabel;
    QImage mHeadshot;
    QColor mColor;
    bool mIsArchived;

    static const QString J_NAME,
        J_NICKNAME,
        J_LABEL,
        J_HEADSHOT,
        J_COLOR,
        J_IS_ARCHIVED;

    Novel *mNovel;

public:
    explicit Character(const QString &name,
                       const QString &nickname = QString(),
                       const QString &label = QString(),
                       const QImage &headshot = QImage(),
                       const QColor &color = QColor(),
                       bool isArchived = false,
                       Novel *novel = 0,
                       int id = -1,
                       QObject *parent = 0);
    ~Character();

    static QString generateLabel(const QString &name);

    QString getName() const;

    QString getNickname() const;

    QString getLabel() const;

    QImage getHeadshot() const;
    void setHeadshot(const QImage &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    Novel *getNovel() const;
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Character *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Character *> deserialize(Novel *novel, const QJsonArray &object);

    bool getIsArchived() const;
    void setIsArchived(bool isArchived);

signals:

public slots:
    void setName(const QString &value);
    void setNickname(const QString &value);
    void setLabel(const QString &value);
};

#endif // CHARACTER_H
