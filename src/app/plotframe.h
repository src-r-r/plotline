#ifndef PLOTFRAME_H
#define PLOTFRAME_H

#include "plotlineappframe.h"
#include "plotlineitemmodel.h"

namespace Ui {
class PlotFrame;
}

class PlotFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit PlotFrame(Novel *novel, QWidget *parent = 0);
    ~PlotFrame();

public slots:
    void onNovelLoad();
    void onNovelNew();

private slots:
    void on_addPlotline_clicked();

private:
    Ui::PlotFrame *ui;

    PlotlineItemModel *mModel;
};

#endif // PLOTFRAME_H
