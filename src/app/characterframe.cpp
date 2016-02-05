#include "characterframe.h"
#include "ui_characterframe.h"

CharacterFrame::CharacterFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::CharacterFrame)
{
    ui->setupUi(this);
    mItemModel = new CharacterItemModel(mMainWindow->novel());
    ui->characterList->setModel(mItemModel);

    // connect signals
    connect(this, SIGNAL(characterListModified()), this,
            SLOT(onCharacterListModified()));
    connect(this, SIGNAL(characterModified()), this,
            SLOT(onCharacterModified()));
}

CharacterFrame::~CharacterFrame()
{
    delete mItemModel;
    delete ui;
}

void CharacterFrame::onNovelLoad()
{
    mItemModel->removeRows(0, mItemModel->rowCount());
    delete mItemModel;
    mItemModel = new CharacterItemModel(mainWindow()->novel());
    QList<Character *> characters = mainWindow()->novel()->characters();
    int row = 0;
    QModelIndex index;
    for (Character *c : characters){
        row = mItemModel->rowCount();
        mItemModel->insertRows(row, 1);
        index = mItemModel->index(row);
        mItemModel->setData(index, c->name());
        mItemModel->setData(index, c->color(), Qt::BackgroundRole);
        mItemModel->setData(index, QVariant(c->id()),
                            CharacterItemModel::CharacterIdRole);
        qDebug() << index.row() << "-" << "Character ID =" << c->id() << "?"
                 << mItemModel->data(index, CharacterItemModel::CharacterIdRole)
                    .toInt();
    }
    ui->characterList->setModel(mItemModel);

    // Automatically select the first item in the list.
    if (mItemModel->rowCount() > 0)
        ui->characterList->setCurrentIndex(mItemModel->index(0));
}

void CharacterFrame::onNovelNew()
{
    while (mItemModel->rowCount() > 0) mItemModel->removeRow(0);
    ui->deleteCharacter->setDisabled(true);
    ui->archiveCharacter->setDisabled(true);
    ui->characterName->clear();
    ui->characterLabel->clear();
    ui->characterNickname->clear();
    clearCharacterHeadshot();
    ui->scrollAreaCharDetails->setDisabled(true);
}

void CharacterFrame::on_addCharacter_clicked()
{
    Character *c = new Character("New Character");

    int row = mItemModel->rowCount();

    mainWindow()->novel()->addCharacter(c);
    mItemModel->insertRows(row, 1);

    QModelIndex index = mItemModel->index(row);
    mItemModel->setData(index, c->name(), Qt::DisplayRole|Qt::EditRole);
    mItemModel->setData(index, c->color(), Qt::BackgroundRole);
    mItemModel->setData(index, QVariant(c->id()),
                        CharacterItemModel::CharacterIdRole);

    emit characterListModified();
    ui->characterList->setCurrentIndex(index);
    emit ui->characterList->activated(mItemModel->lastRow());
}

void CharacterFrame::onCharacterListModified()
{
    ui->scrollAreaCharDetails->setEnabled(mItemModel->rowCount() > 0);
    emit novelModified();
}

void CharacterFrame::onCharacterModified()
{
    QModelIndex index = ui->characterList->currentIndex();
    mItemModel->setData(index, mSelectedCharacter->name(),
                        Qt::DisplayRole|Qt::EditRole);
    mItemModel->setData(index, mSelectedCharacter->color(),
                        Qt::BackgroundRole);
    emit novelModified();
}

void CharacterFrame::on_characterList_activated(const QModelIndex &index)
{
    if (!index.isValid()){
        qWarning() << "Invalid index";
        return;
    }

    int characterId = mItemModel->data(index,
                                       CharacterItemModel::CharacterIdRole)
            .toInt();

    ui->scrollAreaCharDetails->setEnabled(true);

    qDebug() << "Selecting character (id=" << characterId << ")";
    mSelectedCharacter = mMainWindow->novel()->character(characterId);

    ui->characterName->setText(mSelectedCharacter->name());
    ui->characterNickname->setText(mSelectedCharacter->nickname());
    ui->characterLabel->setText(mSelectedCharacter->label());

    setCharacterHeadshot(mSelectedCharacter);

    setButtonColor(mSelectedCharacter->color());

    ui->deleteCharacter->setEnabled(true);
    ui->archiveCharacter->setEnabled(true);
}

void CharacterFrame::setCharacterHeadshot(Character *c)
{
    QGraphicsScene *scene = new QGraphicsScene();

    int h = ui->characterHeadshot->geometry().height(),
            w = ui->characterHeadshot->geometry().width();

    QImage headshot = c->getHeadshot().scaledToWidth(w-2)
            .scaledToHeight(h-2);
    scene->addPixmap(QPixmap::fromImage(headshot));
    ui->characterHeadshot->setScene(scene);
}

void CharacterFrame::clearCharacterHeadshot()
{
    QList<QGraphicsItem *> items = ui->characterHeadshot->scene()->items();
    for (QGraphicsItem *item : items)
        ui->characterHeadshot->scene()->removeItem(item);
}

void CharacterFrame::setButtonColor(const QColor &color)
{
    if (!color.isValid())
        clearButtonColor();
    QImage image = QImage(40, 20, QImage::Format_RGB32);
    image.fill(color);
    ui->characterColor->setIcon(QIcon(QPixmap::fromImage(image)));
}

void CharacterFrame::clearButtonColor()
{
    QString filename = "qrc:/images/images/edit-clear-locationbar-rtl.png";
    ui->characterColor->setIcon(QIcon(QPixmap(filename)));
}

void CharacterFrame::on_characterList_clicked(const QModelIndex &index)
{
    on_characterList_activated(index);
}

void CharacterFrame::on_characterName_textChanged(const QString &arg1)
{
    mSelectedCharacter->setName(arg1);
    mSelectedCharacter->setLabel(Character::generateLabel(arg1));
    mItemModel->setData(ui->characterList->currentIndex(), mSelectedCharacter->name());
    ui->characterLabel->setText(mSelectedCharacter->label());
    emit characterModified();
}

void CharacterFrame::on_characterName_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
    on_characterName_textChanged(ui->characterName->text());
}

void CharacterFrame::on_characterColor_clicked()
{
    QColor color = QColorDialog::getColor(mSelectedCharacter->color());
    mSelectedCharacter->setColor(color);
    emit characterModified();
}
