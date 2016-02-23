#ifndef CHAPTERFILTER_H
#define CHAPTERFILTER_H

#include "plotline.h"
#include "chaptermodel.h"

class ChapterFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ChapterFilter(Plotline *plotline = 0, QObject *parent = 0);

    Plotline *plotline() const;
    void setPlotline(Plotline *plotline);

//    bool insertRows(int row, int count, const QModelIndex &parent);
//    bool removeRows(int row, int count, const QModelIndex &parent);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const;
//    bool filterAcceptsColumn(int source_column, const QModelIndex & source_parent) const;

private:
    Plotline *mPlotline;

signals:

public slots:
};

#endif // CHAPTERFILTER_H
