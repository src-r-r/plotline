#include "scene.h"

const QString Scene::JSON_HEADLINE = QString("headline"),
    Scene::JSON_ACTION = QString("action"),
    Scene::JSON_CHARACTERS = QString("characters"),
    Scene::JSON_POV_CHARACTERS = QString("povCharacters");

Novel *Scene::getNovel() const
{
    return mNovel;
}

void Scene::setNovel(Novel *novel)
{
    mNovel = novel;
}

Scene::Scene(QObject *parent) : Completable(parent), Serializable()
{
    
}

Scene::Scene(const QString &headline, const QString &action,
             Novel *novel, int id, QObject *parent) : Completable(parent),
    Serializable(id)
{
    this->mHeadline = headline;
    this->mAction = action;
    this->mNovel = novel;
}

QString Scene::getHeadline() const
{
    return mHeadline;
}

void Scene::setHeadline(const QString &headline)
{
    this->mHeadline = headline;
}

QString Scene::getAction() const
{
    return mAction;
}

void Scene::setAction(const QString &action)
{
    this->mAction = action;
}

QList<Character *> Scene::getCharacters() const
{
    return this->mCharacters;
}

void Scene::setPointsOfView(const QList<Character *> &characters)
{
    this->mPovCharacters = characters;
}

QList<Character *> Scene::getPointsOfView() const
{
    return this->mPovCharacters;
}

void Scene::setCharacters(const QList<Character *> &characters)
{
    this->mCharacters = characters;
}

QJsonObject Scene::serialize() const
{
    QJsonObject scene = QJsonObject();

    // When adding the character list, just add the character
    // IDs to avoid redundancy.

    QJsonArray jCharacters = QJsonArray(),
            jPovCharacters = QJsonArray();

    for (Character *c : mCharacters)
        jCharacters.append(c->getId());

    for (Character *c : mPovCharacters)
        jPovCharacters.append(c->getId());

    scene.insert(JSON_HEADLINE, mHeadline);
    scene.insert(JSON_ACTION, mAction);
    scene.insert(JSON_CHARACTERS, jCharacters);
    scene.insert(JSON_POV_CHARACTERS, jPovCharacters);

    return scene;
}

Scene *Scene::deserialize(Novel *novel, const QJsonObject &object)
{
    QJsonValue jHeadline = object.value(JSON_HEADLINE),
            jAction = object.value(JSON_ACTION);
    QJsonValue jCharacters = object.value(JSON_CHARACTERS),
            jPovCharacters = object.value(JSON_POV_CHARACTERS);

    QString headline = QString(), action = QString();

    QList<Character *> characters = QList<Character *>(),
            povCharacters = QList<Character *>();

    if (!jHeadline.isNull() && jHeadline.isString())
        headline = object.value(JSON_HEADLINE).toString();
    if (!jAction.isNull() && jAction.isString())
        action = object.value(JSON_ACTION).toString();

    if ((!jCharacters.isNull()) && jCharacters.isArray()){
        for (QJsonValue jCharId : jCharacters.toArray()){
            Character *c = novel->getCharacter(jCharId.toInt());
            if (c != 0)
                characters.append(c);
        }
    }

    if (!jPovCharacters.isNull() && jPovCharacters.isArray()){
        for (QJsonValue jCharId : jPovCharacters.toArray()){
            Character *c = novel->getCharacter(jCharId.toInt());
            if (c != 0)
                povCharacters.append(c);
        }
    }

    Scene *scene = new Scene(headline, action, novel,
                             Serializable::deserialize(object));
    scene->setCharacters(characters);
    scene->setPointsOfView(povCharacters);
    return scene;
}

QList<Scene *> Scene::deserialize(Novel *novel, const QJsonArray &object)
{
    QList<Scene *> scenes;
    for (QJsonValue obj : object)
        if (obj.isObject())
            scenes.append(Scene::deserialize(novel, obj.toObject()));

    return scenes;
}
