#include "sceneitemmodel.h"

SceneItemModel::SceneItemModel(Novel *novel, QObject *parent)
    : QAbstractListModel(parent)
{
    mNovel = novel;

    QList<Scene *> scenes = mNovel->scenes();
    insertRows(0, scenes.count());
    QModelIndex index;

    for (int i = 0; i < scenes.count(); ++i){
        index = createIndex(i, 0);
        setData(index, scenes[i]->headline());
        setData(index, scenes[i]->id(), Qt::UserRole);
        if (scenes[i]->plotline()){
            QBrush brush = QBrush(scenes[i]->plotline()->getColor());
            setData(index, brush, Qt::BackgroundRole);
        }
    }
}

int SceneItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->scenes().count();
}

QVariant SceneItemModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    if (!index.isValid()) {
        qWarning() << "Index" << index << "not valid.";
        return QVariant();
    }

    QList<Scene *> scenes = mNovel->scenes();

    if (row > scenes.count()){
        qWarning() << "row" << row << " > scene count ("
                   << scenes.count() << ")";
        return QVariant();
    }

    Scene *scene = scenes[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return scene->headline();
    if (scene->plotline() && role == Qt::BackgroundRole)
        return scene->plotline()->getColor();

//    qWarning() << "Scene::data - returning general QVariant";
    return QVariant();
}

QVariant SceneItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);

    return QString("Scene");
}

bool SceneItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row > rowCount() || row < 0){
        qWarning() << "Invalid row" << row;
        return false;
    }

    beginInsertRows(parent, row, row+(count-1));

    endInsertRows();

    return true;
}

bool SceneItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int end = row + (count-1);

    if (row > rowCount()-1 || row < 0){
        qWarning() << "Could not delete from row" << row;
        return false;
    }

    if (end > rowCount()-1)
        end = rowCount()-1;
    beginRemoveRows(parent, row, end);

    endRemoveRows();
    return true;
}

Novel *SceneItemModel::novel() const
{
    return mNovel;
}

void SceneItemModel::setNovel(Novel *novel)
{
    mNovel = novel;
}
