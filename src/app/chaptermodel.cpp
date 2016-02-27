#include "chaptermodel.h"

ChapterModel::ChapterModel(Novel *novel, QObject *parent) : QAbstractTableModel(parent)
{
    mNovel = novel;

    QList<Chapter *> chapters = mNovel->chapters();
    mColCount = 1;
    for (int i = 0; i < chapters.count(); ++i)
        if (!chapters[i]->title().isEmpty())
            mColCount = 2;
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
//    if (parent.isValid()){
//        qWarning() << "[+] chapter insert rows: INVALID PARENT" << parent;
//        return false;
//    }
    if (row > rowCount() || row < 0){
        qWarning() << "[+] chapter insert rows: setting row=" << rowCount();
        row = rowCount();
    }

    int end = row + (count-1);

    qDebug("[+] chapter insert rows (row=%d, count=%d, parent=[%d, %d])",
           row, count, parent.row(), parent.column());

    beginInsertRows(parent, row, end);

    for (int i = row; i <= end; ++i)
        mNovel->addChapter(new Chapter(), i);

    endInsertRows();

    return true;
}

bool ChapterModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int end = row + (count-1);

//    if (parent.isValid()){
//        qWarning() << "[-] remove row: valid parent";
//        return false;
//    }

    if (row > rowCount()-1 || row < 0){
        qWarning() << "Could not delete from row" << row;
        return false;
    }

    if (end > rowCount()-1)
        end = rowCount()-1;
    beginRemoveRows(parent, row, end);

    qDebug("[-] chapter remove rows (row=%d, count=%d, parent=[%d, %d][, "\
           "end=%d])",
           row, count, parent.row(), parent.column(), end);

    for (int i = row; i <= end; ++i){
        qDebug() << "[-] chapter remove" << mNovel->chapters()[row]->number();
        mNovel->removeChapter(mNovel->chapters()[row]);
    }

    endRemoveRows();
    return true;
}

bool ChapterModel::moveRows(const QModelIndex &sourceParent, int sourceRow,
                            int count, const QModelIndex &destinationParent,
                            int destinationChild)
{

    int sourceLast = sourceRow + (count-1);

    qDebug("[~] chapter move row (sourceParent=[%d, %d], sourceRow=%d, " \
           "count=%d, destinationParent=[%d, %d], destinationChild=%d)",
           sourceParent.row(), sourceParent.column(), sourceRow,
           count, destinationParent.row(), destinationParent.column(),
           destinationChild);

    beginMoveRows(sourceParent, sourceRow, sourceLast, destinationParent,
                  destinationChild);

    for (int i = 0; i < count; ++i)
        mNovel->moveChapter(sourceRow, destinationChild);

    endMoveRows();
}

//void ChapterModel::rowsMoved(const QModelIndex &parent, int start, int end,
//                             const QModelIndex &destination, int row)
//{

//    qDebug("*emit* rowsMoved(parent=[%d, %d], start=%d, end=%d" \
//           ", destination=[%d, %d], row=%d", parent.row(), parent.column(),
//           start, end, destination.row(), destination.column(), row);
//}

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
        qWarning() << "chapter get data: Invalid index:" << index;
        return QVariant();
    }

    Chapter *chapter = mNovel->chapters()[row];

    if (!chapter){
        qWarning() << "chapter get data: chapter is null";
        return QVariant();
    }

    if (role == Qt::EditRole || role == Qt::DisplayRole){
        switch(col){
        case NUMBER:
            return QVariant(chapter->number());
        case TITLE:
            return chapter->title();
        }
    }

    if (role >= Qt::UserRole)
        qDebug() << "getdata Chapter" << chapter->number();


    if (role == IdRole){
        qDebug() << "chapter get data ID" << chapter->id();
        return QVariant(chapter->id());
    }
    if (role == TitleRole)
        return chapter->title();
    if (role == ContentRole){
        qDebug() << "chapter get data revision content"
                 << chapter->currentRevision()
                 << ":" << chapter->currentContent().length() << "bytes";
        return chapter->currentContent();
    }
    if (role == RevisionRole){
        qDebug() << "chapter get data revision:" << chapter->currentRevision();
        return QVariant(chapter->currentRevision());
    } if (role == NumberRole)
        return QVariant(chapter->number());
    if (role == CompleteRole)
        return QVariant(chapter->revisions()[chapter->currentRevision()]
                ->isComplete());
    if (role == RevisionMarkableRole)
        return QVariant(chapter->canMarkCompleted());
    if (role == SceneRole){
        QJsonArray sceneIds;
        for (Scene *s : chapter->scenes())
            sceneIds.append(QJsonValue(s->id().toString()));
        return sceneIds;
    }
    return QVariant();
}

bool ChapterModel::setData(const QModelIndex &index, const QVariant &value,
                           int role)
{
    int row = index.row();

    if (!index.isValid() || row >= mNovel->chapters().count() || row < 0){
        qWarning() << "chapter set data: invalid index:" << index;
        return false;
    }

    qDebug() << "chapter set data";
    qDebug("    index=(%d, %d)", index.row(), index.column());

    Chapter *chapter = mNovel->chapters()[row];

    if (role == TitleRole){
        chapter->setTitle(value.toString());
        qDebug() << "   role = title";
    } else if (role == ContentRole) {
        chapter->setContent(value.toString());
        qDebug() << "   role = content";
    } else if (role == RevisionRole) {
        qDebug() << "   role = revision";
        chapter->setCurrentRevision(value.toInt());
        qDebug() << "   role = revision";
    } else if (role == RevisionMarkableRole) {
        qWarning() << "RevisionMarkableRole is read-only. Leaving alone";
        qDebug() << "   role = revisionMarkable";
    } else if (role == NumberRole) {
        qWarning() << "Number role is read-only. Leaving alone.";
        qDebug() << "   role = number";
    } else if (role == CompleteRole) {
        chapter->setIsComplete(value.toBool());
        qDebug() << "   role = complete";
    } else if (role == SceneRole) {
        qDebug() << "   role = scene";
        QList<Scene *> scenes;
        for (QJsonValue v : value.toJsonArray())
            scenes << mNovel->scene(QUuid(v.toString()));
        chapter->setScenes(scenes);
    } else {
        qDebug() << "   role = (invalid)" << role;
        return false;
    }
    return true;
}

QVariant ChapterModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    return QVariant();
}

Qt::ItemFlags ChapterModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
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

Qt::DropActions ChapterModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

