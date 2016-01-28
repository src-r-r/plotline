#include "plotlineitemmodel.h"

PlotlineItemModel::PlotlineItemModel(Novel *novel, QObject *parent)
    : QAbstractTableModel(parent)
{
    mNovel = novel;
}

int PlotlineItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->getPlotlines().size();
}

int PlotlineItemModel::columnCount(const QModelIndex &parent) const
{
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

    if ( !index.isValid() || mNovel->getPlotlines().isEmpty() ||
         row > mNovel->getPlotlines().size())
        return QVariant();

    Plotline *plotline = mNovel->getPlotlines()[row];

    // Paint the background color for any column.
    if (role == Qt::BackgroundRole) {
        QBrush brush = QBrush();
        brush.setColor(plotline->getColor());
        return brush;
    }

    // Otherwise, just set column data accordingly.
    if (col == BRIEF) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return plotline->getBrief();
    } else if (col == SYNOPSIS) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
            return plotline->getSynopsis();
    } else if (col == CHARACTERS) {
        if (role == Qt::DisplayRole || role == Qt::EditRole){
            QStringList charList = QStringList();
            for (Character *c : plotline->getCharacters())
                charList << c->getName();
            return QString(charList.join(","));
        } else if (role == Qt::DisplayRole || role == Qt::EditRole) {
            QJsonArray charList = QJsonArray();
            for (Character *c : plotline->getCharacters())
                charList << QJsonValue(c->getId());
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
        } else if (role == Qt::SizeHintRole) {
            if (section == BRIEF)
                return QSize(BRIEF_WIDTH, DEFAULT_HEIGHT);
            else if (section == SYNOPSIS)
                return QSize(SYNOPSIS_WIDTH, DEFAULT_HEIGHT);
            else if (section == CHARACTERS)
                return QSize(CHARACTERS_WIDTH, DEFAULT_HEIGHT);
        }
    }
    return QVariant();
}

bool PlotlineItemModel::setData(const QModelIndex &index,
                               const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int row = index.row(), col = index.column();

    if (mNovel->getPlotlines().isEmpty() || row > mNovel->getPlotlines().size())
        return false;

    Plotline *plotline = mNovel->getPlotlines()[row];
    if (col == BRIEF)
        plotline->setBrief(value.toString());
    else if (col == SYNOPSIS)
        plotline->setSynopsis(value.toString());
    else if (col == CHARACTERS){
        QList<Character *> characterList = QList<Character *>();
        for (QJsonValue v : value.toJsonArray())
            characterList << mNovel->getCharacter(v.toInt());
        plotline->setCharacters(characterList);
    }

    return (col >= BRIEF && col <= CHARACTERS);
}

bool PlotlineItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid() || row < 0  || row > mNovel->getPlotlines().size() )
        return false;
    bool wasInserted = false;

    beginInsertRows(parent, row, row+count);

    for (int i = row; i < row+count-1; ++i){
        mNovel->getPlotlines().insert(i, new Plotline("", ""));
        setData(createIndex(i, 0), QString(""));
        setData(createIndex(i, 1), QString(""));
        setData(createIndex(i, 2), QString(""));
        wasInserted = true;
    }

    endInsertRows();

    return wasInserted;
}

bool PlotlineItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count);

    if (!parent.isValid() || row < 0 || mNovel->getPlotlines().isEmpty()
            || row+count > mNovel->getPlotlines().size() )
        return false;
    bool wasRemoved  = false;
    for (int i = row; i < row+count; ++i){
        mNovel->getPlotlines().removeAt(i);
        wasRemoved = true;
    }

    endRemoveRows();

    return wasRemoved ;
}

Qt::ItemFlags PlotlineItemModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable;
}

