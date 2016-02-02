#include "plotlineitemmodel.h"

PlotlineItemModel::PlotlineItemModel(Novel *novel, QObject *parent)
    : QAbstractTableModel(parent)
{
    mNovel = novel;
    mRowCount = 0;
}

int PlotlineItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mRowCount;
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

    if (mNovel->plotlines().count() == 0)
        return QVariant();

    if ( !index.isValid() || mNovel->plotlines().isEmpty() ||
         row > mNovel->plotlines().count())
        return QVariant();

//    int count = mNovel->getPlotlines().count();
    Plotline *plotline = mNovel->plotlines()[row];

    if (!plotline)
        return QVariant();

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
        if (role == Qt::DisplayRole) {
            if (section == BRIEF)
                return QString("Brief");
            else if (section == SYNOPSIS)
                return QString("Synopsis");
            else if (section == CHARACTERS)
                return QString("Characters Involved");
        }
    }
    return QVariant();
}

bool PlotlineItemModel::setData(const QModelIndex &index,
                               const QVariant &value, int role)
{
    if (!index.isValid()){
        qWarning() << "Invalid index" << index;
        return false;
    }

    int row = index.row(), col = index.column();

    if (row > mNovel->plotlines().size()){
        qWarning() << "Cannot insert at row" << row << ": Only"
                   << mNovel->plotlines().size() << "plotlines";
        return false;
    }

    Plotline *plotline = mNovel->plotlines()[row];
    if (role == Qt::EditRole || role == Qt::DisplayRole){
        switch (col){
        case BRIEF:
            plotline->setBrief(value.toString());
            break;
        case SYNOPSIS:
            plotline->setSynopsis(value.toString());
            break;
        case CHARACTERS:
            QList<Character *> characterList = QList<Character *>();
            if (!value.toJsonArray().isEmpty())
                for (QJsonValue v : value.toJsonArray())
                    characterList << mNovel->character(v.toInt());
            plotline->setCharacters(characterList);
            break;
        }
    }

    return (col >= BRIEF && col <= CHARACTERS);
}

bool PlotlineItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row < 0){
        qWarning() << "Invalid row " << row;
        return false;
    }

    bool wasInserted = false;

    beginInsertRows(parent, row, row+(count-1));

    for (int i = row; i < row+count; ++i){
        ++mRowCount;
        wasInserted = true;
        qDebug() << "Novel now has" << mNovel->plotlines().size()
                 << "plotlines";
    }

    endInsertRows();

    return wasInserted;
}

bool PlotlineItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count);

    if (!parent.isValid() || row < 0 || mNovel->plotlines().isEmpty()
            || row+count > mNovel->plotlines().size() )
        return false;
    bool wasRemoved  = false;
    for (int i = row; i < row+count; ++i){
        --mRowCount;
        mNovel->plotlines().removeAt(i);
        wasRemoved = true;
    }

    endRemoveRows();

    return wasRemoved ;
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

void PlotlineItemModel::addPlotline(Plotline *p)
{
    int r = rowCount();
    if (!insertRows(r, 1)){
        qWarning() << "Could not insert rows at" << r;
        return;
    }
    QModelIndex idx;

    QBrush brush = QBrush(p->getColor());
    for (int i = 0; i < columnCount(); ++i){
        idx = index(r, i);
        setData(idx, brush, Qt::BackgroundRole);
    }

    idx = index(r, BRIEF);
    setData(idx, p->brief(), Qt::EditRole|Qt::DisplayRole);

    idx = index(r, SYNOPSIS);
    setData(idx, p->synopsis(), Qt::EditRole|Qt::DisplayRole);
}
