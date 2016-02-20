#include "fullscreeneditor.h"
#include "ui_fullscreeneditor.h"

FullScreenEditor::FullScreenEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FullScreenEditor)
{
    ui->setupUi(this);
}

FullScreenEditor::FullScreenEditor(QTextEdit *editor, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FullScreenEditor)
{
    ui->setupUi(this);

    mEditor = editor;

    // Set the editor width.
    QSettings setting;

    float factor = setting.value(PreferencesDialog::DFM_EDITOR_SIZE,
                                 QVariant(0.5)).toFloat();

    int w = QApplication::screens()[0]->size().width(),
            h = QApplication::screens()[0]->size().height();

    int w2 = w * factor,
            h2 = h * factor;

    qDebug() << "resizing editor (" << w << "," << h << ")"
             << "*" << factor << "=" << "("
             << w2 << ","
             << h2 << ")";

    ui->chapterContent->setMaximumHeight(h2);
    ui->chapterContent->setMaximumWidth(w2);
    ui->chapterContent->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                                                  QSizePolicy::Expanding));

    // Set the theme and syntax highlighter.
    MarkupHighlighter::MarkupLanguage muLang =
            (MarkupHighlighter::MarkupLanguage) setting.value(
                PreferencesDialog::MARKUP,
                  QVariant((int) MarkupHighlighter::MarkDown))
            .toInt();
    mHighlighter = new MarkupHighlighter(muLang,
                                         ui->chapterContent->document());
    QString fontName = setting.value(PreferencesDialog::FONT).toString();
    QVariant size = setting.value(PreferencesDialog::FONT_SIZE,
                              QVariant(PreferencesDialog::DEFAULT_FONT_SIZE));
    QFont font = QFont(fontName);
    font.setPointSize(size.toInt());
    ui->chapterContent->setFont(font);

    ui->chapterContent->setPlainText(mEditor->toPlainText());

    // Connect the "escape" key.
    QAction *escape = new QAction(this);
    escape->setShortcut(QKeySequence(Qt::Key_Escape));
    connect(escape, SIGNAL(triggered(bool)),
            this, SLOT(onEscapeTriggered(bool)));
    this->addAction(escape);

    // We'll mimic the static word wrap with dynamic word wrap for the time
    // being. This is because setting the rewrapped content will result in
    // either an infinite loop, the content not being set, or the cursor
    // resetting to the beginning (for cursorPositionChanged signal). TODO:
    // resolve this issue.
    QSettings settings;
    qreal width = settings.value(PreferencesDialog::WORD_WRAP_WIDTH,
                                 QVariant(80)).toReal();
    if (width > 0){
        ui->chapterContent->setLineWrapMode(QTextEdit::FixedColumnWidth);
        ui->chapterContent->setLineWrapColumnOrWidth(width);
    }
}

FullScreenEditor::~FullScreenEditor()
{
    delete ui;
}

bool FullScreenEditor::isFullScreen()
{
    return true;
}

void FullScreenEditor::on_chapterContent_textChanged()
{
    QString content = ui->chapterContent->toPlainText();
    mEditor->setPlainText(content);
}

void FullScreenEditor::onEscapeTriggered(bool triggered)
{
    emit close();
}

void FullScreenEditor::on_chapterContent_cursorPositionChanged()
{
}
