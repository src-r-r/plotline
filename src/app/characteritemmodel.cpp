#include "characteritemmodel.h"

CharacterModel::CharacterModel(Novel *novel, QObject *parent)
    : QAbstractListModel(parent)
{
    mNovel = novel;
}

void CharacterModel::addCharacter()
{
    Character *c = new Character("New Character");
    mNovel->addCharacter(c);
    insertRows(this->rowCount(), 1);
    QModelIndex index = lastRow();
    setData(index, c->name(), Qt::DisplayRole|Qt::EditRole);
    setData(index, QVariant(c->id()), CharacterIdRole);
    setData(index, c->color(), Qt::BackgroundRole);
}

int CharacterModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : mNovel->characters().count();
}

QVariant CharacterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        qWarning() << "[<] character data: Invalid index";
        return QVariant();
    }

    if (index.row() > mNovel->characters().size()){
        qWarning("[<] character data: invalid row %d", index.row());
        return QVariant();
    }

    Character *c = mNovel->characters()[index.row()];

    if (role == Qt::ForegroundRole){
        QColor textColor = QColor(0, 0, 0);
        if (!c->color().isValid())
            return textColor;
        if ((255 / 2) > c->color().value())
            textColor = QColor(255, 255, 255);      // White text.
        return QBrush(textColor);
    }if (role == Qt::BackgroundRole || role == ColorRole) {
        if (c->color().isValid())
            return QBrush(c->color());
        return QVariant();
    } else if (role == Qt::DisplayRole || role ==  Qt::EditRole) {
        qDebug("    role = Qt::DisplayRole");
        return c->name();
    } else if (role == CharacterIdRole) {
        qDebug("    role = CharacterIdRole");
        return c->id();
    } else if (role == NameRole) {
        qDebug("    role = NameRole");
        return c->name();
    } else if (role == LabelRole) {
        qDebug("    role = LabelRole");
        return c->label();
    } else if (role == HeadshotRole) {
        qDebug("    role = HeadshotRole");
        QVariant headshot;
        headshot = c->getHeadshot();
        return headshot;
    } else if (role == ColorRole) {
        qDebug("    role = ColorRole");
        if (c->color().isValid())
            return c->color().name();
        return QString();
    } else if (role == ArchivedRole) {
    } else {
        qWarning("[<] character data: Invalid role %d", role);
    }
    return QVariant();
}

QVariant CharacterModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return tr("Character");
    return QVariant();
}

bool CharacterModel::setData(const QModelIndex &index, const QVariant &value,
                             int role)
{
    if (!index.isValid()){
        qWarning() << "[>] character set data: Invalid index";
        return false;
    }

    if (index.row() > mNovel->characters().size()){
        qWarning() << index.row() << " > # of characters(" <<
                      mNovel->characters().count() << ")";
        return false;
    }

    Character *c = mNovel->characters()[index.row()];

    if (role == Qt::BackgroundRole) {
        c->setColor(QColor(value.toString()));
    } else if (role == Qt::DisplayRole || role ==  Qt::EditRole) {
        c->setName(value.toString());
    } else if (role == CharacterIdRole) {
    } else if (role == NameRole) {
        c->setName(value.toString());
    } else if (role == LabelRole) {
        c->setLabel(value.toString());
    } else if (role == HeadshotRole) {
        QImage headshot = value.value<QImage>();
        c->setHeadshot(headshot);
    } else if (role == ColorRole) {
        c->setColor(QColor(value.toString()));
    } else if (role == ArchivedRole) {
    } else {
        qWarning("[>] character set data: Invalid role %d", role);
    }
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

Qt::DropActions CharacterModel::supportedDropActions()
{
    return Qt::MoveAction;
}

QModelIndex CharacterModel::lastRow() const
{
    return index(rowCount()-1);
}

bool CharacterModel::insertRows(int row, int count,
                                    const QModelIndex &parent)
{
    qDebug() << "Inserting rows for novel" << mNovel->getWorkingTitle();
    if (parent.isValid() || row + count <=0 )
        return false;

    int end = row + (count-1);

    beginInsertRows(QModelIndex(), row, end);

    for (int i = row; i <= end; ++i)
        mNovel->addCharacter(new Character(""), i);

    endInsertRows();

    return true;
}

bool CharacterModel::removeRows(int row, int count,
                                    const QModelIndex &parent)
{
    int start = row;
    int end = row + (count-1);

    if (parent.isValid()){
        qWarning() << "[-] remove character - valid parent";
        return false;
    }

    if (row > rowCount()-1 || row < 0){
        qWarning() << "[-] remove character - Invalid row" << row;
        return false;
    }

    if (end > rowCount()-1)
        end = rowCount()-1;
    beginRemoveRows(parent, row, end);

    QList<Character *> characters = mNovel->characters();
    for (int i = start; i <= end; ++i)
        characters.removeAt(i);
    mNovel->setCharacters(characters);

    endRemoveRows();
    return true;
}

bool CharacterModel::moveRows(const QModelIndex &sourceParent, int sourceRow,
                              int count, const QModelIndex &destinationParent,
                              int destinationChild)
{
    int sourceLast = sourceRow + (count-1);

    beginMoveRows(sourceParent, sourceRow, sourceLast, destinationParent,
                  destinationChild);

    QList<Character *> characters = mNovel->characters();

    for (int i = sourceRow; i <= sourceLast; ++i)
        characters.move(i, destinationChild);

    mNovel->setCharacters(characters);

    endMoveRows();

    return true;
}
