#ifndef CHAPTERSFRAME_H
#define CHAPTERSFRAME_H

#include <QWidgetList>
#include <QList>
#include "plotlineappframe.h"
#include "chaptermodel.h"
#include "markuphighlighter.h"
#include "scenelistdialog.h"
#include "fullscreeneditor.h"
#include "chapterfilter.h"

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
    ChapterFilter *mFilter;

    bool mHasDistractions = true;

    QWidgetList mDistractions;
    QTimer *mDistractionTimer;
    MarkupHighlighter *mHighlighter;

    static const int PlotlineRole = Qt::UserRole+1;

    void connectSlots();
    void disconnectSlots();
    void blockEditableSignals();
    void unblockEditableSignals();

signals:
    void chapterSelected();
    void revisionChanged();
    void revisionSet();
    void chapterModified();

    void hideDistractions();
    void showDistractions();

public slots:
    void onNovelLoad();
    void onNovelNew();

    void onChapterModified();
    void onChapterSelected();
    void onRevisionChanged();
    void onRevisionSet();
    void onHideDistractions();
    void onShowDistractions();

protected:
    void mouseMoveEvent(QMouseEvent *event);

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
//    void on_chapterContent_textChanged();
    void on_chapterDistractionFree_clicked();
    void onFullscreenEditorDestroyed(QObject *object);

    void clearLayout(bool enabled, bool clear);
    void onDistractionTimeout(void);
    void onChapterContentModified(int from, int charsAdded, int charsRemoved);
};

#endif // CHAPTERSFRAME_H
