#include "characteritemmodel.h"

CharacterItemModel::CharacterItemModel(QList<Character *> characters,
                                       QObject *parent) : QAbstractItemModel(parent)
{
    mCharacters = characters;
}

QModelIndex CharacterItemModel::parent(const QModelIndex &child) const
{
    // Currently we do not have any children. Simply return QModelIndex
    return QModelIndex();
}

int CharacterItemModel::rowCount(const QModelIndex &parent) const
{
    return mCharacters.count();
}

int CharacterItemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant CharacterItemModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == 0 && role == Qt::DisplayRole)
        return mCharacters[index.row()]->getName();
    return QVariant();
}

Qt::ItemFlags CharacterItemModel::flags(const QModelIndex &index) const
{
    // TODO: Add character attributes as chidlren
    // return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
    return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled |
            Qt::ItemIsDropEnabled | Qt::ItemNeverHasChildren;
}

bool CharacterItemModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    mCharacters.insert(position, new Character(QString()));
}

bool CharacterItemModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    mCharacters.removeAt(position);
}

QModelIndex CharacterItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    return QModelIndex();
}

