#include "characterframe.h"
#include "ui_characterframe.h"

CharacterFrame::CharacterFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharacterFrame)
{
    ui->setupUi(this);
}

CharacterFrame::~CharacterFrame()
{
    delete ui;
}
