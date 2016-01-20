#include "sceneitemmodel.h"

SceneItemModel::SceneItemModel(QList<Scene *> scenes, QObject *parent)
    : QAbstractListModel(parent)
{
    this->mScenes = scenes;
}

QList<Scene *> SceneItemModel::getScenes() const
{
    return mScenes;
}

void SceneItemModel::setScenes(const QList<Scene *> &scenes)
{
    mScenes = scenes;
}

int SceneItemModel::rowCount(const QModelIndex &parent) const
{
    return this->mScenes.size();
}

QVariant SceneItemModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
        return QVariant();
    if (index.row() < 0 || index.row() > this->mScenes.size())
        return QVariant();
    if (role == Qt::DisplayRole)
         return this->mScenes.value(index.row())->getHeadline();
    return QVariant();
}

QVariant SceneItemModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const
{
    return QString("Scene");
}
