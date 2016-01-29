#include "sceneframe.h"
#include "ui_sceneframe.h"

SceneFrame::SceneFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SceneFrame)
{
    ui->setupUi(this);
}

SceneFrame::~SceneFrame()
{
    delete ui;
}
