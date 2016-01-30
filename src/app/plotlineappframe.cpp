#include "plotlineappframe.h"

#include "novel.h"

PlotlineAppFrame::PlotlineAppFrame(MainWindow *mainWindow, QWidget *parent) : QFrame(parent)
{
    mMainWindow = mainWindow;
}

MainWindow *PlotlineAppFrame::mainWindow() const
{
    return mMainWindow;
}

void PlotlineAppFrame::setMainWindow(MainWindow *mainWindow)
{
    mMainWindow = mainWindow;
}
