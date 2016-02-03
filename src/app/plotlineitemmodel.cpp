#include "plotlineitemmodel.h"

PlotlineItemModel::PlotlineItemModel(Novel *novel, QObject *parent)
    : QAbstractTableModel(parent)
{
    mNovel = novel;
    mRowCount = 0;

    QList<Plotline *> plotlines = mNovel->plotlines();
    insertRows(0, plotlines.count());
    QModelIndex d;
    for (int i = 0; i < plotlines.count(); ++i){
        for (int j = 0; j < columnCount(); ++j)
            setData(index(i, j), QVariant(plotlines[i]->id()), PlotlineId);
        d = index(i, BRIEF);
        setData(d, plotlines[i]->brief());
        d = index(i, SYNOPSIS);
        setData(d, plotlines[i]->synopsis());
        d = index(i, CHARACTERS);
    }
}

int PlotlineItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->plotlines().count();
}

int PlotlineItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // This will return 3:
    //  1 - Brief
    //  2 - Synopsis
    //  3 - Characters Involved
    return 3;
}

QVariant PlotlineItemModel::data(const QModelIndex &index, int role) const
{
    int row = index.row(),
            col = index.column();

    if (mNovel->plotlines().count() == 0){
        qWarning() << "No plotlines";
        return QVariant();
    }

    if ( !index.isValid() || mNovel->plotlines().isEmpty() ||
         row > mNovel->plotlines().count()){
        qWarning() << "Invalid index:" << index;
        return QVariant();
    }

//    int count = mNovel->getPlotlines().count();
    Plotline *plotline = mNovel->plotlines()[row];

    if (!plotline){
        qWarning() << "Plotline is null.";
        return QVariant();
    }

    // Paint the background color for any column.
    if (role == Qt::BackgroundRole) {
        QBrush brush = QBrush();
        brush.setColor(plotline->getColor());
        return brush;
    }

    if (role == PlotlineId)
        return QVariant(plotline->id());

    // Otherwise, just set column data accordingly.
    if (col == BRIEF) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return plotline->brief();
    } else if (col == SYNOPSIS) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return plotline->synopsis();
    } else if (col == CHARACTERS) {
        if (role == Qt::DisplayRole || role == Qt::EditRole){
            QStringList charList = QStringList();
            if (!plotline->characters().isEmpty())
                for (Character *c : plotline->characters())
                    charList << c->name();
            return QString(charList.join(","));
        } else if (role == Qt::DisplayRole || role == Qt::EditRole) {
            QJsonArray charList = QJsonArray();
            for (Character *c : plotline->characters())
                charList << QJsonValue(c->id());
        }
    }

    return QVariant();
}

QVariant PlotlineItemModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (section == BRIEF)
                return tr("Brief");
            else if (section == SYNOPSIS)
                return tr("Synopsis");
            else if (section == CHARACTERS)
                return tr("Characters Involved");
        }
    }
    return QVariant();
}

Qt::ItemFlags PlotlineItemModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

Plotline *PlotlineItemModel::getPlotlineAt(const QModelIndex &index)
{
    int id = this->data(index, PlotlineId).toInt();
    return mNovel->plotline(id);
}
