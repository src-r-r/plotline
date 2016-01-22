#ifndef CHAPTER_H
#define CHAPTER_H

#include <QObject>
#include "completable.h"
#include "scene.h"

#include "serializable.h"

class Novel;
class Scene;

class Chapter : public Completable, public Serializable
{
private:
    QString mTitle;
    QString mContent;
    QList<Scene *> mScenes;
    Novel *mNovel;

    static const QString JSON_TITLE, JSON_CONTENT,
        JSON_SCENES;

    Q_OBJECT
public:
    explicit Chapter(const QString &title = QString(),
                     const QString &content = QString(),
                     const QList<Scene *> &scenes = QList<Scene *>(),
                     Novel *novel = 0,
                     int id = -1,
                     QObject *parent = 0);

    QString getTitle() const;
    QString getContent() const;

    QList<Scene *> getScenes() const;
    void setScenes(const QList<Scene *> &scenes);

    Novel *getNovel() const;
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Chapter *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Chapter *> deserialize(Novel *novel, const QJsonArray &object);

signals:

public slots:
    void setTitle(const QString &title);
    void setContent(const QString &content);
};

#endif // CHAPTER_H
