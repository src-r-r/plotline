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
        OPEN_LAST_PROJECT,
        DISTRACTION_FREE_MODE,
        WIDGETS_TIMEOUT,
        SPELL_CHECK,
        MARKUP,
        FONT,
        COLOR_SCHEME;

    enum DistractionFreeMode {
        DfmDisabled = 0,
        ShowWindowed,
        ShowFullScreen
    };

    enum SpellCheckMode {
        SpellCheckDisabled = 0,
        SpellCheckNotInDfm,
        SpellCheckAlways,
    };

    enum MarkupSyntax {
        NoMarkup = 0,
        Markdown,
        RestructuredText
    };

private slots:
    void on_chooseDefaultProjectDirectory_clicked();
    void on_preferencesButtonBox_accepted();
//    void on_preferencesButtonBox_rejected();

    void on_widgetTimeout_sliderMoved(int position);

private:
    Ui::PreferencesDialog *ui;
    static const QStringList WIDGET_TIMEOUTS;
    static const int TIMEOUT_VALUES[6];
};

#endif // PREFERENCESDIALOG_H
