#include "plotlineitemdelegate.h"

PlotlineItemDelegate::PlotlineItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *PlotlineItemDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    switch(index.column()){
    case BRIEF:
        return new QLineEdit(parent);
        break;
    case SYNOPSIS:
        return new QLineEdit(parent);
        break;
    case CHARACTERS:
        return new QPushButton(parent);
        break;
    }

    return new QWidget();
}

void PlotlineItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (editor == 0) return;

    QLineEdit *lineEditor = 0;
    QPushButton *button = 0;

    switch (index.column()){
    case BRIEF:
    case SYNOPSIS:
        lineEditor = static_cast<QLineEdit *>(editor);
        lineEditor->setText(index.model()->data(index, Qt::EditRole).toString());
        break;
    case CHARACTERS:
        button = static_cast<QPushButton *>(editor);
        break;
    }
}

void PlotlineItemDelegate::setModelData(QWidget *editor,
                                        QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
    QLineEdit *lineEditor = 0;
    QPushButton *button = 0;

    switch (index.column()){
    case BRIEF:
    case SYNOPSIS:
        lineEditor = static_cast<QLineEdit *>(editor);
        model->setData(index, lineEditor->text());
        break;
    case CHARACTERS:
        button = static_cast<QPushButton *>(editor);
        break;
    }
}

void PlotlineItemDelegate::updateEditorGeometry(QWidget *editor,
                                                const QStyleOptionViewItem &option,
                                                const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

