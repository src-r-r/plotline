#include "novelframe.h"
#include "ui_novelframe.h"

NovelFrame::NovelFrame(Novel *novel, QWidget *parent) :
    PlotlineAppFrame(novel, parent),
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
    ui->workingTitle->setText(mNovel->getWorkingTitle());
    ui->genre->setText(mNovel->getGenre());
    ui->pointofView->setCurrentIndex((int) mNovel->getPointOfView());
    ui->tense->setCurrentIndex((int) mNovel->getTense());
}

void NovelFrame::onNovelNew()
{
    ui->workingTitle->clear();
    ui->genre->clear();
    ui->pointofView->clear();
    ui->tense->clear();
}

void NovelFrame::on_workingTitle_textEdited(const QString &arg1)
{
    mNovel->setWorkingTitle(arg1);
    emit novelModified();
}

void NovelFrame::on_genre_textEdited(const QString &arg1)
{
    mNovel->setGenre(arg1);
    emit novelModified();
}

void NovelFrame::on_setting_textEdited(const QString &arg1)
{
    mNovel->setSetting(arg1);
    emit novelModified();
}

void NovelFrame::on_pointofView_activated(int index)
{
    mNovel->setPointOfView((Novel::PointOfView) index);
    emit novelModified();
}

void NovelFrame::on_tense_activated(int index)
{
    mNovel->setTense((Novel::Tense) index);
    emit novelModified();
}
