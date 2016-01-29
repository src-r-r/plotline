#include "chaptersframe.h"
#include "ui_chaptersframe.h"

ChaptersFrame::ChaptersFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ChaptersFrame)
{
    ui->setupUi(this);
}

ChaptersFrame::~ChaptersFrame()
{
    delete ui;
}
