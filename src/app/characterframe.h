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
    explicit CharacterFrame(MainWindow *mainWindow, QWidget *parent = 0);
    ~CharacterFrame();

signals:
    void characterModified();
    void characterListModified();

public slots:
    void onNovelLoad();
    void onNovelNew();

    void on_addCharacter_clicked();

    void onCharacterModified();
    void onCharacterListModified();

    void on_characterList_activated(const QModelIndex &index);

    void on_characterList_clicked(const QModelIndex &index);

//    void on_characterName_cursorPositionChanged(int arg1, int arg2);

    void on_characterName_textChanged(const QString &arg1);

private slots:
    void on_characterName_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::CharacterFrame *ui;

    CharacterItemModel *mItemModel;
    Character *mSelectedCharacter;

    // methods
    void setCharacterHeadshot(Character *c);
    void clearCharacterHeadshot();
};

#endif // CHARACTERFRAME_H
