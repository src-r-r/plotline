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
                                               "",
                                               "%t",
                                               "%n",
                                               "%r",
                                               "%n",
                                               "%t"
                                           }),
PublisherDialog::HeaderPlaceholders = QStringList({
                                               "",
                                               "%t",
                                               "%s",
                                               "%l",
                                               "%a",
                                               "%p",
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
    if (index == 0)
        return;
    QString text = ui->chapterHeaderText->text();
    text = text.insert(index, ChapterPlaceholders[index]);
    ui->chapterHeaderText->setText(text);
    ui->chapterHeaderCombo->blockSignals(true);
    ui->chapterHeaderCombo->setCurrentIndex(0);
    ui->chapterHeaderCombo->blockSignals(false);
}

void PublisherDialog::on_titleCombo_activated(int index)
{
    if (index == 0)
        return;
    QString text = ui->titleText->text();
    text = text.insert(index, HeaderPlaceholders[index]);
    ui->titleText->setText(text);
    ui->titleText->blockSignals(true);
    ui->titleCombo->setCurrentIndex(0);
    ui->titleText->blockSignals(false);
}

void PublisherDialog::on_chapterHeaderText_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    chapterTextPos = arg2;
}

void PublisherDialog::on_titleText_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    headerTextPos = arg2;
}
