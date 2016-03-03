#include "savethread.h"

void SaveThread::run()
{
    mNovel->writeTo(mOpenedFile);
}

SaveThread::SaveThread(Novel *novel, const QString &openedFile)
{
    mNovel = novel;
    mOpenedFile = openedFile;
}
