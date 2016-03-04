#include "sceneframe.h"
#include "ui_sceneframe.h"

SceneFrame::SceneFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::SceneFrame)
{
    ui->setupUi(this);
    SceneModel *model = new SceneModel(mainWindow->novel());
    mFilter = new SceneFilter(mainWindow->novel());
    mFilter->setSourceModel(model);
    ui->sceneList->setModel(mFilter);

    Novel *novel = mMainWindow->novel();

    ui->sceneAction->blockSignals(true);
    ui->sceneAction->document()->blockSignals(true);
    mActionHighlighter =
            new CharacterHighlighter(novel, ui->sceneAction->document());
    mHeadlineHighlighter =
            new CharacterHighlighter(novel, ui->sceneHeadline->document());
    ui->sceneAction->blockSignals(false);
    ui->sceneAction->document()->blockSignals(false);

    // Set up the list view for drag/drop re-ordering.
    ui->sceneList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->sceneList->setDragDropMode(QAbstractItemView::InternalMove);
    ui->sceneList->setDragEnabled(true);
    ui->sceneList->viewport()->setAcceptDrops(true);
    ui->sceneList->setDropIndicatorShown(true);

    ui->sceneDetails->setDisabled(true);

    connect(ui->sceneAction, SIGNAL(textChanged()),
            this, SLOT(onActionModified()));
    connect(ui->sceneHeadline, SIGNAL(textChanged()),
            this, SLOT(onHeadlineModified()));
}

SceneFrame::~SceneFrame()
{
//    delete mActionCompleter;
//    delete mActionHighlighter;
//    delete mHeadlineCompleter;
//    delete mHeadlineHighlighter;
    delete ui;
}

void SceneFrame::onNovelLoad()
{
    blockEditableSignals();
//    delete mFilter;

    // Clear the filter of any plotlines.
    for (int i = 0; i < ui->filterScenes->count(); ++i){
        if (!ui->filterScenes->itemData(i, Qt::UserRole).isNull())
            ui->filterScenes->removeItem(i);
    }
    // Refill them, starting with a blank item.
    ui->filterScenes->addItem("", QVariant());
    for (Plotline *plotline : mainWindow()->novel()->plotlines()){
        ui->filterScenes->addItem(plotline->brief(), plotline->id());
    }
    ui->filterScenes->insertSeparator(ui->filterScenes->count());


    // Set up the QCompleter for the headline and action fields.
    QStringList completions;
    for (Character *c : mainWindow()->novel()->characters())
        completions << c->label();
    mHeadlineCompleter = new QCompleter(completions);
    mActionCompleter = new QCompleter(completions);

    mHeadlineCompleter->setWidget(ui->sceneHeadline);
    mHeadlineCompleter->setCompletionPrefix("@");
    mHeadlineCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    mActionCompleter->setWidget(ui->sceneAction);
    mActionCompleter->setCompletionPrefix("@");
    mActionCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    SceneModel *model = new SceneModel(mainWindow()->novel());
    mFilter = new SceneFilter(mainWindow()->novel());
    mFilter->setSourceModel(model);
    ui->sceneList->setModel(mFilter);
    mActionHighlighter->setNovel(mainWindow()->novel());
    mHeadlineHighlighter->setNovel(mainWindow()->novel());
    mActionHighlighter->rehighlight();
    mHeadlineHighlighter->rehighlight();
}

void SceneFrame::onNovelNew()
{

}

void SceneFrame::on_detectCharacters_clicked()
{

}

void SceneFrame::on_sceneList_activated(const QModelIndex &index)
{
    ui->sceneDetails->setDisabled(true);
    if (!index.isValid()) {
        qDebug() << "scene - none selected";
        return;
    }
    QString headline = mFilter->data(index, SceneModel::HeadlineRole).toString(),
            action = mFilter->data(index, SceneModel::ActionRole).toString();
    QUuid plotline = mFilter->data(index, SceneModel::PlotlineRole).toUuid();

    QList<Character *> selectedCharacters = getSelectedCharacters();
//    QList<Character *> pointsOfView = getSelectedPointsOfView();

    ModelCheckbox *checkbox;
    clearLayout(ui->characterList, true);
    mCharacters.clear();
    for (Character *c : mainWindow()->novel()->characters()){
        checkbox = new ModelCheckbox(c->name(), c->id());
        checkbox->setChecked(false);
        bool checked = selectedCharacters.contains(c);
        checkbox->setChecked(checked);
        qDebug("scene: [%s] %s", checked ? "*" : " ",
               c->name().toStdString().data());
        mCharacters << checkbox;
        ui->characterList->addWidget(checkbox);
        connect(checkbox, SIGNAL(toggled(bool, QVariant)),
                this, SLOT(onCharacterToggled(bool, QVariant)));
    }

    fillPlotlineCombo(mainWindow()->novel()->plotline(plotline));

    ui->sceneDetails->setEnabled(true);

    ui->sceneHeadline->blockSignals(true);
    ui->sceneHeadline->document()->blockSignals(true);
    ui->sceneHeadline->document()->setPlainText(headline);
    mActionHighlighter->rehighlight();
    ui->sceneHeadline->blockSignals(false);
    ui->sceneHeadline->document()->blockSignals(false);

    ui->sceneAction->blockSignals(true);
    ui->sceneAction->document()->blockSignals(true);
    ui->sceneAction->document()->setPlainText(action);
    mHeadlineHighlighter->rehighlight();
    ui->sceneAction->document()->blockSignals(false);
    ui->sceneAction->blockSignals(false);

}

void SceneFrame::on_addScene_clicked()
{
    QModelIndex index = ui->sceneList->currentIndex();
    mFilter->insertRows(index.row()+1, 1);
    index = mFilter->index(index.row()+1, 0);
    // select the recently-added scene
    ui->sceneList->setCurrentIndex(index);
    emit novelModified();
    emit ui->sceneList->activated(index);
}

void SceneFrame::on_archiveScene_clicked()
{

}

void SceneFrame::on_deleteScene_clicked()
{
    QModelIndex index = ui->sceneList->currentIndex();
    QItemSelectionModel *model = ui->sceneList->selectionModel();
    QModelIndexList indexes = model->selectedRows();
    if (indexes.count() == 0)
        return;
    QString headline = mFilter->data(index, SceneModel::HeadlineRole)
            .toString(),
        message = tr("Scene Deletion Confirmation"),
        text = tr("Are you sure you want to delete")
            + tr((indexes.count() > 1) ? "  these " : " this ")
            + ((indexes.count() > 1) ? QString::number(indexes.count())
                                     : QString(""))
            + tr((indexes.count() > 1) ? " scenes?\n" : " scene?\n")
            + ((indexes.count() == 1) ? headline : tr(""))
            + QString("\nArchiving is safer."),

        b0t = tr("Archive"),
        b1t = tr("Cancel"),
        b2t = tr("Delete");
    const int dflt = 0;

    int result = QMessageBox::warning(this, message, text, b0t, b1t, b2t, dflt);
    if (result == 0){
        // archive
    } if (result == 1) {
        // cancel
    } else if (result == 2) {
        mFilter->removeRows(indexes);
        index = mFilter->index(index.row()-1, 0);
        emit ui->sceneList->activated(index);
    }
}

void SceneFrame::onCharacterToggled(bool checked, QVariant value)
{
    Character *selected = mainWindow()->novel()->character(value.toUuid());
    QList<Character *> characters = getSelectedCharacters();
    int i = characters.indexOf(selected);
    if (checked && i < 0){
        qDebug() << "Adding character" << selected->name();
        characters << selected;
    } else if (!checked && i >= 0){
        qDebug() << "Removing character" << characters[i]->name();
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
    QUuid id = ui->plotline->itemData(index).toUuid();
    mFilter->setData(sceneIndex, id, SceneModel::PlotlineRole);
    emit novelModified();
}


void SceneFrame::onHeadlineModified()
{
    QModelIndex index = ui->sceneList->currentIndex();
    if (!index.isValid()) return;
    QString headline = ui->sceneHeadline->toPlainText();
    mFilter->setData(index, headline, SceneModel::HeadlineRole);
    emit mFilter->dataChanged(ui->sceneList->currentIndex(),
                             ui->sceneList->currentIndex());

    findCharacters(ui->sceneHeadline);

    emit novelModified();
}

void SceneFrame::onActionModified()
{
    QModelIndex index = ui->sceneList->currentIndex();
    if (!index.isValid()) return;
    QString action = ui->sceneAction->toPlainText();
    mFilter->setData(index, action, SceneModel::ActionRole);
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
    int role = pov ? SceneModel::PointsOfViewRole
                   : SceneModel::CharactersRole;
    QJsonArray charIds = mFilter->data(index, role).toJsonArray();
    QList<Character *> characters;
    for (QJsonValue v : charIds)
        characters << mainWindow()->novel()->character(QUuid(v.toString()));
    return characters;
}

void SceneFrame::_setSelectedCharacters(QList<Character *> characters, bool pov)
{
    QModelIndex index = ui->sceneList->currentIndex();
    int role = pov ? SceneModel::PointsOfViewRole
                   : SceneModel::CharactersRole;
    QJsonArray a;
    for (Character *c : characters)
        a.append(QJsonValue(c->id().toString()));
    mFilter->setData(index, a, role);
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
            if (cb->value().toUuid() == set.value(key)->id())
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
//    QRect cursorRect = editor->cursorRect(cursor);
    int cursorPos = cursor.position();
    int start = findCharReverse("@", text, cursorPos-1, " \t");

    if (start < 0)
        return;

    // Look back in the position to find a "@". If we reach a whitespace
    // character before an "@" just return.

    // Copy the substring
    QString label;
    for (int j = start; j < cursorPos; ++j)
        label.append(text[j]);

    qDebug() << "Search for" << label;
    if (editor == ui->sceneAction)
        emit mActionCompleter->activated(label);
    else if (editor == ui->sceneHeadline)
        emit mHeadlineCompleter->activated(label);

    ui->sceneList->setDragDropMode(QListView::DragDrop);
    ui->sceneList->setDropIndicatorShown(true);
    ui->sceneList->setDragEnabled(true);
    ui->sceneList->setAcceptDrops(true);
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

SceneFrame::HeadlineUpdater::HeadlineUpdater(QTextEdit *field, QListView *listView)
{
    mField = field;
    mListView = listView;
}

void SceneFrame::HeadlineUpdater::run()
{
    SceneModel *model = (SceneModel *) mListView->model();
    model->setData(mListView->currentIndex(), mField->toPlainText());
}

void SceneFrame::on_sceneList_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->sceneList->indexAt(pos);
    qDebug() << "Show context menu at" << index;
    if (!index.isValid())
        return;

    QMenu *m = new QMenu("Scene");
    m->addAction(tr("Delete"), this, SLOT(on_deleteScene_clicked()));
}

void SceneFrame::on_filterScenes_activated(int index)
{
    Q_UNUSED(index);
    QVariant data = ui->filterScenes->currentData();
    if (data.isNull()){
        mFilter->setPlotline(0);
        return;
    }
    QUuid id = data.toUuid();
    Plotline *plotline = mainWindow()->novel()->plotline(id);
    mFilter->setPlotline(plotline);
}

void SceneFrame::on_searchScenes_textEdited(const QString &arg1)
{
    mFilter->setSearch(arg1);
}

void SceneFrame::on_sceneList_indexesMoved(const QModelIndexList &indexes)
{
    qDebug() << "Finished moving:";
    for (QModelIndex index : indexes){
        qDebug() << "   -" << mFilter->data(index, SceneModel::HeadlineRole).toString();
    }
}

void SceneFrame::on_characterSearch_textChanged(const QString &arg1)
{
    for (ModelCheckbox *cb : mCharacters){
        Character *c = mainWindow()->novel()->character(cb->value().toUuid());
        if (!c) break;
        if (arg1.isEmpty() || (c->name().toLower().contains(arg1.toLower()))
                || (arg1.startsWith("@") && c->label().contains(arg1.mid(1)))){
            ui->characterList->addWidget(cb);
            cb->setVisible(true);
        } else {
            ui->characterList->removeWidget(cb);
            cb->setVisible(false);
        }
    }
}
