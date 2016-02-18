#include "chapterfilter.h"

ChapterFilter::ChapterFilter(Plotline *plotline, QObject *parent) : QSortFilterProxyModel(parent)
{
    mPlotline = plotline;
}

bool ChapterFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (0 == mPlotline)
        return true;
    ChapterModel *model = (ChapterModel *) sourceModel();
    QJsonArray sceneIds = model->data(model->index(source_row, 0),
                              ChapterModel::SceneRole).toJsonArray();

    Scene *scene = 0;
    bool found = false;
    for (QJsonValue v : sceneIds){
        scene = mPlotline->novel()->scene(v.toInt());
        if (scene == 0){
            qWarning() << "chapter filter: Could not find scene with id"
                       << v.toInt();
        }
        if (scene->plotline() == mPlotline)
            found = true;
    }
    return found;
}

//bool ChapterFilter::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
//{
//    return true; //we're row-dependent, not column-dependent
//}

Plotline *ChapterFilter::plotline() const
{
    return mPlotline;
}

void ChapterFilter::setPlotline(Plotline *plotline)
{
    mPlotline = plotline;
    emit this->filterChanged();
}
