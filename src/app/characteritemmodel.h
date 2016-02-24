#ifndef CHARACTERITEMMODEL_H
#define CHARACTERITEMMODEL_H

#include <QtCore>
#include <QObject>
#include <QAbstractItemModel>
#include <QBrush>
#include "scene.h"

class CharacterModel : public QAbstractListModel
{
public:
    CharacterModel(Novel *novel, QObject *parent = 0);

    const static int CharacterIdRole = Qt::UserRole;

    void addCharacter();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

    QVariant data(const QModelIndex & index,
                                      int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value,
                 int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;

    QModelIndex lastRow() const;

    // roles
    static const int NameRole = Qt::UserRole + 1,
        NicknameRole = Qt::UserRole + 2,
        LabelRole = Qt::UserRole + 4,
        HeadshotRole = Qt::UserRole + 8,
        ColorRole = Qt::UserRole + 16,
        ArchivedRole = Qt::UserRole + 32;

private:

signals:
    CharacterModel *mParent;
    Novel *mNovel;

public slots:
};

#endif // CHARACTERITEMMODEL_H
