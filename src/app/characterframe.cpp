#include "characterframe.h"
#include "ui_characterframe.h"

CharacterFrame::CharacterFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::CharacterFrame)
{
    ui->setupUi(this);
    mItemModel = new CharacterItemModel(mMainWindow->novel());
}

CharacterFrame::~CharacterFrame()
{
    delete ui;
}

void CharacterFrame::onNovelLoad()
{
    mItemModel = new CharacterItemModel(mainWindow()->novel());
}

void CharacterFrame::onNovelNew()
{
    mItemModel = new CharacterItemModel(mainWindow()->novel());
}

void CharacterFrame::on_addCharacter_clicked()
{
    mItemModel->addCharacter();
    emit novelModified();
}
