#ifndef SCENELISTDIALOG_H
#define SCENELISTDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QWidget>
#include <QTableView>
#include "modelcheckbox.h"
#include "mainwindow.h"
#include "chaptermodel.h"
#include "utils.h"

namespace Ui {
class SceneListDialog;
}

class SceneListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SceneListDialog(Novel *novel, QTableView *mChapterTable, QWidget *parent = 0);
    void accept();
    ~SceneListDialog();

private slots:

private:
    Ui::SceneListDialog *ui;

    Novel *mNovel;
    QTableView *mChapterTable;
    QList<ModelCheckbox *> mSceneCheckboxes;
};

#endif // SCENELISTDIALOG_H
