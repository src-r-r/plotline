#include "chaptersframe.h"
#include "ui_chaptersframe.h"

ChaptersFrame::ChaptersFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::ChaptersFrame)
{
    ui->setupUi(this);

    mModel = new ChapterModel(mainWindow->novel());
    ui->chapterTable->setModel(mModel);
    ui->chapterTable->resizeColumnsToContents();
    ui->chapterTable->horizontalHeader()->setStretchLastSection(true);

    clearLayout(false, true);

    // Connect the signals
    connect(this, SIGNAL(chapterSelected()),
            this, SLOT(onChapterSelected()));
    connect(this, SIGNAL(revisionChanged()),
            this, SLOT(onRevisionChanged()));
    connect(this, SIGNAL(chapterModified()),
            this, SLOT(onChapterModified()));

}

ChaptersFrame::~ChaptersFrame()
{
    delete ui;
}

void ChaptersFrame::onNovelLoad()
{
    mModel = new ChapterModel(mainWindow()->novel());
    ui->chapterTable->setModel(mModel);
    ui->chapterTable->resizeColumnsToContents();
    ui->chapterTable->horizontalHeader()->setStretchLastSection(true);
}

void ChaptersFrame::onNovelNew()
{
    clearLayout(false, true);
}

void ChaptersFrame::onChapterModified()
{
    Chapter *chapter = mainWindow()
            ->novel()->chapters()[ui->chapterTable->currentIndex().row()];
    QModelIndex index = ui->chapterTable->currentIndex();
    mModel->setData(index, chapter->title());
    emit novelModified();
}

void ChaptersFrame::onChapterSelected()
{

    clearLayout(true, true);

    ui->deleteChapter->setEnabled(true);
    ui->archiveChapter->setEnabled(true);
    ui->assignScenes->setEnabled(true);

    QModelIndex index = ui->chapterTable->currentIndex();

    int number = mModel->data(index, ChapterModel::NumberRole).toInt();
    QString title = mModel->data(index, ChapterModel::TitleRole).toString();
    int revision = mModel->data(index, ChapterModel::RevisionRole).toInt();
    bool complete = mModel->data(index, ChapterModel::CompleteRole).toBool();
    QString content = mModel->data(index, ChapterModel::ContentRole).toString();

    ui->chapterNumber->setText(QVariant(number).toString());
    ui->chapterTitle->setText(title);
    ui->chapterContent->setPlainText(content);
    ui->chapterRevision->setValue(revision+1);
    ui->chapterRevision->setMaximum(mainWindow()->novel()->revisionCount());
    ui->chapterRevision->setMinimum(1);
    ui->chapterComplete->setChecked(complete);

    emit revisionChanged();
}

void ChaptersFrame::onRevisionChanged()
{
    if (!ui->chapterTable->currentIndex().isValid()){
        qWarning() << "Invalid index" << ui->chapterTable->currentIndex();
        return;
    }
    int i = ui->chapterTable->currentIndex().row();
    Chapter *chapter = mainWindow()->novel()->chapters()[i];
    qDebug() << "Revisions for chapter:" << chapter->revisions().count();
    int revision = chapter->currentRevision();
    int globalRevision = mainWindow()->novel()->currentRevision();
    bool isComplete = chapter->revisions()[revision]->isComplete();
    QString content = chapter->content(revision);

    ui->chapterRevision->setValue(revision+1);

    if (revision < globalRevision){
        ui->chapterRevision->setStyleSheet("background-color: #ff0000;");
    } else {
        ui->chapterRevision->setStyleSheet("background-color: #ffffff;");
    }

    ui->chapterComplete->setChecked(isComplete);
    ui->chapterContent->setPlainText(content);
}

void ChaptersFrame::on_chapterFilter_activated(int index)
{

}

void ChaptersFrame::on_addChapter_clicked()
{
    if (!mModel->insertRows(mModel->rowCount(), 1)){
        qWarning() << "Error inserting rows at" << mModel->rowCount();
        return;
    }
    emit novelModified();

    ui->chapterTable->setCurrentIndex(mModel->index(mModel->rowCount(), 0));
    emit chapterSelected();
}

void ChaptersFrame::on_archiveChapter_clicked()
{

}

void ChaptersFrame::on_deleteChapter_clicked()
{
    QModelIndex index = ui->chapterTable->currentIndex();
    int row = index.row();
    mModel->removeRows(row, 1);
}

void ChaptersFrame::on_assignScenes_clicked()
{

}

void ChaptersFrame::on_chapterTitle_textEdited(const QString &arg1)
{
    mModel->setData(ui->chapterTable->currentIndex(), arg1,
                    ChapterModel::TitleRole);
    emit chapterModified();
}

void ChaptersFrame::on_chapterTable_activated(const QModelIndex &index)
{
    emit onChapterSelected();
}

void ChaptersFrame::on_chapterTable_clicked(const QModelIndex &index)
{
    if (!index.isValid())
        clearLayout(false, true);
    else
        on_chapterTable_activated(index);
}

void ChaptersFrame::on_chapterComplete_toggled(bool checked)
{
    Chapter *chapter = mainWindow()
            ->novel()->chapters()[ui->chapterTable->currentIndex().row()];
    int rev = chapter->currentRevision();
    chapter->revisions()[rev]->setIsComplete(checked);
}

void ChaptersFrame::on_chapterRevision_valueChanged(int arg1)
{
    if (arg1 < 1) return;
    mModel->setData(ui->chapterTable->currentIndex(), QVariant(arg1-1),
                    ChapterModel::RevisionRole);
    emit revisionChanged();
}

void ChaptersFrame::on_chapterContent_textChanged()
{
    QModelIndex index = ui->chapterTable->currentIndex();
    int role = ChapterModel::ContentRole;
    mModel->setData(index, ui->chapterContent->toPlainText(), role);
    emit chapterModified();
}

void ChaptersFrame::clearLayout(bool enable, bool clear)
{
    if (clear){
        ui->chapterNumber->clear();
        ui->chapterTitle->clear();
        ui->chapterComplete->setChecked(false);
        ui->chapterRevision->clear();
        ui->chapterContent->clear();
    }
    QList<QWidget *> toDisable({
        ui->chapterNumber, ui->chapterTitle, ui->chapterComplete,
                                   ui->chapterRevision, ui->chapterContent
    });
    for (QWidget *w : toDisable){
        if (enable)
            w->setEnabled(true);
        else
            w->setDisabled(true);
    }
}
