#ifndef CHAPTER_H
#define CHAPTER_H

#include <QObject>
#include "completable.h"
#include "scene.h"
#include "revision.h"

#include "serializable.h"

class Novel;
class Scene;
class Revision;

class Chapter : public QObject, Serializable
{
private:
    QString mTitle;
    QList<Scene *> mScenes;
    QList<Revision *> mRevisions;
    Novel *mNovel;

    static const QString JSON_TITLE, JSON_REVISIONS,
        JSON_SCENES;

    Q_OBJECT
public:
    explicit Chapter(const QString &title = QString(),
                    const QList<Revision *> &revisions = QList<Revision *>(),
                     const QList<Scene *> &scenes = QList<Scene *>(),
                     Novel *novel = 0,
                     int id = -1,
                     QObject *parent = 0);

    QString title() const;
    void setTitle(const QString &title);

    QList<Scene *> getScenes() const;
    void setScenes(const QList<Scene *> &scenes);

    Novel *novel() const;
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Chapter *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Chapter *> deserialize(Novel *novel, const QJsonArray &object);

    QList<Revision *> getRevisions() const;
    void setRevisions(const QList<Revision *> &revisions);

signals:

public slots:
};

#endif // CHAPTER_H
