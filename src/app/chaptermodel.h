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
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::DisplayRole);

    bool insertRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());
    bool removeRows(int row, int count,
                    const QModelIndex & parent = QModelIndex());
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                  const QModelIndex &destinationParent, int destinationChild);
    void rowsMoved(const QModelIndex & parent, int start,
                                       int end, const QModelIndex & destination,
                                       int row);


    Qt::ItemFlags flags(const QModelIndex & index) const;
    Qt::DropActions supportedDropActions() const;

//    QMimeData *dropMimeData(const QMimeData *data, Qt::DropAction action,
//                            int row, int column, const QModelIndex &parent);

    Novel *novel() const;
    void setNovel(Novel *novel);

    // Custom roles
    static const int IdRole = Qt::UserRole,
        NumberRole = Qt::UserRole + 1,
        TitleRole = Qt::UserRole + 2,
        ContentRole = Qt::UserRole + 4,
        RevisionRole = Qt::UserRole + 8,
        RevisionMarkableRole = Qt::UserRole + 16,
        CompleteRole = Qt::UserRole + 32,
        SceneRole = Qt::UserRole + 64;
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
