#ifndef SCENEITEMMODEL_H
#define SCENEITEMMODEL_H

#include <QtCore>
#include <QAbstractListModel>
#include <QBrush>
#include "scene.h"

class SceneItemModel : public QAbstractListModel
{
public:
    SceneItemModel(Novel *novel, QObject *parent = 0 );

    // Overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    bool insertRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());

    Novel *novel() const;
    void setNovel(Novel *novel);

private:
    Novel *mNovel = 0;
    SceneItemModel *root;

signals:

public slots:
};

#endif // SCENEITEMMODEL_H
