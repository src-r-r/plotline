#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    mIsSaved = false;
    mSelectedCharacter = 0;


    mNovel = new Novel("Untitled");
    // Load the models
    mCharacterItemModel = new CharacterItemModel(mNovel);
    ui->characterList->setModel(mCharacterItemModel);
    mPlotlineItemModel = new PlotlineItemModel(mNovel);
    ui->plotlineTable->setModel(mPlotlineItemModel);

    emit novelLoaded();


    // Set the widths for the plotline table.
    float widths[3] = {0.50, 0.50, 0.30};
    float totalWidth = ui->plotlineTable->width();
    for (int i = 0; i < 3; ++i){
        float w = totalWidth * widths[i];
        ui->plotlineTable->setColumnWidth(i, w);
    }
    ui->plotlineTable->horizontalHeader()->setStretchLastSection(true);

    // Connect signals.
    connect(this, SIGNAL(novelChanged()), this, SLOT(updateNovel()));
    connect(this, SIGNAL(saveNovel()), this, SLOT(onSaveNovel()));
    connect(this, SIGNAL(novelLoaded()), this, SLOT(onNovelLoaded()));
    connect(this, SIGNAL(characterSelectionChanged(const QModelIndex&)),
            this, SLOT(onCharacterSelectionChanged(const QModelIndex &)));

    emit characterListChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mNovel;
    delete mCharacterItemModel;
    delete mPlotlineItemDelegate;
    delete mPlotlineItemModel;
}

void MainWindow::on_addCharacter_clicked()
{
    mCharacterItemModel->addCharacter();
    emit characterListChanged();
}

void MainWindow::on_workingTitleLineEdit_textEdited(const QString &arg1)
{
    mNovel->setWorkingTitle(arg1);
    if (arg1.length() == 0)
        setWindowTitle("Plotline");
    else
        setWindowTitle("Plotline - " + arg1);
    emit novelChanged();
}

void MainWindow::on_genreLineEdit_textChanged(const QString &arg1)
{
    mNovel->setGenre(arg1);
    emit novelChanged();
}

void MainWindow::on_settingLineEdit_textChanged(const QString &arg1)
{
    mNovel->setSetting(arg1);
    emit novelChanged();
}

void MainWindow::on_tenseCombobox_currentIndexChanged(int index)
{
    mNovel->setTense((Novel::Tense) index);
    emit updateNovel();
}

void MainWindow::on_pointOfViewComboBox_currentIndexChanged(int index)
{
    mNovel->setPointOfView((Novel::PointOfView) index);
    emit updateNovel();
}

///////
/// Custom slots
///////

void MainWindow::updateNovel()
{
    mIsSaved = false;
    setWindowTitle("Plotline - " + (mOpenedFile.isEmpty() ? "Untitled"
                                                         : mOpenedFile) +
                   " *");
    mNovel->setWorkingTitle(ui->workingTitleLineEdit->text());
    mNovel->setGenre(ui->genreLineEdit->text());
}

void MainWindow::onCharacterListChanged()
{
    mCharacterItemModel = new CharacterItemModel(mNovel);
    if (mNovel->getCharacters().size() > 0)
        ui->scrollAreaCharDetails->setEnabled(true);
    else
        ui->scrollAreaCharDetails->setEnabled(false);
}

void MainWindow::onCharacterSelectionChanged(const QModelIndex &current)
{
    qDebug() << "Updating UI to match character" << mSelectedCharacter->getId();
    ui->scrollAreaCharDetails->setEnabled(current.isValid());
    ui->deleteCharacter->setEnabled(current.isValid());
    if (!current.isValid())
        return;

    setCurrentCharacterHeadshot();
    ui->characterName->setText(mSelectedCharacter->getName());
    ui->characterNickname->setText(mSelectedCharacter->getNickname());
    ui->characterLabel->setText(mSelectedCharacter->getLabel());
}

void MainWindow::onCurrentCharacterChanged()
{
    if (!mSelectedCharacter){
        return;
    }
    mSelectedCharacter->setName(ui->characterName->text());
    mSelectedCharacter->setNickname(ui->characterNickname->text());
    mSelectedCharacter->setLabel(ui->characterLabel->text());

    // Update the list view
    QModelIndex index = ui->characterList->selectionModel()->currentIndex();
    mCharacterItemModel->setData(index, mSelectedCharacter->getName());

    //mSelectedCharacter->setHeadshot();

    emit novelChanged();
}

void MainWindow::onNovelLoaded()
{
    qDebug() << "Loading novel " << mNovel->getWorkingTitle();

    ui->workingTitleLineEdit->setText(mNovel->getWorkingTitle());
    ui->genreLineEdit->setText(mNovel->getGenre());
    ui->settingLineEdit->setText(mNovel->getSetting());
    ui->pointOfViewComboBox->setCurrentIndex(mNovel->getPointOfView());
    ui->tenseCombobox->setCurrentIndex(mNovel->getTense());

    emit mNovel->plotlinesChanged();

    // Clear the character detail area.
    ui->characterName->clear();
    ui->characterLabel->clear();
    ui->characterNickname->clear();
    ui->scrollAreaCharDetails->setDisabled(true);

    // Set default selections
    if (!mNovel->getCharacters().empty()){
        QModelIndex i = mCharacterItemModel->index(0);
        ui->characterList->setCurrentIndex(i);
        mSelectedCharacter = mNovel->getCharacters()[0];
        emit characterSelectionChanged(i);
    }

    setWindowTitle("Plotline - " + mOpenedFile);
    mIsSaved = true;
}

void MainWindow::onSaveNovel()
{
    mNovel->writeTo(mOpenedFile);
    setWindowTitle("Plotline - " + (mOpenedFile.isEmpty() ? "Untitled"
                                                          : mOpenedFile));
}

void MainWindow::on_deleteCharacter_clicked()
{
    QItemSelectionModel *model = ui->characterList->selectionModel();
    QModelIndexList rows = model->selectedRows();
    QStringList names = QStringList();
    Character *c = 0;
    for (int i = 0; i < rows.size(); ++i){
        c = mNovel->getCharacters()[rows[i].row()];
        names << c->getName();
    }

    QMessageBox *confirmSave = new QMessageBox(tr("DeleteCharacters"),
        QString("Do you want to delete the characters:") + names.join("\n- "),
        QMessageBox::Question, QMessageBox::Yes, QMessageBox::No,
                                          QMessageBox::NoButton,
                                          this);
    confirmSave->setModal(true);
    int res = confirmSave->exec();
    if (QMessageBox::Yes == res){
        for (int i = 0; i < rows.size(); ++i){
            mNovel->getCharacters().removeAt(rows[i].row());
            mCharacterItemModel->removeRow(rows[i].row());
        }
        mSelectedCharacter = 0;
    }
    emit characterListChanged();
}

void MainWindow::on_characterList_clicked(const QModelIndex &index)
{
    ui->deleteCharacter->setEnabled(index.isValid());
    ui->scrollAreaCharDetails->setEnabled(index.isValid());
    if (index.isValid()){
        qDebug() << "Selecting new character at index" << index.row();
        mSelectedCharacter = mNovel->getCharacters()[index.row()];
    } else {
        qDebug() << "Invalid index:" << index;
    }
    emit characterSelectionChanged(index);
}

void MainWindow::on_characterName_textChanged(const QString &arg1)
{
    mSelectedCharacter->setName(arg1);
    ui->characterLabel->setText(Character::generateLabel(arg1));
    emit currentCharacterChanged();
}

void MainWindow::on_characterNickname_textChanged(const QString &arg1)
{
    mSelectedCharacter->setNickname(arg1);
    emit currentCharacterChanged();
}

void MainWindow::on_characterLabel_textChanged(const QString &arg1)
{
    mSelectedCharacter->setLabel(arg1);
    emit currentCharacterChanged();
}

void MainWindow::on_chooseHeadshot_clicked()
{
    QSettings settings;
    QString defaultDir = settings.value(PreferencesDialog
                                        ::DEFAULT_HEADSHOT_DIRECTORY,
                                        QDir::homePath()).toString();
    QString fileTypes = tr("Image Files (*.png *.jpg *.jpeg *.gif)");
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Headshot"), defaultDir, fileTypes);
    if (fileName.isNull())
        return;

    QImage headshot = QImage(fileName);
    mSelectedCharacter->setHeadshot(headshot);
    setCurrentCharacterHeadshot();
    emit currentCharacterChanged();
}

/**
 * @brief MainWindow::setCurrentCharacterHeadshot
 * For the selected character (in the character tab) set the GraphicsView
 * from the stored QImage.
 */
void MainWindow::setCurrentCharacterHeadshot()
{
    if (!mSelectedCharacter)
        return;

    int height = ui->characterHeadshot->size().height(),
            width = ui->characterHeadshot->size().width();
    QPixmap headshotPix = QPixmap::fromImage(mSelectedCharacter->getHeadshot());
    // Determine how (if at all) the image should be scaled.
    if (height > width)
        headshotPix = headshotPix.scaledToWidth(width);
    else if (width > height)
        headshotPix = headshotPix.scaledToHeight(height);

    QGraphicsScene *scene = new QGraphicsScene();

    // Scale so that we won't have to scroll the GraphicsView
    scene->addPixmap(headshotPix);

    ui->characterHeadshot->setScene(scene);
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

void MainWindow::on_addPlotline_clicked()
{
    PlotlineDialog *plotlineDialog = new PlotlineDialog(mNovel);
    plotlineDialog->exec();
}
