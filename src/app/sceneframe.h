#ifndef SCENEFRAME_H
#define SCENEFRAME_H

#include <QFrame>

namespace Ui {
class SceneFrame;
}

class SceneFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SceneFrame(QWidget *parent = 0);
    ~SceneFrame();

private:
    Ui::SceneFrame *ui;
};

#endif // SCENEFRAME_H
