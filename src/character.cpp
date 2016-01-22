#include "character.h"

const QString Character::J_NAME = "name",
    Character::J_NICKNAME = "nickname",
    Character::J_LABEL = "label",
    Character::J_HEADSHOT = "headshot",
    Character::J_COLOR = "color",
    Character::J_SCENES = "scenes";

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

    character["id"] = this->getId();

    return character;
}

Character *Character::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QString name = QString(), nickname = QString(), label = QString();
    QImage headshot = QImage();
    QColor color = QColor();

    QString headshotBuffer = QString();

    QJsonValue vName = object.value(J_NAME),
            vNickname = object.value(J_NICKNAME),
            vLabel = object.value(J_LABEL),
            vHeadshot = object.value(J_HEADSHOT),
            vColor = object.value(J_COLOR),
            vScenes = object.value(J_SCENES);

    if (!vName.isUndefined() && vName.isString())
        name = vName.toString();

    if (!vNickname.isUndefined() && vNickname.isString())
        nickname = vNickname.toString();

    if (!vLabel.isUndefined() && vLabel.isString())
        label = vLabel.toString();

    // TODO: deserialize headshot.
//    if (!vHeadshot.isNull() && vHeadshot.isString()){
//        headshotBuffer = QBuffer(vName.toString().constData());
//    }

    if (!vColor.isUndefined() && vColor.isArray())
        color = QColor(vColor.toArray().at(0).toInt(),
                vColor.toArray().at(1).toInt(),
                vColor.toArray().at(2).toInt());

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
