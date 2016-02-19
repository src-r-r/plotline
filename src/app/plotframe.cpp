#include "plotframe.h"
#include "ui_plotframe.h"

PlotFrame::PlotFrame(MainWindow *mainWindow, QWidget *parent) :
    PlotlineAppFrame(mainWindow, parent),
    ui(new Ui::PlotFrame)
{
    ui->setupUi(this);

    // Models
    mModel = new PlotlineItemModel(mMainWindow->novel());
    ui->plotlineTable->setModel(mModel);

    // Signals
    connect(ui->plotlineTable, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(onPlotlineDoubleClicked(QModelIndex)));
    connect(this, SIGNAL(plotlineListModified()),
            this, SLOT(onPlotlineListModified()));

    // Properties for table headers.
    ui->plotlineTable->setColumnWidth(PlotlineItemModel::BRIEF,
                                      PlotlineItemModel::BRIEF_WIDTH);
    ui->plotlineTable->setColumnWidth(PlotlineItemModel::SYNOPSIS,
                                      PlotlineItemModel::SYNOPSIS_WIDTH);
    ui->plotlineTable->horizontalHeader()->setStretchLastSection(true);
}

PlotFrame::~PlotFrame()
{
    delete ui;
}

void PlotFrame::onNovelLoad()
{
    mModel = new PlotlineItemModel(mainWindow()->novel());
    ui->plotlineTable->setModel(mModel);
}

void PlotFrame::onNovelNew()
{
    mModel = new PlotlineItemModel(mainWindow()->novel());
}



void PlotFrame::onPlotlineDoubleClicked(QModelIndex index)
{
    showPlotlineDialog();
}

void PlotFrame::onPlotlineListModified()
{
    mModel->removeRows(0, mModel->rowCount());
//    fillPlotlineList();
}

void PlotFrame::on_addPlotline_clicked()
{
    showPlotlineDialog(true);
}

void PlotFrame::on_editPlotline_clicked()
{
    showPlotlineDialog();
}

void PlotFrame::on_archivePlotline_clicked()
{
}

void PlotFrame::on_deletePlotline_clicked()
{
    QModelIndex current = ui->plotlineTable->currentIndex();
    int id = mModel->data(current, PlotlineItemModel::PlotlineId).toInt();
    mModel->removeRows(current.row(), 1);
    mainWindow()->novel()->removePlotline(id);
}

void PlotFrame::on_searchPlotlines_textChanged(const QString &arg1)
{

}

void PlotFrame::on_filterPlotlines_activated(int index)
{

}

PlotlineItemModel *PlotFrame::model() const
{
    return mModel;
}

void PlotFrame::setModel(PlotlineItemModel *model)
{
    mModel = model;
}

void PlotFrame::on_plotlineTable_activated(const QModelIndex &index)
{
}

void PlotFrame::onPlotlineAdded(const QModelIndex &index)
{
    ui->plotlineTable->setCurrentIndex(index);
}

void PlotFrame::showPlotlineDialog(bool isNew)
{
    QModelIndex index = ui->plotlineTable->currentIndex();
    PlotlineDialog *dialog = new PlotlineDialog(mModel, index, isNew);
    connect(dialog, SIGNAL(plotlineAdded(QModelIndex)),
            this, SLOT(onPlotlineAdded(QModelIndex)));
    dialog->exec();
}
