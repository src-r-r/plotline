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

    void on_revisionComments_textChanged();

private:
    Ui::RevisionDialog *ui;

    MainWindow *mMainWindow;

    QStringList mTmpRevisions;
    int mTempRevision = 0;
};

#endif // REVISIONDIALOG_H
