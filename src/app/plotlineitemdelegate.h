#ifndef SCENEITEMDELEGATE_H
#define SCENEITEMDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>

#include "novel.h"
#include "plotline.h"

class Novel;
class Plotline;

class PlotlineItemDelegate : public QStyledItemDelegate
{

    Q_OBJECT

public:
    PlotlineItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    Novel *mNovel;

    static const int BRIEF = 0,
        SYNOPSIS = 1,
        CHARACTERS = 2;

signals:

public slots:
};

#endif // SCENEITEMDELEGATE_H
