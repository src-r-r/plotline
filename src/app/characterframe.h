#ifndef CHARACTERFRAME_H
#define CHARACTERFRAME_H

#include <QFrame>

namespace Ui {
class CharacterFrame;
}

class CharacterFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CharacterFrame(QWidget *parent = 0);
    ~CharacterFrame();

private:
    Ui::CharacterFrame *ui;
};

#endif // CHARACTERFRAME_H
