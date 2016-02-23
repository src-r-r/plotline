#ifndef CHAPTERREORDERDIALOG_H
#define CHAPTERREORDERDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QtWidgets>
#include <QtDebug>
#include "chapter.h"
#include "chaptermodel.h"

namespace Ui {
class ChapterReorderDialog;
}

class ChapterReorderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChapterReorderDialog(QTableView *chapter = 0, QWidget *parent = 0);
    ~ChapterReorderDialog();

private slots:
    void on_ChapterReorderDialog_accepted();

private:
    Ui::ChapterReorderDialog *ui;

    QTableView *mTableView;
};

#endif // CHAPTERREORDERDIALOG_H
