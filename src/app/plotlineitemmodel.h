#ifndef PLOTLINEITEMVIEW_H
#define PLOTLINEITEMVIEW_H

#include <QtCore>
#include <QAbstractTableModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QBrush>
#include "novel.h"

class Novel;

class PlotlineItemModel : public QAbstractTableModel
{
public:
    PlotlineItemModel(Novel *novel = 0, QObject *parent = 0);

    // Read methods
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    // Write methods
    bool setData(const QModelIndex & index, const QVariant & value,
                 int role = Qt::EditRole);

    // List structure methods
    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex());
    Qt::ItemFlags flags(const QModelIndex & index) const;

    Plotline *addPlotline();

private:

    Novel *mNovel;

    // Column numbers
    static const int BRIEF = 0,
        SYNOPSIS = 1,
        CHARACTERS = 2,
    // Column widths
        BRIEF_WIDTH = 50,
        SYNOPSIS_WIDTH = 200,
        CHARACTERS_WIDTH = 100,
    // Heights
        DEFAULT_HEIGHT = 25;

signals:

public slots:
};

#endif // PLOTLINEITEMVIEW_H
