#include "character.h"

const QString Character::J_NAME = QString("name"),
    Character::J_NICKNAME = QString("nickname"),
    Character::J_LABEL = QString("label"),
    Character::J_HEADSHOT = QString("headshot"),
    Character::J_COLOR = QString("color"),
    Character::J_SCENES = QString("scenes");

Character::Character(const QString &name, const QString &nickname,
                     const QString &label, const QImage &headshot,
                     const QColor &color,
                     const QList<Scene *> scenes,
                     Novel *novel,
                     int id,
                     QObject *parent) : QObject(parent), Serializable(id)
{
    this->mName = name;
    this->mNickname = nickname;
    this->mColor = color;
    this->mHeadshot = headshot;
    this->mScenes = scenes;
    this->mNovel = novel;
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

QList<Scene *> Character::getScenes() const
{
    return mScenes;
}

void Character::setScenes(const QList<Scene *> &scenes)
{
    mScenes = scenes;
}

Novel *Character::getNovel() const
{
    return mNovel;
}

void Character::setNovel(Novel *novel)
{
    mNovel = novel;
}

QJsonObject Character::serialize() const
{
    QJsonObject character = QJsonObject();

    QJsonObject color = QJsonObject();
    color["red"] = mColor.red();
    color["green"] = mColor.green();
    color["blue"] = mColor.blue();

    character["id"] = this->getId();
    character[J_NAME] = mName;
    character[J_NICKNAME] = mNickname;
    character[J_LABEL] = mLabel;
    character[J_COLOR] = color;

    return character;
}

Character *Character::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QString name = QString(), nickname = QString(), label = QString();
    QImage headshot = QImage();
    QColor color = QColor();
    QList<Scene *> scenes = QList<Scene *>();

    QString headshotBuffer = QString();

    if (object.contains(J_NAME))
        name = object[J_NAME].toString();

    if (object.contains(J_NICKNAME))
        nickname = object[J_NICKNAME].toString();

    if (object.contains(J_LABEL))
        label = object[J_LABEL].toString();

    if (object.contains(J_COLOR))
        color = QColor(object[J_COLOR].toObject()["red"].toInt(),
                object[J_COLOR].toObject()["green"].toInt(),
                object[J_COLOR].toObject()["blue"].toInt());

    // TODO: deserialize headshot.
//    if (!vHeadshot.isNull() && vHeadshot.isString()){
//        headshotBuffer = QBuffer(vName.toString().constData());
//    }

    Character *character = new Character(name, nickname, label,
                                         headshot, color, QList<Scene *>(),
                                         novel, id);
    return character;
}

QList<Character *> Character::deserialize(Novel *novel, const QJsonArray &object)
{
    QList<Character *> characters = QList<Character *>();
    for (QJsonValue obj : object)
        if (obj.isObject())
            characters.append(Character::deserialize(novel, obj.toObject()));
    return characters;
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
