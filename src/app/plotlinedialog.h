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

class PlotFrame;

namespace Ui {
class PlotlineDialog;
}

class PlotlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotlineDialog(PlotFrame *plotFrame,
                            const QModelIndex &index = QModelIndex(),
                            QWidget *parent = 0);
    ~PlotlineDialog();

private slots:
    void on_plotlineColor_clicked();
    void onColorSelected(const QColor &color);
    void on_clearPlotlineColor_clicked();
    void on_buttonBox_accepted();

signals:

private:
    Ui::PlotlineDialog *ui;

    PlotFrame *mPlotFrame;
    Plotline *mPlotline;
    QModelIndex mIndex;
    QMap<QCheckBox *, Character *> mCharacterList;

    bool mIsNew;
};

#endif // PLOTLINEDIALOG_H
