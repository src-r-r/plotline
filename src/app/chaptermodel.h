#ifndef CHAPTERMODEL_H
#define CHAPTERMODEL_H

#include <QtCore>
#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QTextDocumentFragment>
#include <QBrush>
#include "chapter.h"

class ChapterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ChapterModel(Novel *novel, QObject *parent = 0);


    // Overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    bool insertRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex & index) const;

    Novel *novel() const;
    void setNovel(Novel *novel);

    // Custom roles
    static const int ChapterId = Qt::UserRole;
    // Column numbers
    static const int NUMBER = 0,
        TITLE = 1;

private:
    Novel *mNovel = 0;
    int mRowCount, mColCount;

signals:

public slots:
};

#endif // CHAPTERMODEL_H
