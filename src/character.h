#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <bitset>
#include <QImage>
#include <QColor>

class Character : public QObject
{
    Q_OBJECT

private:

    QString mName,
        mNickname,
        mLabel;
    QImage mHeadshot;
    QColor mColor;

public:
    explicit Character(const QString &mName,
                       const QString &mNickname = QString(),
                       const QString &mLabel = QString(),
                       const QImage &mHeadshot = QImage(),
                       const QColor &mColor = QColor(),
                       QObject *parent = 0);
    Character(const Character &c);

    QString getName() const;

    QString getNickname() const;

    QString getLabel() const;

    QImage getHeadshot() const;
    void setHeadshot(const QImage &value);

    QColor getColor() const;
    void setColor(const QColor &value);

signals:

public slots:
    void setName(const QString &value);
    void setNickname(const QString &value);
    void setLabel(const QString &value);
};

#endif // CHARACTER_H
