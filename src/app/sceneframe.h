#ifndef SCENEFRAME_H
#define SCENEFRAME_H

#include "plotlineappframe.h"
#include <QMap>
#include <QWidget>
#include <QMenu>
#include <QCompleter>
#include "sceneitemmodel.h"
#include "modelcheckbox.h"
#include "characterparser.h"
#include "characterhighlighter.h"
#include "utils.h"

namespace Ui {
class SceneFrame;
}

class SceneFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit SceneFrame(MainWindow *mainWindow, QWidget *parent = 0);
    ~SceneFrame();

    QCompleter *completer() const;
    void setCompleter(QCompleter *completer);

signals:

public slots:
    void onNovelLoad();
    void onNovelNew();

private slots:
    void on_detectCharacters_clicked();
    void on_sceneList_activated(const QModelIndex &index);
    void on_addScene_clicked();
    void on_archiveScene_clicked();
    void on_deleteScene_clicked();
    void onCharacterToggled(bool checked, QVariant value);
    void on_sceneList_clicked(const QModelIndex &index);
    void on_plotline_activated(int index);
    void on_sceneHeadline_textChanged();
    void on_sceneAction_textChanged();

private:

    void findCharacters(const QTextEdit *editor);
    void detectLabelStart(QTextEdit *editor);

    Ui::SceneFrame *ui;

    Scene *mSelectedScene = 0;
    QList<ModelCheckbox *> mCharacters;
    SceneItemModel *mModel;
    QCompleter *mCompleter;

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
};

#endif // SCENEFRAME_H
