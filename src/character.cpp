#include "character.h"



Character::Character(const QString &name, const QString &nickname,
                     const QString &label, const QImage &headshot,
                     const QColor &color, QObject *parent) : QObject(parent)
{
    this->mName = name;
    this->mNickname = nickname;
    this->mColor = color;
    this->mHeadshot = headshot;
    QString lbl = QString();

    // If a label is not given, make the label the name parts in title-case,
    // so the name "John Doe" will appear as "JoDo"
    if (label == 0){
        QStringList nameParts = name.split(QChar(' '));
        for (QString namePart : nameParts)
            lbl.append(namePart[0].toUpper()).append(namePart[1].toLower());
        this->mLabel = lbl;
    } else {
        this->mLabel = label;
    }
}

QString Character::getName() const
{
    return mName;
}

void Character::setName(const QString &value)
{
    mName = value;
}

QString Character::getNickname() const
{
    return mNickname;
}

void Character::setNickname(const QString &value)
{
    mNickname = value;
}

QString Character::getLabel() const
{
    return mLabel;
}

void Character::setLabel(const QString &value)
{
    mLabel = value;
}

QImage Character::getHeadshot() const
{
    return mHeadshot;
}

void Character::setHeadshot(const QImage &value)
{
    mHeadshot = value;
}

QColor Character::getColor() const
{
    return mColor;
}

void Character::setColor(const QColor &value)
{
    mColor = value;
}
