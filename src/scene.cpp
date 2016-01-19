#include "scene.h"

Scene::Scene(QObject *parent) : Completable(parent){

}

Scene::Scene(const QString &headline, const QString &action, QObject *parent) : Completable(parent)
{
    this->headline = headline;
    this->action = action;
}

QString Scene::getHeadline() const
{
    return headline;
}

void Scene::setHeadline(const QString &headline)
{
    this->headline = headline;
}

QString Scene::getAction() const
{
    return action;
}

void Scene::setAction(const QString &action)
{
    this->action = action;
}

QList<Character> Scene::getCharacters() const
{
    return this->mCharacters;
}

void Scene::setPointsOfView(const QList<Character> &characters)
{
    this->mPovCharacters = characters;
}

QList<Character> Scene::getPointsOfView() const
{
    return this->mPovCharacters;
}

void Scene::setCharacters(const QList<Character> &characters)
{
    this->mCharacters = characters;
}

Scene::Scene(const Scene &s) : Completable(s.parent())
{
    this->headline = s.headline;
    this->mCharacters = s.mCharacters;
    this->mPovCharacters = s.mPovCharacters;
}
