#include "novelframe.h"
#include "ui_novelframe.h"

NovelFrame::NovelFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::NovelFrame)
{
    ui->setupUi(this);
}

NovelFrame::~NovelFrame()
{
    delete ui;
}
