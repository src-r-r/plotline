#include "character.h"

const QString Character::J_NAME = QString("name"),
    Character::J_NICKNAME = QString("nickname"),
    Character::J_LABEL = QString("label"),
    Character::J_HEADSHOT = QString("headshot"),
    Character::J_COLOR = QString("color"),
    Character::J_IS_ARCHIVED = "isArchived";

Character::Character(const QString &name, const QString &nickname,
                     const QString &label, const QImage &headshot,
                     const QColor &color,
                     const bool isArchived,
                     Novel *novel,
                     int id,
                     QObject *parent) : QObject(parent), Serializable(id)
{
    this->mName = name;
    this->mNickname = nickname;
    this->mColor = color;
    this->mHeadshot = headshot;
    this->mNovel = novel;
    this->mIsArchived = isArchived;

    // If a label is not given, make the label the name parts in title-case,
    // so the name "John Doe" will appear as "JoDo"
    if (label == 0){
        this->mLabel = Character::generateLabel(name);
    } else {
        this->mLabel = label;
    }
}

Character::~Character()
{
    // nothing to delete
}

QString Character::generateLabel(const QString &name)
{
    QString label = QString();
    QStringList nameParts = name.split(QChar(' '));
    for (QString namePart : nameParts)
        label.append(namePart[0].toUpper()).append(namePart[1].toLower());
    return label;
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
    QJsonArray scenes = QJsonArray();

    character[JSON_ID] = this->id();
    character[J_NAME] = mName;
    character[J_NICKNAME] = mNickname;
    character[J_LABEL] = mLabel;
    character[J_HEADSHOT] = jsonValFromImage(mHeadshot);
    character[J_COLOR] = mColor.name();
    character[J_IS_ARCHIVED] = QJsonValue(mIsArchived);

    return character;
}

Character *Character::deserialize(Novel *novel, const QJsonObject &object)
{
    int id = Serializable::deserialize(object);

    QString name = QString(), nickname = QString(), label = QString();
    QImage headshot = QImage();
    QColor color = QColor();
    bool isArchived = false;

    if (object.contains(J_NAME))
        name = object[J_NAME].toString();

    if (object.contains(J_NICKNAME))
        nickname = object[J_NICKNAME].toString();

    if (object.contains(J_LABEL))
        label = object[J_LABEL].toString();

    if (object.contains(J_COLOR))
        color = QColor(object[J_COLOR].toString());

    if (object.contains(J_IS_ARCHIVED))
        isArchived = object[J_IS_ARCHIVED].toBool();

    else
        qWarning() << "Character color not set";

    if (object.contains(J_HEADSHOT))
        headshot = imageFrom(object[J_HEADSHOT]);

    Character *character = new Character(name, nickname, label,
                                         headshot, color, isArchived,
                                         novel, id);
    return character;
}

QList<Character *> Character::deserialize(Novel *novel, const QJsonArray &object)
{
    QList<Character *> characters = QList<Character *>();
    for (QJsonValue obj : object)
        if (obj.isObject())
            characters << Character::deserialize(novel, obj.toObject());
    return characters;
}

bool Character::getIsArchived() const
{
    return mIsArchived;
}

void Character::setIsArchived(bool isArchived)
{
    mIsArchived = isArchived;
}

QString Character::name() const
{
    return mName;
}

void Character::setName(const QString &value)
{
    mName = value;
}

QString Character::nickname() const
{
    return mNickname;
}

void Character::setNickname(const QString &value)
{
    mNickname = value;
}

QString Character::label() const
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

QColor Character::color() const
{
    return mColor;
}

void Character::setColor(const QColor &value)
{
    mColor = value;
}
