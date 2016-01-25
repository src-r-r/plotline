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

#include "novel.h"
#include "characteritemmodel.h"

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

private slots:

    void on_addCharacter_clicked();
    void on_workingTitleLineEdit_textEdited(const QString &arg1);

    void on_genreLineEdit_textChanged(const QString &arg1);

    void on_settingLineEdit_textChanged(const QString &arg1);

    void on_actionOpen_Novel_triggered();

    void on_actionSave_triggered();

    /**
     * custom slots
     */
    void onCharacterListChanged();
    void onNovelLoaded();
    void updateNovel();
    void onSaveNovel();

    void on_tenseCombobox_currentIndexChanged(int index);
    void on_pointOfViewComboBox_currentIndexChanged(int index);
    void on_actionNovel_triggered();

private:

    Ui::MainWindow *ui;
    Novel *mNovel;
    bool mIsSaved;
    QString mOpenedFile;
};

#endif // MAINWINDOW_H
