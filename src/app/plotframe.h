#ifndef PLOTFRAME_H
#define PLOTFRAME_H

#include "plotlineappframe.h"
#include "plotlineitemmodel.h"

class PlotlineAppFrame;

namespace Ui {
class PlotFrame;
}

class PlotFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit PlotFrame(MainWindow *mainWindow, QWidget *parent = 0);
    ~PlotFrame();

    PlotlineItemModel *model() const;
    void setModel(PlotlineItemModel *model);

signals:
    void plotlineListModified();

public slots:
    void onNovelLoad();
    void onNovelNew();

    void onPlotlineDoubleClicked(QModelIndex index);
    void onPlotlineListModified();

private slots:
    void on_addPlotline_clicked();
    void on_editPlotline_clicked();
    void on_archivePlotline_clicked();
    void on_deletePlotline_clicked();
    void on_searchPlotlines_textChanged(const QString &arg1);
    void on_filterPlotlines_activated(int index);

    void on_plotlineTable_activated(const QModelIndex &index);

    void onPlotlineAdded(const QModelIndex &index);

    void on_plotlineTable_clicked(const QModelIndex &index);

private:
    Ui::PlotFrame *ui;

    PlotlineItemModel *mModel;
    Plotline *mSelectedPlotline;
    void showPlotlineDialog(bool isNew=false);
};

#endif // PLOTFRAME_H
