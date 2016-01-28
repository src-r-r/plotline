#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QItemSelectionModel>

#include "novel.h"
#include "characteritemmodel.h"
#include "plotlineitemmodel.h"
#include "plotlineitemdelegate.h"
#include "preferencesdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static const int TENSE_PAST = 0,
        TENSE_PRESENT = 1,
        TENSE_FUTURE = 2,
        TENSE_OTHER = 3,

        POV_1_1 = 0,
        POV_2_1 = 1,
        POV_3_1 = 2,
        POV_1_P = 3,
        POV_2_P = 4,
        POV_3_P = 5,
        POV_OTHER = 6;

signals:
    void saveNovel();
    void novelChanged();
    void novelLoaded();
    void characterListChanged();
    void characterSelectionChanged(const QModelIndex &index);
    void currentCharacterChanged();

private slots:

    void on_addCharacter_clicked();
    void on_workingTitleLineEdit_textEdited(const QString &arg1);
    void on_genreLineEdit_textChanged(const QString &arg1);
    void on_settingLineEdit_textChanged(const QString &arg1);
    void on_tenseCombobox_currentIndexChanged(int index);
    void on_pointOfViewComboBox_currentIndexChanged(int index);
    void on_deleteCharacter_clicked();
    void on_characterList_clicked(const QModelIndex &index);
    void on_characterName_textChanged(const QString &arg1);

    /**
     * custom slots
     */
    void onCharacterListChanged();
    void onNovelLoaded();
    void updateNovel();
    void onSaveNovel();
    void onCharacterSelectionChanged(const QModelIndex &index);
    void onCurrentCharacterChanged();

    void on_characterNickname_textChanged(const QString &arg1);
    void on_characterLabel_textChanged(const QString &arg1);
    void on_chooseHeadshot_clicked();
    void on_actionPreferences_triggered();
    void on_actionNovelNew_triggered();
    void on_actionNovelOpen_triggered();
    void on_actionNovelSave_triggered();
    void on_actionNovelRevisions_triggered();
    void on_actionNovelExport_triggered();
    void on_actionNovelBind_triggered();
    void on_actionNovelSaveAs_triggered();
    void on_actionNovelClose_triggered();
    void on_MainWindow_destroyed();

    void on_addPlotline_clicked();

private:

    // Window & Dialogs
    Ui::MainWindow *ui;
    PreferencesDialog *mPrefDialog;

    Novel *mNovel;
    bool mIsSaved;
    QString mOpenedFile;

    // Currently-selected items
    Character *mSelectedCharacter;
    Plotline *mSelectedPlotline;

    // Models
    CharacterItemModel *mCharacterItemModel;
    PlotlineItemModel *mPlotlineItemModel;

    // Delegates
    PlotlineItemDelegate *mPlotlineItemDelegate;

    // functions
    void setCurrentCharacterHeadshot();
};

#endif // MAINWINDOW_H
