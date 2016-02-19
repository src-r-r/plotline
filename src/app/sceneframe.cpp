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
    blockEditableSignals();
    delete mModel;
    mModel = new SceneItemModel(mainWindow()->novel());
    ui->sceneList->setModel(mModel);
    mActionHighlighter->setNovel(mainWindow()->novel());
    mHeadlineHighlighter->setNovel(mainWindow()->novel());
    connectSlots();
    unblockEditableSignals();
}

void SceneFrame::onNovelNew()
{

}

void SceneFrame::on_detectCharacters_clicked()
{

}

void SceneFrame::on_sceneList_activated(const QModelIndex &index)
{
    QString headline = mModel->data(index, SceneItemModel::HeadlineRole).toString(),
            action = mModel->data(index, SceneItemModel::ActionRole).toString();
    int plotline = mModel->data(index, SceneItemModel::PlotlineRole).toInt();

    QList<Character *> characters = getSelectedCharacters();
    QList<Character *> pointsOfView = getSelectedPointsOfView();

    ModelCheckbox *checkbox;
    clearLayout(ui->characterList, true);
    mCharacters.clear();
    for (Character *c : mainWindow()->novel()->characters()){
        checkbox = new ModelCheckbox(c->name(), QVariant(c->id()));
        mCharacters.append(checkbox);
        ui->characterList->addWidget(checkbox);
        connect(checkbox, SIGNAL(toggled(bool,QVariant)),
                this, SLOT(onCharacterToggled(bool,QVariant)));
    }

    fillPlotlineCombo();

    blockEditableSignals();
    ui->sceneDetails->setEnabled(true);
    ui->sceneHeadline->setText(headline);
    ui->sceneAction->setText(action);
    unblockEditableSignals();
}

void SceneFrame::on_addScene_clicked()
{
    mModel->insertRows(ui->sceneList->currentIndex().row(), 1);
    emit novelModified();
    emit on_sceneList_activated(mModel->index(mModel->rowCount(), 0));
}

void SceneFrame::on_archiveScene_clicked()
{

}

void SceneFrame::on_deleteScene_clicked()
{

}

void SceneFrame::onCharacterToggled(bool checked, QVariant value)
{
    Character *selected = mainWindow()->novel()->character(value.toInt());
    QList<Character *> characters = getSelectedCharacters();
    int i = characters.indexOf(selected);
    if (checked && i < 0){
        characters << selected;
    } else if (!checked && i >= 0){
        characters.removeAt(i);
    }
    setSelectedCharacters(characters);
    emit novelModified();
}

void SceneFrame::on_sceneList_clicked(const QModelIndex &index)
{
    on_sceneList_activated(index);
}

void SceneFrame::on_plotline_activated(int index)
{
    QModelIndex sceneIndex = ui->sceneList->currentIndex();
    int id = ui->plotline->itemData(index).toInt();
    mModel->setData(sceneIndex, QVariant(id), SceneItemModel::PlotlineRole);
    emit novelModified();
}


void SceneFrame::onHeadlineModified()
{
    QModelIndex index = ui->sceneList->currentIndex();
    QString headline = ui->sceneHeadline->toPlainText();
    mModel->setData(index, headline, SceneItemModel::HeadlineRole);

    findCharacters(ui->sceneHeadline);

    emit novelModified();
}

void SceneFrame::onActionModified()
{
    QModelIndex index = ui->sceneList->currentIndex();
    QString action = ui->sceneAction->toPlainText();
    mModel->setData(index, action, SceneItemModel::ActionRole);
    findCharacters(ui->sceneAction);

    emit novelModified();
}

void SceneFrame::disconnectSlots()
{
    disconnect(ui->sceneAction->document(), SIGNAL(contentsChanged()));
    disconnect(ui->sceneHeadline->document(), SIGNAL(contentsChanged()));
}

void SceneFrame::connectSlots()
{
    connect(ui->sceneAction->document(), SIGNAL(contentsChanged()),
            this, SLOT(onActionModified()));
    connect(ui->sceneHeadline->document(), SIGNAL(contentsChanged()),
            this, SLOT(onHeadlineModified()));
}

void SceneFrame::blockEditableSignals()
{
    ui->sceneAction->blockSignals(true);
    ui->sceneHeadline->blockSignals(true);
}

void SceneFrame::unblockEditableSignals()
{
    ui->sceneAction->blockSignals(false);
    ui->sceneHeadline->blockSignals(false);
}

QList<Character *> SceneFrame::_getSelectedCharacters(bool pov)
{
    QModelIndex index = ui->sceneList->currentIndex();
    int role = pov ? SceneItemModel::PointsOfViewRole
                   : SceneItemModel::CharactersRole;
    QJsonArray charIds = mModel->data(index, role).toJsonArray();
    QList<Character *> characters;
    for (QJsonValue v : charIds)
        characters << mainWindow()->novel()->character(v.toInt());
    return characters;
}

void SceneFrame::_setSelectedCharacters(QList<Character *> characters, bool pov)
{
    QModelIndex index = ui->sceneList->currentIndex();
    int role = pov ? SceneItemModel::PointsOfViewRole
                   : SceneItemModel::CharactersRole;
    QJsonArray a;
    for (Character *c : characters)
        a.append(QJsonValue(c->id()));
    mModel->setData(index, a, role);
}

QList<Character *> SceneFrame::getSelectedCharacters()
{
    return _getSelectedCharacters();
}

void SceneFrame::setSelectedCharacters(QList<Character *> characters)
{
    _setSelectedCharacters(characters);
}

QList<Character *> SceneFrame::getSelectedPointsOfView()
{
    return _getSelectedCharacters(true);
}

void SceneFrame::setSelectedPointsOfView(QList<Character *> characters)
{
    _setSelectedCharacters(characters, true);
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

void SceneFrame::fillPlotlineCombo(Plotline *selected)
{
    while (ui->plotline->count() != 0) ui->plotline->removeItem(0);
    for (Plotline *p : mainWindow()->novel()->plotlines()){
        ui->plotline->addItem(p->brief(), QVariant(p->id()));
        if (selected != 0 && p == selected)
            ui->plotline->setCurrentIndex(ui->plotline->count()-1);
    }
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

