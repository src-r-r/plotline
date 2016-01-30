#include "sceneframe.h"
#include "ui_sceneframe.h"

SceneFrame::SceneFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
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
