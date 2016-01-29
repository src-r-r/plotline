#include "plotframe.h"
#include "ui_plotframe.h"

PlotFrame::PlotFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PlotFrame)
{
    ui->setupUi(this);
}

PlotFrame::~PlotFrame()
{
    delete ui;
}
