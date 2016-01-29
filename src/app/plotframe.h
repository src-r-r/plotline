#ifndef PLOTFRAME_H
#define PLOTFRAME_H

#include <QFrame>

namespace Ui {
class PlotFrame;
}

class PlotFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PlotFrame(QWidget *parent = 0);
    ~PlotFrame();

private:
    Ui::PlotFrame *ui;
};

#endif // PLOTFRAME_H
