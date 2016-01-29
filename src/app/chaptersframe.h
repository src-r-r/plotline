#ifndef CHAPTERSFRAME_H
#define CHAPTERSFRAME_H

#include "plotlineappframe.h"

namespace Ui {
class ChaptersFrame;
}

class ChaptersFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit ChaptersFrame(Novel *novel, QWidget *parent = 0);
    ~ChaptersFrame();

private:
    Ui::ChaptersFrame *ui;

signals:
    void novelModified();

public slots:
    void onNovelLoad();
    void onNovelNew();
};

#endif // CHAPTERSFRAME_H
