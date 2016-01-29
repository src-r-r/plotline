#include "characterframe.h"
#include "ui_characterframe.h"

CharacterFrame::CharacterFrame(Novel *novel, QWidget *parent) :
    PlotlineAppFrame(novel, parent),
    ui(new Ui::CharacterFrame)
{
    ui->setupUi(this);
    mItemModel = new CharacterItemModel(mNovel);
}

CharacterFrame::~CharacterFrame()
{
    delete ui;
}

void CharacterFrame::onNovelLoad()
{
    mItemModel = new CharacterItemModel(mNovel);
}

void CharacterFrame::onNovelNew()
{
    mItemModel = new CharacterItemModel(mNovel);
}

void CharacterFrame::on_addCharacter_clicked()
{
    mItemModel->addCharacter();
    emit novelModified();
}
