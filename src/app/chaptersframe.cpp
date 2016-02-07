#include "chaptersframe.h"
#include "ui_chaptersframe.h"

ChaptersFrame::ChaptersFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::ChaptersFrame)
{
    ui->setupUi(this);

    mModel = new ChapterModel(mainWindow->novel());
    ui->chapterTable->setModel(mModel);

    // Connect the signals
    connect(this, SIGNAL(chapterSelected()),
            this, SLOT(onChapterSelected()));
    connect(this, SIGNAL(revisionChanged()),
            this, SLOT(onRevisionChanged()));
}

ChaptersFrame::~ChaptersFrame()
{
    delete ui;
}

void ChaptersFrame::onNovelLoad()
{
    mModel = new ChapterModel(mainWindow()->novel());
    ui->chapterTable->setModel(mModel);
}

void ChaptersFrame::onNovelNew()
{

}

void ChaptersFrame::onChapterSelected()
{
    ui->chapterLayout->setEnabled(true);

    QModelIndex index = ui->chapterTable->currentIndex();
    QString num = QVariant(index.row()+1).toString();

    ui->chapterNumber->setText(num);
    ui->chapterTitle->setText(mSelectedChapter->title());

    int globalRevision = mainWindow()->novel()->currentRevision();
    ui->chapterRevision->setMaximum(globalRevision+1);
    ui->chapterRevision->setMinimum(1);

    emit revisionChanged();
}

void ChaptersFrame::onRevisionChanged()
{
    qDebug() << "Revisions for chapter:" << mSelectedChapter->revisions().count();
    int revision = mSelectedChapter->currentRevision();
    int globalRevision = mainWindow()->novel()->currentRevision();
    bool isComplete = mSelectedChapter->revisions()[revision]->isComplete();
    QString content = mSelectedChapter->content(revision);

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
    Chapter *chapter = new Chapter();

    int r = mModel->rowCount();
    if (!mModel->insertRows(r, 1)){
        qWarning() << "Chapter: Could not insert rows after row" << r;
        return;
    }
    mModel->setData(mModel->index(r, ChapterModel::NUMBER), QString(r+1));
//    mModel->setData(index(r, ChapterModel::TITLE), r)

    mainWindow()->novel()->addChapter(chapter);

    ui->chapterTable->setCurrentIndex(mModel->index(r, 0));
    mSelectedChapter = chapter;

    onChapterSelected();

    emit novelModified();
}

void ChaptersFrame::on_archiveChapter_clicked()
{

}

void ChaptersFrame::on_deleteChapter_clicked()
{

}

void ChaptersFrame::on_assignScenes_clicked()
{

}

void ChaptersFrame::on_chapterTitle_textEdited(const QString &arg1)
{
    mSelectedChapter->setTitle(arg1);
}

void ChaptersFrame::on_chapterTable_activated(const QModelIndex &index)
{
    int chapterId = mModel->data(index, ChapterModel::ChapterId).toInt();
    mSelectedChapter = mainWindow()->novel()->chapter(chapterId);
    emit onChapterSelected();
}

void ChaptersFrame::on_chapterTable_clicked(const QModelIndex &index)
{
    on_chapterTable_activated(index);
}

void ChaptersFrame::on_chapterComplete_toggled(bool checked)
{
    int rev = mSelectedChapter->currentRevision();
    mSelectedChapter->revisions()[rev]->setIsComplete(checked);
}

void ChaptersFrame::on_chapterRevision_valueChanged(int arg1)
{
    mSelectedChapter->setCurrentRevision(arg1-1);
    emit revisionChanged();
}
