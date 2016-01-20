#ifndef CHAPTER_H
#define CHAPTER_H

#include <QObject>
#include "completable.h"
#include "scene.h"

class Chapter : public Completable
{
private:
    QString mTitle;
    QString mContent;
    QList<Scene *> mScenes;

    Q_OBJECT
public:
    explicit Chapter(const QString &title = QString(),
                     const QString &content = QString(),
                     const QList<Scene *> &scenes = QList<Scene *>(),
                     QObject *parent = 0);

    QString getTitle() const;
    QString getContent() const;

    QList<Scene *> getScenes() const;
    void setScenes(const QList<Scene *> &scenes);

signals:

public slots:
    void setTitle(const QString &title);
    void setContent(const QString &content);
};

#endif // CHAPTER_H
