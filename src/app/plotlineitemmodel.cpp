#include "plotlineitemmodel.h"

PlotlineItemModel::PlotlineItemModel(Novel *novel, QObject *parent)
    : QAbstractTableModel(parent)
{
    mNovel = novel;
    connect(mNovel, SIGNAL(plotlinesChanged()), this, SLOT(onNovelPlotlinesChanged()));
}

int PlotlineItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->getPlotlines().count();
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

    if (mNovel->getPlotlines().count() == 0)
        return QVariant();

    if ( !index.isValid() || mNovel->getPlotlines().isEmpty() ||
         row > mNovel->getPlotlines().count())
        return QVariant();

//    int count = mNovel->getPlotlines().count();
    Plotline *plotline = mNovel->getPlotlines()[row];

    if (!plotline)
        return QVariant();

    // Paint the background color for any column.
    if (role == Qt::BackgroundRole) {
        QBrush brush = QBrush();
        brush.setColor(plotline->getColor());
        return brush;
    }

    if (role == ROLE_PLOTLINE_ID)
        return QVariant(plotline->id());

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
            if (!plotline->getCharacters().isEmpty())
                for (Character *c : plotline->getCharacters())
                    charList << c->name();
            return QString(charList.join(","));
        } else if (role == Qt::DisplayRole || role == Qt::EditRole) {
            QJsonArray charList = QJsonArray();
            for (Character *c : plotline->getCharacters())
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
    if (!index.isValid()){
        qWarning() << "Invalid index" << index;
        return false;
    }

    int row = index.row(), col = index.column();

    if (row > mNovel->getPlotlines().size()){
        qWarning() << "Cannot insert at row" << row << ": Only"
                   << mNovel->getPlotlines().size() << "plotlines";
        return false;
    }

    Plotline *plotline = mNovel->getPlotlines()[row];
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

    beginInsertRows(parent, row, row+count);

    for (int i = row; i < row+count; ++i){
        mNovel->addPlotline(new Plotline("", ""));
        wasInserted = true;
        qDebug() << "Novel now has" << mNovel->getPlotlines().size()
                 << "plotlines";
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

void PlotlineItemModel::onNovelPlotlinesChanged()
{
    if (rowCount() != 0)
        removeRows(0, rowCount());
    QList<Plotline *> plotlines = mNovel->getPlotlines();
    int count = plotlines.count();

    if (!insertRows(0, count, QModelIndex())){
        qWarning() << "Could not insert" << count << "rows";
        return;
    }

    for (int i = 0; i < count; ++i){
        setData(index(i, BRIEF), plotlines[i]->getBrief());
        setData(index(i, SYNOPSIS), plotlines[i]->getSynopsis());
        QJsonArray characters = QJsonArray();
        if (!plotlines[i]->getCharacters().empty())
            for (Character *c : plotlines[i]->getCharacters())
                characters << QJsonValue(c->id());
        setData(index(i, CHARACTERS), characters);
        // Also set the background color and Character ID for all columns.
        for (int j = 0; j < columnCount(); ++j){
            setData(index(i, j), plotlines[i]->getColor(), Qt::BackgroundRole);
            setData(index(i, j), QVariant(plotlines[i]->id()), ROLE_PLOTLINE_ID);
        }
    }
}

Qt::ItemFlags PlotlineItemModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

Plotline *PlotlineItemModel::getPlotlineAt(const QModelIndex &index)
{
    int id = this->data(index, ROLE_PLOTLINE_ID).toInt();
    return mNovel->getPlotline(id);
}
