#include "plotframe.h"
#include "ui_plotframe.h"

PlotFrame::PlotFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::PlotFrame)
{
    ui->setupUi(this);
}

PlotFrame::~PlotFrame()
{
    delete ui;
}

void PlotFrame::onNovelLoad()
{
    mModel = new PlotlineItemModel(mainWindow()->novel());
}

void PlotFrame::onNovelNew()
{
    mModel = new PlotlineItemModel(mainWindow()->novel());
}

void PlotFrame::on_addPlotline_clicked()
{
    mainWindow()->novel()->addPlotline(new Plotline("", ""));
    emit mainWindow()->novel()->plotlinesChanged();
}
