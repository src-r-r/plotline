#include "plotlineitemmodel.h"

PlotlineItemModel::PlotlineItemModel(Novel *novel, QObject *parent)
    : QAbstractTableModel(parent)
{
    mNovel = novel;
    mRowCount = 0;
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

bool PlotlineItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0)
        row = 0;

    int end = row + (count-1);

    beginInsertRows(parent, row, end);

    for (int i = row; i <= end; ++i)
        mNovel->addPlotline(new Plotline("", ""), row);

    endInsertRows();

    return true;
}

bool PlotlineItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int end = row + (count-1);

    if (row > rowCount()-1 || row < 0){
        qWarning() << "Could not delete from row" << row;
        return false;
    }

    if (end > rowCount()-1)
        end = rowCount()-1;

    beginRemoveRows(parent, row, end);

    for (int i = row; i <= end; ++i)
        mNovel->removePlotline(mNovel->plotlines()[i]);

    endRemoveRows();
    return true;
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
    if (role == Qt::BackgroundRole || role == ColorRole) {
        QBrush brush = QBrush();
        brush.setColor(plotline->getColor());
        return brush;
    }

    // Otherwise, just set column data accordingly.
    if ((col == BRIEF && (role == Qt::DisplayRole
                         || role == Qt::EditRole))
            || role == BriefRole) {
        return plotline->brief();
    } else if ((col == SYNOPSIS && (role == Qt::DisplayRole
                                   || role == Qt::EditRole))
               || role == SynopsisRole) {
        return plotline->synopsis();
    } else if ((col == CHARACTERS && (role == Qt::EditRole)) ||
               role == CharacterRole) {
        QJsonArray jChars;
        for (Character *c : plotline->characters())
            jChars.append(QJsonValue(c->id()));
        return jChars;
    } else if ((col == CHARACTERS) && (role == Qt::DisplayRole)) {
        QStringList names;
        for (Character *c : plotline->characters())
            names << c->name();
        return names.join(",");
    }

    return QVariant();
}

bool PlotlineItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()){
        qWarning() << "set plotline data: invalid index" << index;
        return false;
    }

    int row = index.row(),
            column = index.column();

    Plotline *plotline = mNovel->plotlines()[index.row()];

    if (role == BriefRole){
        plotline->setBrief(value.toString());
    } else if (role == SynopsisRole){
        plotline->setSynopsis(value.toString());
    } else if (role == CharacterRole){
        QList<Character *> characters;
        for (QJsonValue v : value.toJsonArray())
            characters << mNovel->character(v.toInt());
        plotline->setCharacters(characters);
    } else if (role == ColorRole) {
        plotline->setColor(QColor(value.toString()));
    }

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

Novel *PlotlineItemModel::novel() const
{
    return mNovel;
}

void PlotlineItemModel::setNovel(Novel *novel)
{
    mNovel = novel;
}
