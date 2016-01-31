#include "characteritemmodel.h"

CharacterItemModel::CharacterItemModel(Novel *novel, QObject *parent)
    : QAbstractListModel(parent)
{
    mNovel = novel;
    for (int i = 0; i < mNovel->characters().length(); ++i)
    {
        QModelIndex index = createIndex(i, 0);
        QBrush brush = QBrush();
        brush.setColor(mNovel->characters()[i]->color());
        this->setData(index, mNovel->characters()[i]->name(),
                      Qt::UserRole);
        this->setData(index, brush, Qt::BackgroundRole);
        setData(index, QVariant(mNovel->characters()[i]->id()), CharacterIdRole);
    }
}

void CharacterItemModel::addCharacter()
{
    Character *c = new Character("New Character");
    mNovel->addCharacter(c);
    insertRows(this->rowCount(), 1);
    QModelIndex index = lastRow();
    setData(index, c->name(), Qt::DisplayRole|Qt::EditRole);
    setData(index, QVariant(c->id()), CharacterIdRole);
    setData(index, c->color(), Qt::BackgroundRole);
}

int CharacterItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->characters().size();
}

QVariant CharacterItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        qWarning() << "Invalid index";
        return QVariant();
    }

    if (index.row() > mNovel->characters().size()){
        qWarning() << index.row() << " > # of characters(" <<
                      mNovel->characters().count() << ")";
        return QVariant();
    }

    Character *c = mNovel->characters()[index.row()];
    QVariant value;
    if (role == Qt::BackgroundRole) {
        QBrush value = QBrush();
        value.setColor(c->color());
        return value;
    } else if (role == Qt::DisplayRole || role ==  Qt::EditRole) {
        return c->name();
    } else if (role == CharacterIdRole) {
        return c->id();
    }
    return QVariant();
}

QVariant CharacterItemModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return tr("Character");
    return QVariant();
}

Qt::ItemFlags CharacterItemModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemFlag::ItemIsEnabled|Qt::ItemIsSelectable;
}

QModelIndex CharacterItemModel::lastRow() const
{
    return index(rowCount()-1);
}

bool CharacterItemModel::insertRows(int row, int count,
                                    const QModelIndex &parent)
{
    qDebug() << "Inserting rows for novel" << mNovel->getWorkingTitle();
    if (parent.isValid() || row + count <=0 )
        return false;

    bool inserted = false;

    beginInsertRows(QModelIndex(), row, row+count-1);

    for (int i = 0; i < (row + count - 1); ++i){
        mNovel->characters().insert(row+i, new Character(QString()));
        inserted = true;
    }

    endInsertRows();

    return inserted;
}

bool CharacterItemModel::removeRows(int row, int count,
                                    const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row >= mNovel->characters().size() || row + count <= 0)
        return false;

    int beginRow = qMax(0, row);
    int endRow = qMin(row + count - 1, mNovel->characters().size() - 1);

    beginRemoveRows(parent, beginRow, endRow);

    while (beginRow <= endRow) {
        mNovel->characters().removeAt(beginRow);
        ++beginRow;
    }

    endRemoveRows();
    return true;
}
