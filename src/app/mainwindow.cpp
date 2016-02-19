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

    mNovelFrame = new NovelFrame(this);
    mCharacterFrame = new CharacterFrame(this);
    mPlotFrame = new PlotFrame(this);
    mSceneFrame = new SceneFrame(this);
    mChapterFrame = new ChaptersFrame(this);

    frames = QList<PlotlineAppFrame *>();
    frames << mNovelFrame
           << mCharacterFrame
           << mPlotFrame
           << mSceneFrame
           << mChapterFrame;

    for (int i = 0; i < frames.count(); ++i) {
        ui->tabWidget->insertTab(i, frames[i], frameTitles[i]);
    }

    connectAll();

    mDistractions << ui->tabWidget->tabBar()
                  << menuWidget();
    for (QToolBar *toolbar : findChildren<QToolBar *>(""))
        mDistractions << toolbar;

    connect(mChapterFrame, SIGNAL(hideDistractions()),
            this, SLOT(onHideDistractions()));
    connect(mChapterFrame, SIGNAL(showDistractions()),
            this, SLOT(onShowDistractions()));

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
    mIsSaved = false;
}

void MainWindow::onSaveNovel()
{
    QSettings settings;
    QString projDir = settings.value(
                PreferencesDialog::DEFAULT_PROJECT_DIRECTORY,
                    QDir::homePath()).toString();
    if (mOpenedFile.isNull()){
        QString fileTypes = tr("Plotline Files (*.json *.pln);;All Files (*.*)");
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Novel"), projDir, fileTypes);
        if (fileName.isEmpty())
            return;
        mOpenedFile = fileName;
    }
    mNovel->writeTo(mOpenedFile);
    mIsSaved = true;
    QString path = mOpenedFile.isEmpty() ? "Untitled" : mOpenedFile;
    setWindowTitle("Plotline - " + path);
}

void MainWindow::onNovelNew()
{
}

void MainWindow::on_actionPreferences_triggered()
{
    mPrefDialog = new PreferencesDialog(this);
    mPrefDialog->exec();
}

void MainWindow::on_actionNovelNew_triggered()
{
    if (!mIsSaved)
    {
        int result = QMessageBox::question(this, tr("New Novel"),
            tr("Do you want to save the current novel?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
            QMessageBox::Save);
        if (result == QMessageBox::Save)
            emit saveNovel();
        if (result == QMessageBox::Cancel)
            return;
    }
    mNovel = new Novel(QString());
    mIsSaved = true;
    mOpenedFile = QString();
    emit novelLoaded();
}

void MainWindow::on_actionNovelOpen_triggered()
{
    QString fileTypes = tr("Plotline Files (*.json *.pln);;All Files (*.*)");
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Novel"), QString(), fileTypes);
    if (fileName.isEmpty())
        return;

    mOpenedFile = fileName;
    QString error;
    mNovel = Novel::readFrom(mOpenedFile, &error);
    if (!mNovel){
        QString message = tr("Could not open novel due to parse error.");
        if (!error.isEmpty())
            message += tr("\nThe error message is:\n") + error;
        QMessageBox::critical(this, tr("Could not open novel."),
                              message);
    }
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
    RevisionDialog *dialog = new RevisionDialog(this);
    dialog->show();
    emit mChapterFrame->revisionSet();
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
        int result = QMessageBox::question(this, tr("Quit"),
            tr("Do you want to save the current novel?"),
            QMessageBox::Save | QMessageBox::Discard,
            QMessageBox::Save);
        if (result == QMessageBox::Yes)
            emit saveNovel();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    emit mChapterFrame->showDistractions();
}

void MainWindow::disconnectAll()
{
    disconnect(this, SIGNAL(novelChanged()));
    disconnect(this, SIGNAL(saveNovel()));
    disconnect(this, SIGNAL(novelNew()));
    disconnect(this, SIGNAL(novelLoaded()));
    for (int i = 0; i < frames.count(); ++i) {
        disconnect(frames[i], SIGNAL(novelModified()));
        disconnect(this, SIGNAL(novelLoaded()));
        disconnect(this, SIGNAL(novelNew()));
    }
}

void MainWindow::connectAll()
{
    connect(this, SIGNAL(novelChanged()), this, SLOT(onNovelModified()));
    connect(this, SIGNAL(saveNovel()), this, SLOT(onSaveNovel()));
    connect(this, SIGNAL(novelNew()), this, SLOT(onNovelNew()));
    connect(this, SIGNAL(novelLoaded()),
            this, SLOT(onNovelLoaded()));
    for (int i = 0; i < frames.count(); ++i) {
        connect(frames[i], SIGNAL(novelModified()), this,
                SLOT(onNovelModified()));
        connect(this, SIGNAL(novelLoaded()), frames[i], SLOT(onNovelLoad()));
        connect(this, SIGNAL(novelNew()), frames[i], SLOT(onNovelNew()));
    }
}

Novel *MainWindow::novel() const
{
    return mNovel;
}

void MainWindow::setNovel(Novel *novel)
{
    mNovel = novel;
}

void MainWindow::openNovel(const QString &path)
{
    mOpenedFile = path;
    QString error = QString();
    mNovel = Novel::readFrom(path, &error);
    if (mNovel){
        emit novelLoaded();
        mIsSaved = true;
    } else {
        QString message = tr("Could not open novel due to parse error.");
        if (!error.isEmpty())
            message += tr("\nThe error message is:\n") + error;
        QMessageBox::critical(this, tr("Could not open novel."),
                              message);
    }
}

void MainWindow::openTab(const int index)
{
    qDebug() << "Opening tab" << index;
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::onNovelLoaded()
{
    QString path = mOpenedFile.isEmpty() ? "Untitled" : mOpenedFile;
    setWindowTitle("Plotline - " + path);
}

void MainWindow::onHideDistractions()
{
    QSettings settings;

    int mode = settings.value(PreferencesDialog::DISTRACTION_FREE_MODE,
                   QVariant((int) PreferencesDialog::ShowWindowed)).toInt();
    if (mode == PreferencesDialog::ShowWindowed){
        for (QWidget *widget : mDistractions)
            widget->hide();
        this->setMouseTracking(true);
    }
}

void MainWindow::onShowDistractions()
{
    for (QWidget *widget : mDistractions)
        widget->show();
}
