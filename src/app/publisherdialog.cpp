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
                                               "%n",
                                               "%t",
                                               "%I",
                                               "%1",
                                               "%O"
                                           }),
PublisherDialog::HeaderPlaceholders = QStringList({
                                               "",
                                               "%t",        // title
                                               "%s",        // short title
                                               "%l",        // author's last name
                                               "%a",        // author's full name
                                               "%p",        // page number
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

void PublisherDialog::updatePreview()
{
    // todo
}

QString PublisherDialog::formatTitleHeader() const
{
    QString name = mNovel->author()->name();
    if (!mNovel->author()->penName().isEmpty())
        name = mNovel->author()->penName();
    return QString("# ") + mNovel->getWorkingTitle() + QString("\n")
            + QString("# by\n# ") + name + QString("\n\n");
}

QString PublisherDialog::formatChapterHeader(Chapter *chapter) const
{
    QString format = ui->chapterHeaderText->text();
    return format.replace("%n", "\n# ")
            .replace("%t", chapter->title())
            .replace("%I", QString::number(chapter->number()))
            .replace("%1", QString::number(chapter->number()))
            .replace("%O", QString::number(chapter->number()))
            + QString("\n\n");
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

void PublisherDialog::on_PublisherDialog_accepted()
{
    QString text = formatTitleHeader();
    for (Chapter *c : mNovel->chapters()){
        text += formatChapterHeader(c);
        text += c->latestContent() + QString("\n\n");
    }
    QString outPath = ui->outputFile->text();
    QFile *outFile = new QFile(outPath);
    int success = outFile->open(QFile::WriteOnly);
    if (!success){
        QMessageBox::critical(this, tr("Error"),
                              tr("Could not publish to \"")
                              + outPath + tr("\""), QMessageBox::Ok,
                              QMessageBox::NoButton);
        qWarning() << "Could not write to" << outPath;
        return;
    }
    outFile->write(text.toStdString().data(), text.length());
    qDebug() << "Wrote" << text.length() << "bytes to" << outPath;
    outFile->close();
    delete outFile;
}
