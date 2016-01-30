#include "novelframe.h"
#include "ui_novelframe.h"

NovelFrame::NovelFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::NovelFrame)
{
    ui->setupUi(this);
}

NovelFrame::~NovelFrame()
{
    delete ui;
}

void NovelFrame::onNovelLoad()
{
    Novel *novel = mainWindow()->novel();
    ui->workingTitle->setText(novel->getWorkingTitle());
    ui->genre->setText(novel->getGenre());
    ui->setting->setText(novel->getSetting());
    ui->pointofView->setCurrentIndex((int) novel->getPointOfView());
    ui->tense->setCurrentIndex((int) novel->getTense());
}

void NovelFrame::onNovelNew()
{
    ui->workingTitle->clear();
    ui->genre->clear();
    ui->setting->clear();
    ui->pointofView->clear();
    ui->tense->clear();
}

void NovelFrame::on_workingTitle_textEdited(const QString &arg1)
{
    mMainWindow->novel()->setWorkingTitle(arg1);
    emit novelModified();
}

void NovelFrame::on_genre_textEdited(const QString &arg1)
{
    mMainWindow->novel()->setGenre(arg1);
    emit novelModified();
}

void NovelFrame::on_setting_textEdited(const QString &arg1)
{
    mMainWindow->novel()->setSetting(arg1);
    emit novelModified();
}

void NovelFrame::on_pointofView_activated(int index)
{
    mMainWindow->novel()->setPointOfView((Novel::PointOfView) index);
    emit novelModified();
}

void NovelFrame::on_tense_activated(int index)
{
    mMainWindow->novel()->setTense((Novel::Tense) index);
    emit novelModified();
}
