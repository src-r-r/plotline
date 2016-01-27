#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QFileDialog>
#include <QAbstractButton>

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();

    static const QString DEFAULT_PROJECT_DIRECTORY,
        DEFAULT_HEADSHOT_DIRECTORY,
        OPEN_LAST_PROJECT;


private slots:
    void on_chooseDefaultProjectDirectory_clicked();
    void on_preferencesButtonBox_accepted();
    void on_preferencesButtonBox_rejected();

private:
    Ui::PreferencesDialog *ui;
};

#endif // PREFERENCESDIALOG_H
