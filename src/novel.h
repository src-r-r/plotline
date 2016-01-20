#ifndef NOVEL_H
#define NOVEL_H

#include <QObject>
#include <stdlib.h>
#include "chapter.h"

class Novel : public QObject
{
    Q_OBJECT

public:
    enum Tense {
        Past, Present, Future
    };

    enum PointOfView {
        FirstPersonSingular, SecondPersonSingular, ThirdPersonSingular,
        FirstPersonPlural, SecondPersonPlural, ThirdPersonPlural,
    };

    explicit Novel(const QString &workingTitle,
                   const QString &genre = QString(),
                   const QString &setting = QString(),
                   const Novel::Tense tense = Past,
                   const Novel::PointOfView pov = ThirdPersonSingular,
                   const QList<Scene *> scenes = QList<Scene *>(),
                   const QList<Chapter *> chapters = QList<Chapter *>(),
                   QObject *parent = 0);

    QString getWorkingTitle() const;

    QString getGenre() const;

    Novel::Tense getTense() const;
    void setTense(const Novel::Tense tense);

    QString getSetting() const;

    QList<Scene *> getScenes() const;
    void setScenes(const QList<Scene *> &value);

    QList<Chapter *> getChapters() const;
    void setChapters(const QList<Chapter *> &value);

    Novel::PointOfView getPointOfView() const;
    void setPointOfView(const Novel::PointOfView &pointOfView);

private:

    QString workingTitle,
    genre,
    setting;
    Novel::Tense mTense;
    Novel::PointOfView mPointOfView;
    QList<Scene *> mScenes;
    QList<Chapter *> mChapters;

signals:

public slots:
    void setWorkingTitle(const QString &value);
    void setGenre(const QString &value);
    void setSetting(const QString &value);

};

#endif // NOVEL_H
