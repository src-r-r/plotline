#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "completable.h"
#include "character.h"
#include "novel.h"
#include "plotline.h"

class Novel;
class Character;
class Plotline;

class Scene : public Completable, public Serializable
{
    Q_OBJECT
private:

    QString mHeadline,
        mAction;
    QList<Character *> mCharacters;
    QList<Character *> mPovCharacters;
    Plotline *mPlotline;
    Novel *mNovel;

    static const QString JSON_HEADLINE,
        JSON_ACTION,
        JSON_CHARACTERS,
        JSON_POV_CHARACTERS,
        JSON_PLOTLINE;

public:
    explicit Scene(QObject *parent=0);
    explicit Scene(const QString &mHeadline, const QString &mAction,
                   Novel *novel = 0, Plotline *plotline = 0,
                   int id = -1, QObject *parent = 0);

    QString headline() const;
    void setHeadline(const QString &mHeadline);

    QString action() const;
    void setAction(const QString &value);

    void setCharacters(const QList<Character *> &mCharacters);
    void addCharacter(Character *character);
    void addCharacter(const int id);
    void removeCharacter(Character *character);
    void removeCharacter(const int id);
    QList<Character *> getCharacters() const;

    void setPointsOfView(const QList<Character *> &mCharacters);
    QList<Character *> getPointsOfView() const;

    Novel *getNovel() const;
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Scene *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Scene *> deserialize(Novel *novel, const QJsonArray &object);

    Plotline *plotline() const;
    void setPlotline(Plotline *plotline);

signals:

public slots:
};

#endif // SCENE_H
