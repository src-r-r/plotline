#include "publisherdialog.h"
#include "ui_publisherdialog.h"
#include <QtWidgets>

const QStringList PublisherDialog::Extensions = QStringList({
                                               "epub",
                                               "mobi",
                                               "markdown",
                                               "markdown",
                                               "pdf",
                                               "html",
                                               "odt"
                                           }),
PublisherDialog::ChapterPlaceholders = QStringList({
                                               "epub",
                                               "mobi",
                                               "markdown",
                                               "markdown",
                                               "pdf",
                                               "html",
                                               "odt"
                                           }),
PublisherDialog::Extensions = QStringList({
                                               "epub",
                                               "mobi",
                                               "markdown",
                                               "markdown",
                                               "pdf",
                                               "html",
                                               "odt"
                                           });

PublisherDialog::PublisherDialog(Novel *novel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PublisherDialog)
{
    ui->setupUi(this);
    mNovel = novel;
}

PublisherDialog::~PublisherDialog()
{
    delete ui;
}

void PublisherDialog::on_chooseDirectory_clicked()
{
    QString outDir = QFileDialog::getExistingDirectory(this,
                                                         "Output Directory",
                                      QDir::homePath());
    outDir += QDir::separator() + mNovel->getWorkingTitle() + QChar('.')
            + Extensions[ui->format->currentIndex()];
    ui->outputFile->setText(outDir);
}

void PublisherDialog::on_chapterHeaderCombo_activated(int index)
{

}
