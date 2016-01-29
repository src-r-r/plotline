#ifndef CHAPTERSFRAME_H
#define CHAPTERSFRAME_H

#include <QFrame>

namespace Ui {
class ChaptersFrame;
}

class ChaptersFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ChaptersFrame(QWidget *parent = 0);
    ~ChaptersFrame();

private:
    Ui::ChaptersFrame *ui;
};

#endif // CHAPTERSFRAME_H
