#include "chapterreorderdialog.h"
#include "ui_chapterreorderdialog.h"

ChapterReorderDialog::ChapterReorderDialog(QTableView *tableView,
                                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChapterReorderDialog)
{
    ui->setupUi(this);

    mTableView = tableView;

    ChapterModel *model = (ChapterModel *) tableView->model();
    QModelIndex index, selected = tableView->currentIndex();
    QString label, number, title;

    for (int row = 0; row < model->rowCount(); ++row){
        index = model->index(row, 0);
        if (selected != index){
            number = model->data(index, ChapterModel::NumberRole).toString();
            title = model->data(index, ChapterModel::TitleRole).toString();
            label = QString("Chapter ") + number;

            if (!title.isNull())
                label += QString(": ") + title;
            ui->chapterList->addItem(label, QVariant(row));
        }
    }
}

ChapterReorderDialog::~ChapterReorderDialog()
{
    delete ui;
}

void ChapterReorderDialog::on_ChapterReorderDialog_accepted()
{
    ChapterModel *model = (ChapterModel *) mTableView->model();
    QModelIndex selected = mTableView->currentIndex();

    model->moveRows(QModelIndex(), selected.row(), 1,
                    QModelIndex(),
                    ui->chapterList->currentData().toInt());
}
