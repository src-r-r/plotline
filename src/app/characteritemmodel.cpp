#include "characteritemmodel.h"

CharacterItemModel::CharacterItemModel(Novel *novel, QObject *parent)
    : QAbstractListModel(parent)
{
    mNovel = novel;
    for (int i = 0; i < mNovel->getCharacters().length(); ++i)
    {
        QModelIndex index = createIndex(i, 0);
        QBrush brush = QBrush();
        brush.setColor(mNovel->getCharacters()[i]->getColor());
        this->setData(index, mNovel->getCharacters()[i]->getName(),
                      Qt::UserRole);
        this->setData(index, brush, Qt::BackgroundRole);
    }
}

void CharacterItemModel::addCharacter()
{
    QModelIndex index;
    Character *c = new Character("");
    mNovel->addCharacter(c);
    this->insertRow(this->rowCount(), index);
    this->setData(index, c->getName());
}

void CharacterItemModel::setCharacters(const QList<Character *> &characters)
{

}

int CharacterItemModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->getCharacters().size();
}

QVariant CharacterItemModel::data(const QModelIndex &index, int role) const
{
    if (index.row() > mNovel->getCharacters().size())
        return QVariant();

    Character *c = mNovel->getCharacters()[index.row()];
    QVariant value;
    if (role == Qt::BackgroundRole) {
        QBrush value = QBrush();
        value.setColor(c->getColor());
        return value;
    } else if (role == Qt::UserRole) {
        return c->getName();
    }
    return QVariant();
}

QVariant CharacterItemModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const
{
    return tr("Character");
}

//bool CharacterItemModel::setData(const QModelIndex &index,
//                                 const QVariant &value, int role)
//{

//}

//Qt::ItemFlags CharacterItemModel::flags(const QModelIndex &index) const
//{

//}

bool CharacterItemModel::insertRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "Inserting rows for novel" << mNovel->getWorkingTitle();
    if (parent.isValid() || row + count <=0 )
        return false;

    bool inserted = false;

    beginInsertRows(parent, row, row+count);

    for (int i = 0; i < count; ++i){
        mNovel->getCharacters().insert(row+i, new Character(QString()));
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

    if (row >= mNovel->getCharacters().size() || row + count <= 0)
        return false;

    int beginRow = qMax(0, row);
    int endRow = qMin(row + count - 1, mNovel->getCharacters().size() - 1);

    beginRemoveRows(parent, beginRow, endRow);

    while (beginRow <= endRow) {
        mNovel->getCharacters().removeAt(beginRow);
        ++beginRow;
    }

    endRemoveRows();
    return true;
}
