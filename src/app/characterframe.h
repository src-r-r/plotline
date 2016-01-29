#ifndef CHARACTERFRAME_H
#define CHARACTERFRAME_H

#include <QFrame>
#include "plotlineappframe.h"
#include "characteritemmodel.h"

namespace Ui {
class CharacterFrame;
}

class CharacterFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit CharacterFrame(Novel *novel, QWidget *parent = 0);
    ~CharacterFrame();

public slots:
    void onNovelLoad();
    void onNovelNew();

private slots:
    void on_addCharacter_clicked();

private:
    Ui::CharacterFrame *ui;

    CharacterItemModel *mItemModel;
};

#endif // CHARACTERFRAME_H
