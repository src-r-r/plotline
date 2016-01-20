#ifndef SCENEITEMMODEL_H
#define SCENEITEMMODEL_H

#include <QtCore>
#include <QAbstractListModel>
#include "scene.h"

class SceneItemModel : public QAbstractListModel
{
public:
    SceneItemModel(QList<Scene *> scenes=QList<Scene *>(),
                   QObject *parent = 0 );

    QList<Scene *> getScenes() const;
    void setScenes(const QList<Scene *> &scenes);

    // Overrides
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole)
        const;

private:
    QList<Scene *> mScenes;
    SceneItemModel *root;

signals:

public slots:
};

#endif // SCENEITEMMODEL_H
