#ifndef CHARACTERITEMMODEL_H
#define CHARACTERITEMMODEL_H

#include <QtCore>
#include <QObject>
#include <QAbstractListModel>
#include "scene.h"

class CharacterItemModel : public QAbstractItemModel
{
public:
    CharacterItemModel(QList<Character *> characters = QList<Character *>(),
                       QObject *parent = 0);



    // reading
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    //writing
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole) Q_DECL_OVERRIDE;
//    bool setHeaderData(int section, Qt::Orientation orientation,
//                       const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
//    bool insertColumns(int position, int columns,
//                       const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
//    bool removeColumns(int position, int columns,
//                       const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;

private:
    //void setupModelData(const QStringList &lines, TreeItem *parent);
    Character *getItem(const QModelIndex &index) const;

    Character *rootItem;

signals:
    CharacterItemModel *mParent;
    QList<Character *> mCharacters;

public slots:
};

#endif // CHARACTERITEMMODEL_H
