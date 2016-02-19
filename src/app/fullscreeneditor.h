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
#include <QTextEdit>

namespace Ui {
class FullScreenEditor;
}

class FullScreenEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit FullScreenEditor(QWidget *parent = 0);
    explicit FullScreenEditor(QTextEdit *mEditor, QWidget *parent=0);
    ~FullScreenEditor();

    bool isFullScreen();

public slots:

signals:
    void contentChanged();

private slots:
    void on_chapterContent_textChanged();
    void onEscapeTriggered(bool triggered);

private:
    Ui::FullScreenEditor *ui;

    QTextEdit *mEditor;
    MarkupHighlighter *mHighlighter;
};

#endif // FULLSCREENEDITOR_H