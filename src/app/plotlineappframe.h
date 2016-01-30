#ifndef PLOTLINEAPPFRAME_H
#define PLOTLINEAPPFRAME_H

#include <QWidget>
#include <QFrame>
#include "novel.h"

class MainWindow;

class PlotlineAppFrame : public QFrame
{
    Q_OBJECT

public:
    PlotlineAppFrame(MainWindow *mainWindow, QWidget *parent = 0);

    MainWindow *mainWindow() const;
    void setMainWindow(MainWindow *mainWindow);

protected:
    MainWindow *mMainWindow;

signals:
    void novelModified();

public slots:
    virtual void onNovelLoad() = 0;
    virtual void onNovelNew() = 0;
};

#include "mainwindow.h"

#endif // PLOTLINEAPPFRAME_H
