#ifndef SCENEFILTER_H
#define SCENEFILTER_H

#include <QtCore>
#include <QAbstractProxyModel>
#include "plotline.h"
#include "sceneitemmodel.h"
#include "plotlineitemmodel.h"

class SceneFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SceneFilter(Novel *novel, Plotline *plotline = 0, QObject *parent = 0);


    Qt::ItemFlags flags(const QModelIndex &index) const;
    Qt::DropActions supportedDropActions() const;

//    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent = QModelIndex())
    const;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool removeRows(const QModelIndexList &indexList);
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                  const QModelIndex &destinationParent, int destinationChild);

    Plotline *plotline() const;
    void setPlotline(Plotline *plotline);

    QString search() const;
    void setSearch(const QString &search);

    Novel *novel() const;
    void setNovel(Novel *novel);

private:
    Novel *mNovel;
    Plotline *mPlotline;
    QString mSearch;

signals:

public slots:
};

#endif // SCENEFILTER_H
