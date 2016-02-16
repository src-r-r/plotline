#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

const QString PreferencesDialog::DEFAULT_PROJECT_DIRECTORY = QString("defaultProjectDirectory"),
    PreferencesDialog::DEFAULT_HEADSHOT_DIRECTORY = QString("defaultHeadshotDirectory"),
    PreferencesDialog::OPEN_LAST_PROJECT = QString("openLastProject"),
    PreferencesDialog::DISTRACTION_FREE_MODE = "distractionFreeMode",
    PreferencesDialog::WIDGETS_TIMEOUT = "editorWidgetsTimeout",
    PreferencesDialog::SPELL_CHECK = "editorSpellCheck",
    PreferencesDialog::MARKUP = "editorMarkup",
    PreferencesDialog::FONT = "editorFont",
    PreferencesDialog::FONT_SIZE = "fontSize",
    PreferencesDialog::COLOR_SCHEME = "editorColorScheme";

const QStringList PreferencesDialog::WIDGET_TIMEOUTS({"Immediately",
                                                      "500 milliseconds",
                                                      "1 second",
                                                      "5 seconds",
                                                      "30 seconds",
                                                      "Never",
                                                     });

const int PreferencesDialog::TIMEOUT_VALUES[6] = {0, 500, 1000, 5000, 30000, -1};

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
    ui->openLastProject->setChecked(settings.value(OPEN_LAST_PROJECT, false)
                                    .toBool());
    ui->distractionFreeMode->setCurrentIndex(
                settings.value(
                    DISTRACTION_FREE_MODE,
                    QVariant((int) ShowWindowed))
                .toInt());
    ui->widgetTimeout->setValue(settings.value(WIDGETS_TIMEOUT, QVariant(0))
                                .toInt());
    ui->widgetTimeoutValue->setText(WIDGET_TIMEOUTS[ui->widgetTimeout->value()]);
    ui->editorSpellCheck->setCurrentIndex(
                settings.value(SPELL_CHECK, QVariant((int) SpellCheckDisabled))
                .toInt());
    ui->editorSyntax->setCurrentIndex(
                settings.value(MARKUP, QVariant((int) Markdown)).toInt());
    ui->editorFontSize->setValue(settings.value(FONT_SIZE,
                                          QVariant(DEFAULT_FONT_SIZE))
                           .toInt());

    QString font = settings.value(FONT).toString();
    if (!font.isEmpty())
        ui->editorFont->setCurrentFont(QFont(font));
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
    settings.setValue(DISTRACTION_FREE_MODE,
                      ui->distractionFreeMode->currentIndex());
    settings.setValue(WIDGETS_TIMEOUT, ui->widgetTimeout->value());
    settings.setValue(SPELL_CHECK, ui->editorSpellCheck->currentIndex());
    settings.setValue(MARKUP, ui->editorSyntax->currentIndex());
    settings.setValue(COLOR_SCHEME, ui->editorColorScheme->currentIndex());
    settings.setValue(FONT, ui->editorFont->currentFont().toString());
    settings.setValue(FONT_SIZE, ui->editorFontSize->value());
}

void PreferencesDialog::on_widgetTimeout_sliderMoved(int position)
{
    ui->widgetTimeoutValue->setText(WIDGET_TIMEOUTS[position]);
}
