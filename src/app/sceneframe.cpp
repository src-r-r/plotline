#include "sceneframe.h"
#include "ui_sceneframe.h"

SceneFrame::SceneFrame(Novel *novel, QWidget *parent) :
    PlotlineAppFrame(novel, parent),
    ui(new Ui::SceneFrame)
{
    ui->setupUi(this);
}

SceneFrame::~SceneFrame()
{
    delete ui;
}

void SceneFrame::onNovelLoad()
{

}

void SceneFrame::onNovelNew()
{

}
