#include "scenelistdialog.h"
#include "ui_scenelistdialog.h"

SceneListDialog::SceneListDialog(Novel *novel, QTableView *chapterTable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneListDialog)
{
    ui->setupUi(this);

    mNovel = novel;
    mChapterTable = chapterTable;

    // Get the chapter from the table.
    QModelIndex index = chapterTable->currentIndex();
    ChapterModel *model = (ChapterModel *) chapterTable->model();
    QUuid id = model->data(index, ChapterModel::IdRole).toUuid();
    Chapter *chapter = mNovel->chapter(id);
    QList<Plotline *> plotlines = mNovel->plotlines();

    if (!chapter){
        qWarning() << "No chapter selected.";
        return;
    }

    // Fill the plotline selection
    ui->plotlineSelection->addItem("", QVariant(0));
    for (Plotline *p : plotlines)
        ui->plotlineSelection->addItem(p->brief(), p->id());

    // Get the scene lists to compare.
    QList<Scene *> novelScenes = mNovel->scenes();
    QList<Scene *> chapterScenes = chapter->scenes();

    // Add all novel scenes as a model checkbox. If the scene is included
    // as a scene assigned to the chapter, mark it as checked.
    for (Scene *s : novelScenes){
        ModelCheckbox *cb = new ModelCheckbox(s->headline(), s->id());
        cb->setChecked(chapterScenes.contains(s));
        mCheckboxes << cb;
        ui->sceneList->addWidget(cb);
    }

    fillList();
}

void SceneListDialog::accept(){
    QAbstractItemModel *model = mChapterTable->model();
    QModelIndex index = mChapterTable->currentIndex();
    int role = 0;
    for (ModelCheckbox *cb : mCheckboxes){
        QUuid id = cb->value().toUuid();
        if (cb->isChecked())
            role = ChapterModel::AddSceneRole;
        else
            role = ChapterModel::RemoveSceneRole;
        model->setData(index, id, role);
    }
    this->close();
}

SceneListDialog::~SceneListDialog()
{
    delete ui;
}

void SceneListDialog::fillList()
{
    Scene *s = 0;

    for (ModelCheckbox *cb : mCheckboxes){
        s = mNovel->scene(cb->value().toUuid());
        bool contains = s->headline().toLower().contains(mSearch.toLower());
        bool plotlineMatches = (s->plotline() == mPlotline);
        if ((mPlotline == 0 || plotlineMatches) && (mSearch.isNull() || contains))
            cb->setVisible(true);
        else
            cb->setVisible(false);
    }
}

void SceneListDialog::on_plotlineSelection_activated(int index)
{
    if (index == 0){
        mPlotline = 0;
        fillList();
    }
    QUuid id = ui->plotlineSelection->currentData().toUuid();
    mPlotline = mNovel->plotline(id);
    fillList();
}

void SceneListDialog::on_sceneSearch_textChanged(const QString &arg1)
{
    mSearch = arg1;
    fillList();
}
