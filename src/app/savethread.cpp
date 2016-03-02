#include "savethread.h"

void SaveThread::run()
{
    mMainWindow->setDisabled(true);
    QLabel *label = new QLabel(
                tr("Writing novel to \"")
                + mOpenedFile + tr("\""), mMainWindow->statusBar()
                );
    mMainWindow->statusBar()->addWidget(label);
    // Disable the interface.
    mNovel->writeTo(mOpenedFile);
    mMainWindow->setEnabled(true);
    mMainWindow->statusBar()->removeWidget(label);
}

SaveThread::SaveThread(MainWindow *mainWindow, Novel *novel,
                                   const QString &openedFile)
{
    mMainWindow = mainWindow;
    mNovel = novel;
    mOpenedFile = openedFile;
}
