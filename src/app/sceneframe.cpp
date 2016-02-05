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
    CharacterParser *parser = new CharacterParser(mainWindow()->novel(),
                                                  ui->sceneHeadline,
                                                  mCharacters);

    QThreadPool::globalInstance()->start(update);
    QThreadPool::globalInstance()->start(parser);
    emit novelModified();
}

void SceneFrame::on_sceneAction_textChanged()
{
    if (!mSelectedScene) return;
    mSelectedScene->setAction(ui->sceneAction->toPlainText());
    HeadlineUpdater *update = new HeadlineUpdater(ui->sceneHeadline,
                                                  ui->sceneList);
    QThreadPool::globalInstance()->start(update);
    CharacterParser *parser = new CharacterParser(mainWindow()->novel(),
                                                  ui->sceneAction,
                                                  mCharacters);
    QThreadPool::globalInstance()->start(parser);
    emit novelModified();
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

SceneFrame::CharacterParser::CharacterParser(Novel *novel, QTextEdit *field,
                                             QList<ModelCheckbox *> checkboxes)
{
    mNovel = novel;
    mField = field;
    mCheckboxes = checkboxes;
}

void SceneFrame::CharacterParser::run()
{
    QString text = mField->toPlainText();
    ParsedCharacterSet set = ParsedCharacterSet::parse(mNovel, text);
    qDebug() << set.count() << "characters found in" << mField->objectName();
    for (ModelCheckbox *cb : mCheckboxes){
        for (int key : set.keys())
            if (cb->value().toInt() == set.value(key)->id())
                cb->setChecked(true);
    }
}

void SceneFrame::on_sceneHeadline_cursorPositionChanged()
{
    on_sceneHeadline_textChanged();
}

void SceneFrame::on_sceneAction_cursorPositionChanged()
{
    on_sceneAction_textChanged();
}
