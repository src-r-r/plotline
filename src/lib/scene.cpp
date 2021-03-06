#include "scene.h"

const QString Scene::JSON_HEADLINE = QString("headline"),
    Scene::JSON_ACTION = QString("action"),
    Scene::JSON_CHARACTERS = QString("characters"),
    Scene::JSON_POV_CHARACTERS = QString("povCharacters"),
    Scene::JSON_PLOTLINE = QString("plotline");

Novel *Scene::getNovel() const
{
    return mNovel;
}

void Scene::setNovel(Novel *novel)
{
    mNovel = novel;
}

Plotline *Scene::plotline() const
{
    return mPlotline;
}

void Scene::setPlotline(Plotline *plotline)
{
    mPlotline = plotline;
}

Scene::Scene(QObject *parent) : Completable(parent), Serializable()
{
    
}

Scene::Scene(const QString &headline, const QString &action, Novel *novel,
             Plotline *plotline, const QUuid &id, QObject *parent) : Completable(parent),
    Serializable(id)
{
    this->mHeadline = headline;
    this->mAction = action;
    this->mNovel = novel;
    mPlotline = plotline;
}

QString Scene::headline() const
{
    return mHeadline;
}

void Scene::setHeadline(const QString &headline)
{
    this->mHeadline = headline;
}

QString Scene::action() const
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

void Scene::addCharacter(const QUuid &id)
{
    mCharacters.append(mNovel->character(id));
}

void Scene::removeCharacter(Character *character)
{
    mCharacters.removeAll(character);
}

void Scene::removeCharacter(const QUuid &id)
{
    mCharacters.removeAll(mNovel->character(id));
}

QJsonObject Scene::serialize() const
{
    QJsonObject scene = QJsonObject();

    // When adding the character list, just add the character
    // IDs to avoid redundancy.

    QJsonArray jCharacters = QJsonArray(),
            jPovCharacters = QJsonArray();

    for (Character *c : mCharacters)
        jCharacters.append(c->id().toString());

    for (Character *c : mPovCharacters)
        jPovCharacters.append(c->id().toString());

    scene[JSON_HEADLINE] = mHeadline;
    scene[JSON_ACTION] = mAction;
    scene[JSON_CHARACTERS] = jCharacters;
    scene[JSON_POV_CHARACTERS] = jPovCharacters;
    scene[JSON_ID] = id().toString();
    if (mPlotline)
        scene.insert(JSON_PLOTLINE, QJsonValue(mPlotline->id().toString()));

    return scene;
}

Scene *Scene::deserialize(Novel *novel, const QJsonObject &object)
{

    QString headline = QString(), action = QString();
    Plotline *plotline = 0;

    QList<Character *> characters = QList<Character *>(),
            povCharacters = QList<Character *>();

    QStringList missing = QStringList();

    if (object.contains(JSON_HEADLINE))
        headline = object[JSON_HEADLINE].toString();
    else
        missing.append(JSON_HEADLINE);

    if (object.contains(JSON_ACTION))
        action = object[JSON_ACTION].toString();
    else
        missing.append(JSON_ACTION);

    if (object.contains(JSON_CHARACTERS))
        for (QJsonValue val : object[JSON_CHARACTERS].toArray())
          characters << novel->character(QUuid(val.toString()));
    else
        missing.append(JSON_CHARACTERS);

    if (object.contains(JSON_POV_CHARACTERS))
        for (QJsonValue val : object[JSON_POV_CHARACTERS].toArray())
          povCharacters.append(novel->character(QUuid(val.toString())));

    if (object.contains(JSON_PLOTLINE))
        plotline = novel->plotline(QUuid(object[JSON_PLOTLINE].toString()));

    if (!missing.empty())
        qWarning() << "Scene missing the following fields: "
                   << missing.join(",");

    QUuid id = QUuid(object[JSON_ID].toString());
    qDebug() << "[+] deserialize scene with id" << id;
    Scene *scene = new Scene(headline, action, novel, plotline, id);
    scene->setCharacters(characters);
    scene->setPointsOfView(povCharacters);
    return scene;
}

QList<Scene *> Scene::deserialize(Novel *novel, const QJsonArray &object)
{
    QList<Scene *> scenes;
    for (QJsonValue obj : object){
        if (obj.isObject())
            scenes << Scene::deserialize(novel, obj.toObject());
        else
            scenes << novel->scene(QUuid(obj.toString()));
    }

    return scenes;
}
