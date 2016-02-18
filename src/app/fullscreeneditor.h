#ifndef FULLSCREENEDITOR_H
#define FULLSCREENEDITOR_H

#include <QMainWindow>
#include "revision.h"
#include <QTableView>
#include <QAbstractItemModel>
#include <chaptermodel.h>
#include <preferencesdialog.h>
#include "markuphighlighter.h"
#include <QScreen>

namespace Ui {
class FullScreenEditor;
}

class FullScreenEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FullScreenEditor(QWidget *parent = 0);
    explicit FullScreenEditor(QTableView *chapterTable, QWidget *parent=0);
    ~FullScreenEditor();

    bool isFullScreen();

public slots:

    void onContentsChanged();

private:
    Ui::FullScreenEditor *ui;

    QTableView *mChapterTable;
    MarkupHighlighter *mHighlighter;
};

#endif // FULLSCREENEDITOR_H
