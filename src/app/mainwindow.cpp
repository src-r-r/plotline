#include "mainwindow.h"
#include "ui_mainwindow.h"

const QStringList MainWindow::frameTitles = QStringList(tr("Novel"))
        << tr("Character")
        << tr("Plotline")
        << tr("Scene")
        << tr("Chapter");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    mIsSaved = false;

    mNovel = new Novel("Untitled");

    mNovelFrame = new NovelFrame(mNovel);
    mCharacterFrame = new CharacterFrame(mNovel);
    mPlotFrame = new PlotFrame(mNovel);
    mSceneFrame = new SceneFrame(mNovel);
    mChapterFrame = new ChaptersFrame(mNovel);

    frames = QList<PlotlineAppFrame *>();
    frames << mNovelFrame
           << mCharacterFrame
           << mPlotFrame
           << mSceneFrame
           << mChapterFrame;
    for (int i = 0; i < frames.count(); ++i) {
        ui->tabWidget->insertTab(i, frames[i], frameTitles[i]);
        connect(frames[i], SIGNAL(novelModified()), this,
                SLOT(onNovelModified()));
        connect(this, SIGNAL(novelLoaded()), frames[i], SLOT(onNovelLoad()));
        connect(this, SIGNAL(novelNew()), frames[i], SLOT(onNovelNew()));
    }

    connect(this, SIGNAL(saveNovel()), this, SLOT(onSaveNovel()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mNovel;
}

void MainWindow::onNovelModified()
{
    QString path = mOpenedFile.isEmpty() ? "Untitled" : mOpenedFile;
    setWindowTitle(QString("Plotline - " + path + "*"));
}

void MainWindow::onSaveNovel()
{
    mNovel->writeTo(mOpenedFile);
    QString path = mOpenedFile.isEmpty() ? "Untitled" : mOpenedFile;
    setWindowTitle("Plotline - " + path);
}

void MainWindow::on_actionPreferences_triggered()
{
    mPrefDialog = new PreferencesDialog(this);
    int result = mPrefDialog->exec();
}

void MainWindow::on_actionNovelNew_triggered()
{
    if (!mIsSaved)
    {
        QMessageBox *confirmSave = new QMessageBox(tr("New Novel"),
            tr("Do you want to save the current novel?"),
            QMessageBox::Question, QMessageBox::Yes, QMessageBox::No,
                                              QMessageBox::NoButton,
                                              this);
        confirmSave->setModal(true);
        int result = confirmSave->exec();
        if (result == QMessageBox::Yes && mOpenedFile.isEmpty())
            emit saveNovel();
    }
    mNovel = new Novel(QString());
    emit novelNew();
}

void MainWindow::on_actionNovelOpen_triggered()
{
    QString fileTypes = tr("Plotline Files (*.json *.pln);;All Files (*.*)");
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Novel"), QString(), fileTypes);
    if (fileName.isEmpty())
        return;

    mOpenedFile = fileName;
    mNovel = Novel::readFrom(mOpenedFile);
    qDebug() << "Opened novel" << mNovel->getWorkingTitle();
    emit novelLoaded();
}

void MainWindow::on_actionNovelSave_triggered()
{
    QSettings settings;
    QString defaultDir = settings.value(PreferencesDialog
                                    ::DEFAULT_PROJECT_DIRECTORY,
                                    QDir::homePath()).toString();
    if (mOpenedFile.isEmpty()){
        mOpenedFile = QFileDialog::getSaveFileName(this,
                                                    tr("Save Novel"),
                                                    defaultDir,
                                                    tr("Plotline File (*.pln)"));
        if (mOpenedFile.isEmpty())
            return;

        if (!mOpenedFile.endsWith(".pln"))
            mOpenedFile.append(".pln");
    }
    emit saveNovel();
}

void MainWindow::on_actionNovelRevisions_triggered()
{

}

void MainWindow::on_actionNovelExport_triggered()
{

}

void MainWindow::on_actionNovelBind_triggered()
{

}

void MainWindow::on_actionNovelSaveAs_triggered()
{
    QString otherFile = QFileDialog::getSaveFileName(this,
                                                tr("Save Novel"),
                                                QString(),
                                                tr("Plotline File (*.pln)"));
    if (otherFile.isEmpty())
        return;
    if (!otherFile.endsWith(".pln"))
        otherFile.append(".pln");
    mOpenedFile = otherFile;

    emit saveNovel();
}

void MainWindow::on_actionNovelClose_triggered()
{
    emit MainWindow::destroy();
}

void MainWindow::on_MainWindow_destroyed()
{
    if (!mIsSaved)
    {
        QMessageBox *confirmSave = new QMessageBox(tr("Quit"),
            tr("Do you want to save the current novel?"),
            QMessageBox::Question, QMessageBox::Yes, QMessageBox::No,
                                              QMessageBox::NoButton,
                                              this);
        confirmSave->setModal(true);
        int result = confirmSave->exec();
        if (result == QMessageBox::Yes && mOpenedFile.isEmpty())
            emit saveNovel();
    }
}
