#ifndef PLOTLINE_H
#define PLOTLINE_H

#include <QObject>
#include <QVector>
#include "character.h"
#include "scene.h"
#include "serializable.h"

class Novel;
class Character;
class Scene;

class Plotline : public QObject, public Serializable
{
    Q_OBJECT

private:

    static const QString J_CHARACTERS,
        J_SCENES,
        J_SYNOPSIS,
        J_COLOR;

    QList<Character *> mCharacters;
    QList<Scene *> mScenes;
    QString mSynopsis;
    QColor mColor;
    Novel *mNovel;

public:
    explicit Plotline(const QString &mSynopsis,
                      const QList<Scene *> &mScenes = QList<Scene *>(),
                      const QList<Character *> &mCharacters = QList<Character *>(),
                      const QColor &mColor = QColor(),
                      Novel *novel = 0,
                      int id = -1,
                      QObject *parent = 0);

    QString getSynopsis() const;
    void setSynopsis(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    QList<Character *> getCharacters() const;
    void setCharacters(const QList<Character *> &characters);

    QList<Scene *> getScenes() const;
    void setScenes(const QList<Scene *> &scenes);

    Novel *getNovel();
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Plotline *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Plotline *> deserialize(Novel *novel, const QJsonArray &object);

signals:

public slots:
};

#endif // PLOTLINE_H
