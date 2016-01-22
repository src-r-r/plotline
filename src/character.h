#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <bitset>
#include <QImage>
#include <QColor>
#include "serializable.h"

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

    static const QString J_NAME,
        J_NICKNAME,
        J_LABEL,
        J_HEADSHOT,
        J_COLOR,
        J_SCENES;

    QList<Scene *> mScenes;
    Novel *mNovel;

public:
    explicit Character(const QString &mName,
                       const QString &mNickname = QString(),
                       const QString &mLabel = QString(),
                       const QImage &mHeadshot = QImage(),
                       const QColor &mColor = QColor(),
                       const QList<Scene *> scenes = QList<Scene *>(),
                       Novel *novel = 0,
                       int id = -1,
                       QObject *parent = 0);

    QString getName() const;

    QString getNickname() const;

    QString getLabel() const;

    QImage getHeadshot() const;
    void setHeadshot(const QImage &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    QList<Scene *> getScenes() const;
    void setScenes(const QList<Scene *> &scenes);

    Novel *getNovel() const;
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Character *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Character *> deserialize(Novel *novel, const QJsonArray &object);

signals:

public slots:
    void setName(const QString &value);
    void setNickname(const QString &value);
    void setLabel(const QString &value);
};

#endif // CHARACTER_H
