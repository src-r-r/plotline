#ifndef REVISIONDIALOG_H
#define REVISIONDIALOG_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class RevisionDialog;
}

class RevisionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RevisionDialog(MainWindow *mainWindow, QWidget *parent = 0);
    ~RevisionDialog();

    MainWindow *mainWindow() const;
    void setMainWindow(MainWindow *mainWindow);

private slots:
    void on_addRevision_clicked();
    void on_revisionNumber_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::RevisionDialog *ui;

    MainWindow *mMainWindow;

    int mNewRevisions = 0;
    int mRevision = 0;
};

#endif // REVISIONDIALOG_H
