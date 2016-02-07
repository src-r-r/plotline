#ifndef CHAPTERSFRAME_H
#define CHAPTERSFRAME_H

#include "plotlineappframe.h"
#include "chaptermodel.h"

class PlotlineAppFrame;

namespace Ui {
class ChaptersFrame;
}

class ChaptersFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit ChaptersFrame(MainWindow *mainWindow, QWidget *parent = 0);
    ~ChaptersFrame();

private:
    Ui::ChaptersFrame *ui;

    Chapter *mSelectedChapter;
    ChapterModel *mModel;

signals:
    void chapterSelected();
    void revisionChanged();

public slots:
    void onNovelLoad();
    void onNovelNew();

    void onChapterSelected();
    void onRevisionChanged();

private slots:
    void on_chapterFilter_activated(int index);
    void on_addChapter_clicked();
    void on_archiveChapter_clicked();
    void on_deleteChapter_clicked();
    void on_assignScenes_clicked();
    void on_chapterTitle_textEdited(const QString &arg1);
    void on_chapterTable_activated(const QModelIndex &index);
    void on_chapterTable_clicked(const QModelIndex &index);
    void on_chapterComplete_toggled(bool checked);
    void on_chapterRevision_valueChanged(int arg1);
};

#endif // CHAPTERSFRAME_H
