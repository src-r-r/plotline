#ifndef CHARACTERITEMMODEL_H
#define CHARACTERITEMMODEL_H

#include <QtCore>
#include <QObject>
#include <QAbstractItemModel>
#include <QBrush>
#include "scene.h"

class CharacterItemModel : public QAbstractListModel
{
public:
    CharacterItemModel(Novel *novel, QObject *parent = 0);

    const static int CharacterIdRole = Qt::UserRole;

    void addCharacter();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

    QVariant data(const QModelIndex & index,
                                      int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;

    QModelIndex lastRow() const;

private:
    Character *rootItem;

signals:
    CharacterItemModel *mParent;
    Novel *mNovel;

public slots:
};

#endif // CHARACTERITEMMODEL_H
