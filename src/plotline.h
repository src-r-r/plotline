#ifndef PLOTLINE_H
#define PLOTLINE_H

#include <QObject>
#include <QVector>
#include "character.h"
#include "scene.h"

class Plotline : public QObject
{
    Q_OBJECT

private:

    QList<Character> mCharacters;
    QList<Scene> mScenes;
    QString mSynopsis;
    QColor mColor;

public:
    explicit Plotline(const QString &mSynopsis,
                      const QList<Scene> &mScenes = QList<Scene>(),
                      const QList<Character> &mCharacters = QList<Character>(),
                      const QColor &mColor = QColor(),
                      QObject *parent = 0);

    QString getSynopsis() const;
    void setSynopsis(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    QList<Character> getCharacters() const;
    void setCharacters(const QList<Character> &mCharacters);

    QList<Scene> getScenes() const;
    void setScenes(const QList<Scene> &mScenes);

signals:

public slots:
};

#endif // PLOTLINE_H
