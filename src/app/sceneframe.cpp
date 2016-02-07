#include "sceneframe.h"
#include "ui_sceneframe.h"

SceneFrame::SceneFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::SceneFrame)
{
    ui->setupUi(this);
    mModel = new SceneItemModel(mainWindow->novel());
    ui->sceneList->setModel(mModel);

    Novel *novel = mMainWindow->novel();

    mActionHighlighter =
            new CharacterHighlighter(novel, ui->sceneAction->document());
    mHeadlineHighlighter =
            new CharacterHighlighter(novel, ui->sceneHeadline->document());
}

SceneFrame::~SceneFrame()
{
    delete ui;
}

void SceneFrame::onNovelLoad()
{
    delete mModel;
    mModel = new SceneItemModel(mainWindow()->novel());
    ui->sceneList->setModel(mModel);
    mActionHighlighter->setNovel(mainWindow()->novel());
    mHeadlineHighlighter->setNovel(mainWindow()->novel());
}

void SceneFrame::onNovelNew()
{

}

void SceneFrame::on_detectCharacters_clicked()
{

}

void SceneFrame::on_sceneList_activated(const QModelIndex &index)
{
    mSelectedScene = mainWindow()->novel()->scenes()[index.row()];
    ui->sceneDetails->setEnabled(true);

    ui->sceneHeadline->setText(mSelectedScene->headline());
    ui->sceneAction->setText(mSelectedScene->action());

    // Fill in the plotline list.

    while (ui->plotline->count() != 0)
        ui->plotline->removeItem(0);

    ui->plotline->addItem("", QVariant(-1));
    for (Plotline *p : mainWindow()->novel()->plotlines()){
        ui->plotline->addItem(p->brief(), QVariant(p->id()));
        if (mSelectedScene->plotline() == p)
            ui->plotline->setCurrentIndex(ui->plotline->count()-1);
    }

    // Fill the character list on-demand.
    // First remove any existing characters in the list.
    clearLayout(ui->characterList);

    for (Character *c : mainWindow()->novel()->characters()){
        ModelCheckbox *cb = new ModelCheckbox(c->name(), QVariant(c->id()));
        mCharacters.append(cb);
        if (mSelectedScene->getCharacters().indexOf(c) >= 0)
            cb->setChecked(true);
        connect(cb, SIGNAL(toggled(bool,QVariant)),
                this, SLOT(onCharacterToggled(bool,QVariant)));
        ui->characterList->addWidget(cb);
    }
}

void SceneFrame::on_addScene_clicked()
{
    Scene *scene = new Scene("New Scene", "");

    int r = mModel->rowCount();
    if (!mModel->insertRows(r, 1)){
        qWarning() << "Could not insert rows after row" << r;
        return;
    }
    QModelIndex index = mModel->index(r, 0);
    mModel->setData(index, scene->action());

    mainWindow()->novel()->addScene(scene);
    emit novelModified();
}

void SceneFrame::on_archiveScene_clicked()
{

}

void SceneFrame::on_deleteScene_clicked()
{

}

void SceneFrame::onCharacterToggled(bool checked, QVariant value)
{
    if (checked)
        mSelectedScene->addCharacter(value.toInt());
    else
        mSelectedScene->removeCharacter(value.toInt());
    emit novelModified();
}

void SceneFrame::on_sceneList_clicked(const QModelIndex &index)
{
    on_sceneList_activated(index);
}

void SceneFrame::on_plotline_activated(int index)
{
    int id = ui->plotline->itemData(index).toInt();
    if (id == 0)
        mSelectedScene->setPlotline(0);
    else {
        Plotline *plotline = mainWindow()->novel()->plotline(id);
        mSelectedScene->setPlotline(plotline);
    }
    emit novelModified();
}

void SceneFrame::on_sceneHeadline_textChanged()
{
    if (!mSelectedScene) return;
    mSelectedScene->setHeadline(ui->sceneHeadline->toPlainText());
    mModel->setData(ui->sceneList->currentIndex(), mSelectedScene->headline());

    HeadlineUpdater *update = new HeadlineUpdater(ui->sceneHeadline,
                                                  ui->sceneList);
    detectLabelStart(ui->sceneHeadline);
    findCharacters(ui->sceneHeadline);

    QThreadPool::globalInstance()->start(update);
    emit novelModified();
}

void SceneFrame::on_sceneAction_textChanged()
{
    if (!mSelectedScene) return;
    mSelectedScene->setAction(ui->sceneAction->toPlainText());
    HeadlineUpdater *update = new HeadlineUpdater(ui->sceneHeadline,
                                                  ui->sceneList);
    detectLabelStart(ui->sceneHeadline);
    findCharacters(ui->sceneAction);
    QThreadPool::globalInstance()->start(update);
    emit novelModified();
}

void SceneFrame::findCharacters(const QTextEdit *editor)
{

    QString text = editor->toPlainText();
    ParsedCharacterSet set = ParsedCharacterSet::parse(mainWindow()->novel(),
                                                       text);
    qDebug() << set.count() << "characters found in" << editor->objectName();
    for (ModelCheckbox *cb : mCharacters){
        for (int key : set.keys())
            if (cb->value().toInt() == set.value(key)->id())
                cb->setChecked(true);
    }
}

/**
 * @brief SceneFrame::detectLabelStart
 * Detects when a user begins typing in a character tag (starting with "@").
 * Get the current position of the text cursor and create a context menu with
 * the list of characters.
 * @param editor
 */
void SceneFrame::detectLabelStart(QTextEdit *editor)
{
    QString text = editor->toPlainText();
    QTextCursor cursor = editor->textCursor();
    QRect cursorRect = editor->cursorRect(cursor);
    int cursorPos = cursor.position();
    int start = findCharReverse("@", text, cursorPos-1, " \t");
    QMenu *menu;
    QList<QAction *> actions;

    if (start < 0)
        return;

    // Look back in the position to find a "@". If we reach a whitespace
    // character before an "@" just return.

    // Copy the substring
    QString label = QString();
    for (int j = start; j < cursorPos; ++j)
        label.append(text[j]);

    qDebug() << "Search for" << label;

    QPoint point = cursorRect.bottomRight();

    QStringList completions = QStringList();

    mCompleter = new QCompleter(completions);

    for (Character *c : mainWindow()->novel()->characters(label)){
        QString text = QString("[") + c->label() + QString("] ") + c->name();
        completions.append(text);
    }

    mCompleter->complete(cursorRect);
}

QCompleter *SceneFrame::completer() const
{
    return mCompleter;
}

void SceneFrame::setCompleter(QCompleter *completer)
{
    mCompleter = completer;
}

SceneFrame::HeadlineUpdater::HeadlineUpdater(QTextEdit *field, QListView *listView)
{
    mField = field;
    mListView = listView;
}

void SceneFrame::HeadlineUpdater::run()
{
    SceneItemModel *model = (SceneItemModel *) mListView->model();
    model->setData(mListView->currentIndex(), mField->toPlainText());
}
