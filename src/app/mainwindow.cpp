#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    mIsSaved = false;
    mSelectedCharacter = 0;

    // Set up the models
    mNovel = new Novel("Untitled");
    mCharacterItemModel = new CharacterItemModel(mNovel);
    ui->characterList->setModel(mCharacterItemModel);

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
    delete mSelectedCharacter;
}

void MainWindow::on_addCharacter_clicked()
{
    qDebug() << "Inserting a character";
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

void MainWindow::on_actionOpen_Novel_triggered()
{
    QString fileTypes = tr("Plotline Files (*.json *.pln);;All Files (*.*)");
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Novel"), QString(), fileTypes);
    if (fileName.isEmpty())
        return;
    QFile *jsonFile = new QFile(fileName);
    jsonFile->open(QFile::ReadOnly);
    QByteArray jsonData = jsonFile->readAll();
    jsonFile->close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    mNovel = Novel::deserialize(doc.object());
    mOpenedFile = fileName;
    qDebug() << "Opened novel " << mNovel->getWorkingTitle();
    emit novelLoaded();
}

void MainWindow::on_actionSave_triggered()
{
    emit saveNovel();
}

void MainWindow::on_tenseCombobox_currentIndexChanged(int index)
{
    switch (index) {
    case TENSE_PAST:
        mNovel->setTense(Novel::Past);
        break;
    case TENSE_PRESENT:
        mNovel->setTense(Novel::Present);
        break;
    case TENSE_FUTURE:
        mNovel->setTense(Novel::Future);
        break;
    case TENSE_OTHER:
    default:
        mNovel->setTense(Novel::OtherTense);
        break;
    }

    emit updateNovel();
}

void MainWindow::on_pointOfViewComboBox_currentIndexChanged(int index)
{
    Novel::PointOfView pointOfView = Novel::FirstPersonSingular;
    switch (index)
    {
    case POV_1_1:
        pointOfView = Novel::FirstPersonSingular;
        break;
    case POV_1_P:
        pointOfView = Novel::FirstPersonPlural;
        break;
    case POV_2_1:
        pointOfView = Novel::SecondPersonSingular;
        break;
    case POV_2_P:
        pointOfView = Novel::SecondPersonPlural;
        break;
    case POV_3_1:
        pointOfView = Novel::ThirdPersonSingular;
        break;
    case POV_3_P:
        pointOfView = Novel::ThirdPersonPlural;
        break;
    case POV_OTHER:
    default:
        pointOfView = Novel::OtherPointOfView;
        break;
    }

    mNovel->setPointOfView(pointOfView);

    emit updateNovel();
}


void MainWindow::on_actionNewNovel_triggered()
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

void MainWindow::onSaveNovel()
{
    if (mOpenedFile.isEmpty()){
        mOpenedFile = QFileDialog::getSaveFileName(this,
                                                    tr("Save Novel"),
                                                    QString(),
                                                    tr("Plotline File (*.pln)"));
        if (mOpenedFile.isEmpty())
            return;

        if (!mOpenedFile.endsWith(".pln"))
            mOpenedFile.append(".pln");
    }
    QJsonObject jNovel = mNovel->serialize();
    QFile *outFile = new QFile(mOpenedFile);
    outFile->open(QFile::WriteOnly);
    outFile->write(QJsonDocument(jNovel).toJson());
    outFile->close();
    setWindowTitle("Plotline - " + (mOpenedFile.isEmpty() ? "Untitled"
                                                          : mOpenedFile));
}

void MainWindow::onCharacterSelectionChanged(const QModelIndex &current)
{
    qDebug() << "Updating UI to match character" << mSelectedCharacter->getId();
    ui->scrollAreaCharDetails->setEnabled(current.isValid());
    ui->deleteCharacter->setEnabled(current.isValid());
    if (!current.isValid())
        return;
    ui->characterName->setText(mSelectedCharacter->getName());
    ui->characterNickname->setText(mSelectedCharacter->getNickname());
    ui->characterLabel->setText(mSelectedCharacter->getLabel());
}

void MainWindow::onCurrentCharacterChanged()
{
    if (!mSelectedCharacter)
        return;
    mSelectedCharacter->setName(ui->characterName->text());
    mSelectedCharacter->setNickname(ui->characterNickname->text());
    mSelectedCharacter->setLabel(ui->characterLabel->text());

    // Update the list view
    QModelIndex index = ui->characterList->selectionModel()->currentIndex();
    mCharacterItemModel->setData(index, mSelectedCharacter->getName());

    //mSelectedCharacter->setHeadshot();
}

void MainWindow::onNovelLoaded()
{
    qDebug() << "Loading novel " << mNovel->getWorkingTitle();
    int povIndex = POV_OTHER,
            tenseIndex = TENSE_OTHER;
    switch (mNovel->getPointOfView())
    {
    case Novel::FirstPersonSingular:
        povIndex = POV_1_1;
        break;
    case Novel::FirstPersonPlural:
        povIndex = POV_1_P;
        break;
    case Novel::SecondPersonSingular:
        povIndex = POV_2_1;
        break;
    case Novel::SecondPersonPlural:
        povIndex = POV_2_P;
        break;
    case Novel::ThirdPersonSingular:
        povIndex = POV_3_1;
        break;
    case Novel::ThirdPersonPlural:
        povIndex = POV_3_P;
        break;
    case Novel::OtherPointOfView:
    default:
        povIndex = POV_OTHER;
        break;
    }

    switch(mNovel->getTense())
    {
    case Novel::Past:
        tenseIndex = TENSE_PAST;
        break;
    case Novel::Present:
        tenseIndex = TENSE_PRESENT;
        break;
    case Novel::Future:
        tenseIndex = TENSE_FUTURE;
        break;
    case Novel::OtherTense:
    default:
        tenseIndex = TENSE_OTHER;
        break;
    }

    ui->workingTitleLineEdit->setText(mNovel->getWorkingTitle());
    ui->genreLineEdit->setText(mNovel->getGenre());
    ui->settingLineEdit->setText(mNovel->getSetting());
    ui->pointOfViewComboBox->setCurrentIndex(povIndex);
    ui->tenseCombobox->setCurrentIndex(tenseIndex);

    // Load the models
    mCharacterItemModel = new CharacterItemModel(mNovel);
    ui->characterList->setModel(mCharacterItemModel);

    setWindowTitle("Plotline - " + mOpenedFile);
    mIsSaved = true;
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
