#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

const QString PreferencesDialog::DEFAULT_PROJECT_DIRECTORY = QString("defaultProjectDirectory"),
    PreferencesDialog::DEFAULT_HEADSHOT_DIRECTORY = QString("defaultHeadshotDirectory"),
    PreferencesDialog::OPEN_LAST_PROJECT = QString("openLastProject");

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    // Load from preferences.
    QSettings settings;

    ui->defaultProjectDirectory->setText(settings.value(
                                             DEFAULT_PROJECT_DIRECTORY,
                                             QDir::homePath()).toString());
    ui->openLastProject->setChecked(settings.value(OPEN_LAST_PROJECT).toBool());
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::on_chooseDefaultProjectDirectory_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory();
    if (dirName.isNull())
        return;
    ui->defaultProjectDirectory->setText(dirName);
}

void PreferencesDialog::on_preferencesButtonBox_accepted()
{
    QSettings settings;
    QString defProjectText = ui->defaultProjectDirectory->text();
    if (!defProjectText.isNull())
        settings.setValue(DEFAULT_PROJECT_DIRECTORY, defProjectText);
    settings.setValue(OPEN_LAST_PROJECT,
                      QVariant(ui->openLastProject->isChecked()));
}

void PreferencesDialog::on_preferencesButtonBox_rejected()
{

}
