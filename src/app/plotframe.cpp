#include "plotframe.h"
#include "ui_plotframe.h"

PlotFrame::PlotFrame(Novel *novel, QWidget *parent) :
    PlotlineAppFrame(novel, parent),
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
    mModel = new PlotlineItemModel(mNovel);
}

void PlotFrame::onNovelNew()
{
    mModel = new PlotlineItemModel(mNovel);
}

void PlotFrame::on_addPlotline_clicked()
{
    mNovel->addPlotline(new Plotline("", ""));
    emit mNovel->plotlinesChanged();
}
