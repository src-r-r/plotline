#ifndef PLOTLINEAPPFRAME_H
#define PLOTLINEAPPFRAME_H

#include <QWidget>
#include <QFrame>
#include "novel.h"

class PlotlineAppFrame : public QFrame
{
    Q_OBJECT

public:
    PlotlineAppFrame(Novel *mNovel, QWidget *parent = 0);

    Novel *novel() const;
    void setNovel(Novel *novel);

protected:
    Novel *mNovel;

signals:
    void novelModified();

public slots:
    virtual void onNovelLoad() = 0;
    virtual void onNovelNew() = 0;
};

#endif // PLOTLINEAPPFRAME_H
