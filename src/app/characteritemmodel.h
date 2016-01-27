#ifndef CHARACTERITEMMODEL_H
#define CHARACTERITEMMODEL_H

#include <QtCore>
#include <QObject>
#include <QAbstractListModel>
#include <QBrush>
#include "scene.h"

class CharacterItemModel : public QAbstractListModel
{
public:
    CharacterItemModel(Novel *novel, QObject *parent = 0);

    void addCharacter();
    void setCharacters(const QList<Character *> &characters);

private:

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index,
                                      int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
//    Qt::ItemFlags flags(const QModelIndex & index) const;
    bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

    Character *rootItem;

signals:
    CharacterItemModel *mParent;
    Novel *mNovel;

public slots:
};

#endif // CHARACTERITEMMODEL_H
