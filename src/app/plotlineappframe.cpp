#include "plotlineappframe.h"

#include "novel.h"

PlotlineAppFrame::PlotlineAppFrame(Novel *novel, QWidget *parent) : QFrame(parent)
{
    mNovel = novel;
}


Novel *PlotlineAppFrame::novel() const
{
    return mNovel;
}

void PlotlineAppFrame::setNovel(Novel *novel)
{
    mNovel = novel;
}
