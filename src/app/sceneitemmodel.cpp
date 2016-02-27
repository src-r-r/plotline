#include "sceneitemmodel.h"

SceneItemModel::SceneItemModel(Novel *novel, QObject *parent)
    : QAbstractListModel(parent)
{
    mNovel = novel;
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

    QJsonArray characterIds;

    if (role == Qt::ForegroundRole){
        QColor textColor = QColor(0, 0, 0);
        if ((255 / 2) > scene->plotline()->getColor().value())
            textColor = QColor(255, 255, 255);      // White text.
        return QBrush(textColor);
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return scene->headline();
    if (scene->plotline() && role == Qt::BackgroundRole)
        return scene->plotline()->getColor();
    if (role == HeadlineRole)
        return scene->headline();
    if (role == ActionRole)
        return scene->action();
    if (role == PlotlineRole && (scene->plotline() != 0))
        return QVariant(scene->plotline()->id());
    if (role == CharactersRole){
        for(Character *c : scene->getCharacters())
            characterIds << QJsonValue(c->id());
        return characterIds;
    } if (role == PointsOfViewRole) {
        for (Character *c : scene->getPointsOfView())
            characterIds << QJsonValue(c->id());
        return characterIds;
    }

//    qWarning() << "Scene::data - returning general QVariant";
    return QVariant();
}

bool SceneItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    if (row >= mNovel->scenes().count()){
        qWarning() << "set scene data: row" << row << "> novel scene count ("
                   << mNovel->scenes().count() << ")";
        return false;
    } else if (!index.isValid()){
        qWarning() << "set scene data: Invalid index";
        return false;
    }

    Scene *scene = mNovel->scenes()[row];

    QList<Character *> characters;

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        scene->setHeadline(value.toString());
    else if (scene->plotline() && role == Qt::BackgroundRole){
        qWarning() << "set scene data: BackgroundRole is read-only";
        return false;
    }
    else if (role == HeadlineRole)
        scene->setHeadline(value.toString());
    else if (role == ActionRole)
        scene->setAction(value.toString());
    else if (role == PlotlineRole){
        Plotline *p = mNovel->plotline(value.toInt());
        if (!p) qWarning() << "set scene data: Could not find plotline" << value.toInt();
        scene->setPlotline(p);
    }else if (role == CharactersRole){
        for (QJsonValue val : value.toJsonArray())
            characters << mNovel->character(val.toInt());
        scene->setCharacters(characters);
    } else if (role == PointsOfViewRole) {
        for (QJsonValue val : value.toJsonArray())
            characters << mNovel->character(val.toInt());
        scene->setPointsOfView(characters);
    }
    return true;
}

QVariant SceneItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);

    return QString("Scene");
}

Qt::ItemFlags SceneItemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

bool SceneItemModel::insertRows(int row, int count, const QModelIndex &parent)
{

    if (row > rowCount() || row < 0){
        qWarning() << "Invalid row" << row;
        row = rowCount();
    }

    int start = row, end = row+(count-1);

    beginInsertRows(parent, row, end);

    for (int i = start; i <= end; ++i)
        mNovel->addScene(new Scene("New Scene", ""), i);

    endInsertRows();

    return true;
}

bool SceneItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int start = row;
    int end = row + (count-1);

    if (parent.isValid()){
        qWarning() << "remove scene - valid parent";
        return false;
    }

    if (row > rowCount()-1 || row < 0){
        qWarning() << "Could not delete from row" << row;
        return false;
    }

    if (end > rowCount()-1)
        end = rowCount()-1;
    beginRemoveRows(parent, row, end);

    for (int i = start; i <= end; ++i)
        mNovel->removeScene(mNovel->scenes()[i]);

    endRemoveRows();
    return true;
}

bool SceneItemModel::moveRows(const QModelIndex &sourceParent, int sourceRow,
                              int count, const QModelIndex &destinationParent,
                              int destinationChild)
{
    QList<Scene *> move;

    int sourceLast = sourceRow + (count-1);

    beginMoveRows(sourceParent, sourceRow, sourceLast, destinationParent,
                  destinationChild);

    for (int i = sourceRow; i <= sourceLast; ++i)
        mNovel->moveScenes(i, destinationChild);

    endMoveRows();

    return true;
}

Qt::DropActions SceneItemModel::supportedDropActions() const
{
    return Qt::MoveAction;
}
