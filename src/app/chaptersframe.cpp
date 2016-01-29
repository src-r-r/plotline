#include "chaptersframe.h"
#include "ui_chaptersframe.h"

ChaptersFrame::ChaptersFrame(Novel *novel, QWidget *parent) :
    PlotlineAppFrame(novel, parent),
    ui(new Ui::ChaptersFrame)
{
    ui->setupUi(this);
}

ChaptersFrame::~ChaptersFrame()
{
    delete ui;
}

void ChaptersFrame::onNovelLoad()
{

}

void ChaptersFrame::onNovelNew()
{

}
