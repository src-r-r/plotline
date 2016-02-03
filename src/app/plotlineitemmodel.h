#ifndef PLOTLINEITEMVIEW_H
#define PLOTLINEITEMVIEW_H

#include <QtCore>
#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QTextDocumentFragment>
#include <QBrush>
#include "novel.h"

class Novel;

class PlotlineItemModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PlotlineItemModel(Novel *novel = 0, QObject *parent = 0);

    // Read methods
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    // Write methods
//    bool setData(const QModelIndex & index, const QVariant & value,
//                 int role = Qt::EditRole);


    Qt::ItemFlags flags(const QModelIndex & index) const;

    Plotline *getPlotlineAt(const QModelIndex & index);
    Plotline *getPlotlineAt(const int index);
//    void addPlotline(int row, Plotline *p);

    // Custom roles
    static const int PlotlineId = Qt::UserRole;

    // Column numbers
    static const int BRIEF = 0,
        SYNOPSIS = 1,
        CHARACTERS = 2,
    // Column widths
        BRIEF_WIDTH = 200,
        SYNOPSIS_WIDTH = 420,
        CHARACTERS_WIDTH = 100;
private:

    Novel *mNovel;
    int mRowCount;

signals:

public slots:
};

#endif // PLOTLINEITEMVIEW_H
