#ifndef CHAPTERSFRAME_H
#define CHAPTERSFRAME_H

#include "plotlineappframe.h"

class PlotlineAppFrame;

namespace Ui {
class ChaptersFrame;
}

class ChaptersFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit ChaptersFrame(MainWindow *mainWindow, QWidget *parent = 0);
    ~ChaptersFrame();

private:
    Ui::ChaptersFrame *ui;

public slots:
    void onNovelLoad();
    void onNovelNew();
};

#endif // CHAPTERSFRAME_H
