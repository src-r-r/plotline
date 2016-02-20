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
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());

    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                  const QModelIndex &destinationParent, int destinationChild);

    // Drag/drop support

    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                      int column, const QModelIndex &parent);
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;

    static const int HeadlineRole = Qt::UserRole + 0,
        ActionRole = Qt::UserRole + 1,
        PlotlineRole = Qt::UserRole + 2,
        CharactersRole = Qt::UserRole + 4,
        PointsOfViewRole = Qt::UserRole + 8;

private:

    Novel *mNovel;

signals:

public slots:
};

#endif // SCENEITEMMODEL_H
