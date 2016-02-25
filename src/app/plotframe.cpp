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
    ui->plotlineTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->plotlineTable->setSelectionMode(QAbstractItemView::SingleSelection);
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
    QString expl = tr("If you delete, it's lost forever. However, archiving")
            + tr(" will make it retreivable.");
    QMessageBox *messageBox = new QMessageBox(tr("Delete this plotline?"),
                                              expl, QMessageBox::Warning,
                                              QMessageBox::Ok,
                                              QMessageBox::Save,
                                              QMessageBox::Cancel);
    messageBox->setButtonText(QMessageBox::Ok, tr("Delete"));
    messageBox->setButtonText(QMessageBox::Save, tr("Archive"));

    int res = messageBox->exec();
    if (res == QMessageBox::Ok){
        QModelIndex current = ui->plotlineTable->currentIndex();
        mModel->removeRows(current.row(), 1);
    } else if (res == QMessageBox::Save){
        // TODO: archiving.
    }
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
    bool enable = index.isValid();
    ui->deletePlotline->setEnabled(enable);
    ui->archivePlotline->setEnabled(enable);
    ui->editPlotline->setEnabled(enable);
}

void PlotFrame::onPlotlineAdded(const QModelIndex &index)
{
    ui->plotlineTable->setCurrentIndex(index);
}

void PlotFrame::showPlotlineDialog(bool isNew)
{
    QModelIndex index = ui->plotlineTable->currentIndex();
    PlotlineDialog *dialog = new PlotlineDialog(ui->plotlineTable,
                                                mainWindow()->novel(),
                                                isNew);
    connect(dialog, SIGNAL(plotlineAdded(QModelIndex)),
            this, SLOT(onPlotlineAdded(QModelIndex)));
    dialog->exec();
}
