#ifndef SCENEFRAME_H
#define SCENEFRAME_H

#include "plotlineappframe.h"
#include <QMap>
#include <QWidget>
#include <QMenu>
#include <QCompleter>
#include <QDrag>
#include "sceneitemmodel.h"
#include "modelcheckbox.h"
#include "characterparser.h"
#include "characterhighlighter.h"
#include "utils.h"
#include "scenefilter.h"

namespace Ui {
class SceneFrame;
}

class SceneFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit SceneFrame(MainWindow *mainWindow, QWidget *parent = 0);
    ~SceneFrame();

signals:

public slots:
    void onNovelLoad();
    void onNovelNew();

protected:

private slots:
    void on_detectCharacters_clicked();
    void on_sceneList_activated(const QModelIndex &index);
    void on_addScene_clicked();
    void on_archiveScene_clicked();
    void on_deleteScene_clicked();
    void onCharacterToggled(bool checked, QVariant value);
    void on_sceneList_clicked(const QModelIndex &index);
    void on_plotline_activated(int index);
//    void on_sceneHeadline_textChanged();
//    void on_sceneAction_textChanged();
    void onHeadlineModified();

    void onActionModified();

    void on_sceneList_customContextMenuRequested(const QPoint &pos);

    void on_filterScenes_activated(int index);

    void on_searchScenes_textEdited(const QString &arg1);

    void on_sceneList_indexesMoved(const QModelIndexList &indexes);

    void on_characterSearch_textChanged(const QString &arg1);

private:

    void disconnectSlots();
    void connectSlots();
    void blockEditableSignals();
    void unblockEditableSignals();

    QList<Character *> _getSelectedCharacters(bool pov=false);
    void _setSelectedCharacters(QList<Character *> characters, bool pov=false);

    QList<Character *> getSelectedCharacters();
    void setSelectedCharacters(QList<Character *> characters);

    QList<Character *> getSelectedPointsOfView();
    void setSelectedPointsOfView(QList<Character *> characters);

    void findCharacters(const QTextEdit *editor);
    void detectLabelStart(QTextEdit *editor);
    void fillPlotlineCombo(Plotline *selected = 0);

    Ui::SceneFrame *ui;

    Scene *mSelectedScene = 0;
    QList<ModelCheckbox *> mCharacters;
    SceneFilter *mFilter;
    QPoint mDragPos;

    class HeadlineUpdater : public QRunnable
    {
    public:
        HeadlineUpdater(QTextEdit *field, QListView *listView);
        void run();
    private:
        QTextEdit *mField;
        QListView *mListView;
    };

    CharacterHighlighter *mActionHighlighter,
        *mHeadlineHighlighter;
    QCompleter *mHeadlineCompleter,
        *mActionCompleter;
};

#endif // SCENEFRAME_H
