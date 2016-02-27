#include "scenelistdialog.h"
#include "ui_scenelistdialog.h"

SceneListDialog::SceneListDialog(Novel *novel, QTableView *chapterTable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneListDialog)
{
    ui->setupUi(this);

    mNovel = novel;
    mChapterTable = chapterTable;

    // Get the scenes that are selected for the selected chapter.
    QList<Scene *> selected;
    ChapterModel *model = (ChapterModel *) chapterTable->model();
    QModelIndex index = chapterTable->currentIndex();
    QJsonArray data = model->data(index, ChapterModel::SceneRole).toJsonArray();
    for (QJsonValue v : data)
        selected << mNovel->scene(v.toVariant().toUuid());

    // Now go through all the scenes and add a ModelCheckbox. If the scene
    // is a selected scene, mark it as checked.
    QList<Scene *> all = novel->scenes();
    ModelCheckbox *cb;
    clearLayout(ui->sceneList, true);
    for (Scene *scene : all){
        cb = new ModelCheckbox(scene->headline(), QVariant(scene->id()));
        cb->setChecked(selected.contains(scene));
        mSceneCheckboxes << cb;
        ui->sceneList->addWidget(cb);
    }
}

void SceneListDialog::accept(){
    QAbstractItemModel *model = mChapterTable->model();
    QModelIndex index = mChapterTable->currentIndex();
    QJsonArray value;
    for (ModelCheckbox *cb : mSceneCheckboxes)
        if (cb->isChecked())
            value << QJsonValue(cb->value().toInt());
    model->setData(index, value, ChapterModel::SceneRole);
    this->close();
}

SceneListDialog::~SceneListDialog()
{
    delete ui;
}
