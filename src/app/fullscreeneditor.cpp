#include "fullscreeneditor.h"
#include "ui_fullscreeneditor.h"

FullScreenEditor::FullScreenEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FullScreenEditor)
{
    ui->setupUi(this);
}

FullScreenEditor::FullScreenEditor(QTableView *chapterTable, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FullScreenEditor)
{
    ui->setupUi(this);
    mChapterTable = chapterTable;

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


    // Set up the models.
    ChapterModel *model = (ChapterModel *) chapterTable->model();
    QModelIndex index = chapterTable->currentIndex();
    QString content = model->data(index, ChapterModel::ContentRole).toString();

    ui->chapterContent->setPlainText(content);

    connect(ui->chapterContent->document(), SIGNAL(contentsChanged()),
            this, SLOT(onContentsChanged()));
}

FullScreenEditor::~FullScreenEditor()
{
    delete ui;
}

bool FullScreenEditor::isFullScreen()
{
    return true;
}

void FullScreenEditor::onContentsChanged()
{
    QString content = ui->chapterContent->toPlainText();
    ChapterModel *model = (ChapterModel *) mChapterTable->model();
    QModelIndex index = mChapterTable->currentIndex();
    model->setData(index, content, ChapterModel::ContentRole);
}
