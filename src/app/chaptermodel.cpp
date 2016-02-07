#include "chaptermodel.h"

ChapterModel::ChapterModel(Novel *novel, QObject *parent) : QAbstractTableModel(parent)
{
    mNovel = novel;
    mRowCount = 0;

    QList<Chapter *> chapters = mNovel->chapters();
    insertRows(0, chapters.count());
    QModelIndex d;
    mColCount = 1;
    for (int i = 0; i < chapters.count(); ++i){
        int id = chapters[i]->id();
        for (int j = 0; j < columnCount(); ++j)
            setData(index(i, j), QVariant(id), ChapterId);
        d = index(i, NUMBER);
        setData(d, QString(i+1));

        if (!chapters[i]->title().isEmpty()){
            mColCount = 2;
            d = index(i, TITLE);
            setData(d, chapters[i]->title());
        }
    }
}

int ChapterModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->chapters().count();
}

int ChapterModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mColCount;
}

bool ChapterModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row > rowCount() || row < 0){
        qWarning() << "chapter: Invalid row" << row;
        return false;
    }

    beginInsertRows(parent, row, row+(count-1));

    endInsertRows();

    return true;
}

bool ChapterModel::removeRows(int row, int count, const QModelIndex &parent)
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

QVariant ChapterModel::data(const QModelIndex &index, int role) const
{
    int row = index.row(),
            col = index.column();

    if (mNovel->chapters().count() == 0){
        qWarning() << "No chapters";
        return QVariant();
    }

    if ( !index.isValid() || mNovel->chapters().isEmpty() ||
         row > mNovel->chapters().count()){
        qWarning() << "Chapter: Invalid index:" << index;
        return QVariant();
    }

    Chapter *chapter = mNovel->chapters()[row];

    if (!chapter){
        qWarning() << "Chapter is null!";
        return QVariant();
    }

    if (role == ChapterId)
        return QVariant(chapter->id());

    if (role == Qt::EditRole || role == Qt::DisplayRole){
        switch(col){
        case NUMBER:
            return QVariant(row+1);
        case TITLE:
            return chapter->title();
        }
    }
    return QVariant();
}

QVariant ChapterModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (section == NUMBER)
                return QString("");
            if (section == TITLE)
                return tr("Chapter");
        }
    }
    return QVariant();
}

Qt::ItemFlags ChapterModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

Novel *ChapterModel::novel() const
{
    return mNovel;
}

void ChapterModel::setNovel(Novel *novel)
{
    mNovel = novel;

    // Determine if the column count is 1 or 2.
    mColCount = 1;
    for (Chapter *c : mNovel->chapters()){
        if (!c->title().isEmpty()){
            mColCount = 2;
            break;
        }
    }
}
