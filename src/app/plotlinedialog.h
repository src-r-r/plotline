#ifndef PLOTLINEDIALOG_H
#define PLOTLINEDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QPainter>

#include "plotline.h"

namespace Ui {
class PlotlineDialog;
}

class PlotlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotlineDialog(Novel *novel, Plotline *plotline = 0,
                            QWidget *parent = 0);
    ~PlotlineDialog();

private slots:
    void on_plotlineColor_clicked();
    void onColorSelected(const QColor &color);

    void on_clearPlotlineColor_clicked();

    void on_buttonBox_accepted();

    void on_plotlineCharacterSelect_activated(int index);

    void on_plotlineCharacterList_activated(const QModelIndex &index);

private:
    Ui::PlotlineDialog *ui;

    Novel *mNovel;
    Plotline *mPlotline;

    bool mIsNew;
};

#endif // PLOTLINEDIALOG_H
