#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "completable.h"
#include "character.h"
#include "novel.h"

class Novel;
class Character;

class Scene : public Completable, public Serializable
{
    Q_OBJECT
private:

    QString mHeadline,
        mAction;
    QList<Character *> mCharacters;
    QList<Character *> mPovCharacters;
    Novel *mNovel;

    static const QString JSON_HEADLINE,
        JSON_ACTION,
        JSON_CHARACTERS,
        JSON_POV_CHARACTERS;

public:
    explicit Scene(QObject *parent=0);
    explicit Scene(const QString &mHeadline, const QString &mAction,
                   Novel *novel = 0, int id = -1, QObject *parent = 0);

    QString getHeadline() const;
    void setHeadline(const QString &mHeadline);

    QString getAction() const;
    void setAction(const QString &value);

    void setCharacters(const QList<Character *> &mCharacters);
    void addCharacter(Character *character);
    QList<Character *> getCharacters() const;

    void setPointsOfView(const QList<Character *> &mCharacters);
    QList<Character *> getPointsOfView() const;

    Novel *getNovel() const;
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Scene *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Scene *> deserialize(Novel *novel, const QJsonArray &object);

signals:

public slots:
};

#endif // SCENE_H
