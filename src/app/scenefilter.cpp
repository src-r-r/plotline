#include "scenefilter.h"

SceneFilter::SceneFilter(Novel *novel, Plotline *plotline, QObject *parent)
    : QSortFilterProxyModel(parent)
{
    mNovel = novel;
    mPlotline = plotline;
    mSearch = QString();
//    connect(this, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
//            this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
//    connect(this, SIGNAL(rowsInserted(QModelIndex,int,int)),
    //            this, SLOT(onRowsInserted(QModelIndex, int, int)));
}

Qt::ItemFlags SceneFilter::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QSortFilterProxyModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

Qt::DropActions SceneFilter::supportedDropActions() const
{
    return Qt::MoveAction;
}

bool SceneFilter::filterAcceptsRow(int source_row,
                                   const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent);
    Scene *scene = mNovel->scenes()[source_row];

    bool b = ((mPlotline == 0 || (scene->plotline() == mPlotline)) &&
            (mSearch.isEmpty() || (scene->headline().toLower().contains(mSearch.toLower())
                                   || scene->action().toLower().contains(mSearch.toLower())) ));
    return b;
}

bool SceneFilter::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row+(count-1));
    SceneModel *sceneModel = (SceneModel *) sourceModel();
    qDebug() << "[+] scene filter - add " << count << "scenes at" << row;
    bool res = sceneModel->insertRows(row, count, mPlotline, parent);
    endInsertRows();

    return res;
}

bool SceneFilter::removeRows(const QModelIndexList &indexList)
{
    QList<QUuid> toDelete;
    for (QModelIndex index : indexList)
        toDelete << data(index, SceneModel::IdRole).toUuid();
    for (QUuid id : toDelete){
        Scene *scene = mNovel->scene(id);
        if (scene)
            qDebug() << "[-] Removing scene" << scene->headline();
        else
            qDebug() << "[!] Could not get scene by" << id;
        mNovel->removeScene(scene);
    }
    return true;
}

bool SceneFilter::moveRows(const QModelIndex &sourceParent, int sourceRow,
                           int count, const QModelIndex &destinationParent,
                           int destinationChild)
{
    beginMoveRows(sourceParent, sourceRow, sourceRow+(count-1), destinationParent,
                  destinationChild);

    endMoveRows();
}

Plotline *SceneFilter::plotline() const
{
    return mPlotline;
}

void SceneFilter::setPlotline(Plotline *plotline)
{
    mPlotline = plotline;
    emit this->filterChanged();
}

QString SceneFilter::search() const
{
    return mSearch;
}

void SceneFilter::setSearch(const QString &search)
{
    mSearch = search;
    emit this->filterChanged();
}

Novel *SceneFilter::novel() const
{
    return mNovel;
}

void SceneFilter::setNovel(Novel *novel)
{
    mNovel = novel;
    emit filterChanged();
}
