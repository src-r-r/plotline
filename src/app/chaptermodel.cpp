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
    if (row > rowCount() || row < 0){
        qWarning() << "chapter: Invalid row" << row;
        return false;
    }

    int end = row + count-1;

    beginInsertRows(parent, row, end);

    for (int i = row; i <= end; ++i)
        mNovel->addChapter(new Chapter(), i+1);

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

    for (int i = row; i <= end; ++i){
        mNovel->removeChapterAt(i, true);
    }

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

    if (role == IdRole){
        qDebug() << "Returning chapter ID" << chapter->id();
        return QVariant(chapter->id());
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

    if (role == TitleRole)
        return chapter->title();
    if (role == ContentRole){
        qDebug() << " - content for revision" << chapter->currentRevision()
                 << ":" << chapter->currentContent().length() << "bytes";
        return chapter->currentContent();
    }
    if (role == RevisionRole){
        qDebug() << " - revision:" << chapter->currentRevision();
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
            sceneIds.append(QJsonValue(s->id()));
        return sceneIds;
    }
    return QVariant();
}

bool ChapterModel::setData(const QModelIndex &index, const QVariant &value,
                           int role)
{
    int row = index.row();

    if (!index.isValid()){
        qWarning() << "Setting chapter data: invalid index.";
        return false;
    }

    if (row >= mNovel->chapters().count() || row < 0){
        qWarning() << "Setting chapter data: invalid index" << index;
        return false;
    }

    Chapter *chapter = mNovel->chapters()[row];

//    if (role >= Qt::UserRole){
//        qDebug() << "setdata Chapter" << chapter->number();
//        for (int i = 0; i < chapter->revisions().count(); ++i)
//            qDebug() << " > Revision" << i << ":"
//                     << chapter->revisions()[i]->content().size()
//                     << "bytes";
//    }

    if (role == TitleRole){
        chapter->setTitle(value.toString());
    } else if (role == ContentRole) {
        chapter->setContent(value.toString());
//        qDebug() << "ch" << chapter->number()
//                 << "rev" << chapter->currentRevision()
//                 << ":" << value.toString();
    } else if (role == RevisionRole) {
        qDebug() << " - Setting current revision:" << value.toInt();
        chapter->setCurrentRevision(value.toInt());
    } else if (role == RevisionMarkableRole) {
        qWarning() << "RevisionMarkableRole is read-only. Leaving alone";
    } else if (role == NumberRole) {
        qWarning() << "Number role is read-only. Leaving alone.";
    } else if (role == CompleteRole) {
        chapter->setIsComplete(value.toBool());
    } else if (role == SceneRole) {
        QList<Scene *> scenes;
        for (QJsonValue v : value.toJsonArray())
            scenes << mNovel->scene(v.toInt());
        chapter->setScenes(scenes);
    } else {
        return false;
    }
    return true;
}

QVariant ChapterModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
    // kind of obvious what this table is and what the columns mean.
    // Leave blank and just return a QVariant.

//    if (orientation == Qt::Horizontal) {
//        if (role == Qt::DisplayRole || role == Qt::EditRole) {
//            if (section == NUMBER)
//                return QString("");
//            if (section == TITLE)
//                return tr("Chapter");
//        }
//    }
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
