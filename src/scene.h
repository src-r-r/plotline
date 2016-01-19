#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "completable.h"
#include "character.h"

class Scene : public Completable
{
    Q_OBJECT
private:
    QString headline,
        action;
    QList<Character> mCharacters;
    QList<Character> mPovCharacters;

public:
    explicit Scene(QObject *parent=0);
    explicit Scene(const QString &headline, const QString &action, QObject *parent = 0);

    QString getHeadline() const;
    void setHeadline(const QString &headline);

    QString getAction() const;
    void setAction(const QString &value);

    void setCharacters(const QList<Character> &mCharacters);
    QList<Character> getCharacters() const;

    void setPointsOfView(const QList<Character> &mCharacters);
    QList<Character> getPointsOfView() const;

    Scene(const Scene &s);

signals:

public slots:
};

#endif // SCENE_H
