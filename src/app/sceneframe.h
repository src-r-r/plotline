#ifndef SCENEFRAME_H
#define SCENEFRAME_H

#include "plotlineappframe.h"

namespace Ui {
class SceneFrame;
}

class SceneFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit SceneFrame(MainWindow *mainWindow, QWidget *parent = 0);
    ~SceneFrame();

public slots:
    void onNovelLoad();
    void onNovelNew();

private:
    Ui::SceneFrame *ui;
};

#endif // SCENEFRAME_H
