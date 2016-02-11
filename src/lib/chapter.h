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

class Chapter : public QObject, public Serializable
{
private:
    QString mTitle;
    QList<Scene *> mScenes;
    QList<Revision *> mRevisions;
    Novel *mNovel;

    int mCurrentRevision = 0;

    static const QString JSON_TITLE, JSON_REVISIONS,
        JSON_SCENES, JSON_CURRENT_REVISION;

    Q_OBJECT
public:
    explicit Chapter(const QString &title = QString(),
                    const QList<Revision *> &revisions = QList<Revision *>(),
                     const QList<Scene *> &scenes = QList<Scene *>(),
                     Novel *novel = 0,
                     int currentRevision = -1,
                     int id = -1,
                     QObject *parent = 0);
    ~Chapter();

    QString title() const;
    void setTitle(const QString &title);

    QList<Scene *> scenes() const;
    void setScenes(const QList<Scene *> &scenes);

    Novel *novel() const;
    void setNovel(Novel *novel);

    QJsonObject serialize() const;
    static Chapter *deserialize(Novel *novel, const QJsonObject &object);
    static QList<Chapter *> deserialize(Novel *novel, const QJsonArray &object);

    int number();
    QList<Revision *> revisions() const;
    Revision *addRevision();
    void removeRevision(int i);
    int currentRevision() const;
    void setCurrentRevision(int currentRevision);

    QString content(int revision) const;
    QString currentContent() const;
    QString latestContent() const;

signals:

public slots:
};

#endif // CHAPTER_H
