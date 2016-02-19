#ifndef PLOTLINEDIALOG_H
#define PLOTLINEDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QPainter>
#include <QtCore>
#include <QtDebug>
#include <QModelIndex>
#include <QWidget>
#include <QCheckBox>

#include "plotline.h"
#include "plotframe.h"
#include "plotlineitemmodel.h"

class PlotFrame;

namespace Ui {
class PlotlineDialog;
}

class PlotlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotlineDialog(PlotlineItemModel *model,
                            const QModelIndex &index,
                            bool isNew = false,
                            QWidget *parent = 0);
    ~PlotlineDialog();

private slots:
    void on_plotlineColor_clicked();
    void onColorSelected(const QColor &color);
    void on_clearPlotlineColor_clicked();
    void on_buttonBox_accepted();

signals:

    void plotlineAdded(const QModelIndex &index);
    void plotlineModified(const QModelIndex &index);
    void canceled();

private:
    Ui::PlotlineDialog *ui;

    PlotlineItemModel *mModel;
    Plotline *mPlotline;
    QModelIndex mIndex;
    QMap<QCheckBox *, Character *> mCharacterList;

    QColor mColor;

    bool mIsNew;
};

#endif // PLOTLINEDIALOG_H
