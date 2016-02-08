#include "revisiondialog.h"
#include "ui_revisiondialog.h"

RevisionDialog::RevisionDialog(MainWindow *mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RevisionDialog)
{
    ui->setupUi(this);
    mMainWindow = mainWindow;

    ui->revisionNumber->setRange(1, mainWindow->novel()->revisionCount());
    ui->revisionNumber->setValue(mainWindow->novel()->currentRevision()+1);
    mRevision = mainWindow->novel()->currentRevision();
}

RevisionDialog::~RevisionDialog()
{
    delete ui;
}

MainWindow *RevisionDialog::mainWindow() const
{
    return mMainWindow;
}

void RevisionDialog::setMainWindow(MainWindow *mainWindow)
{
    mMainWindow = mainWindow;
}

void RevisionDialog::on_addRevision_clicked()
{
    ++mNewRevisions;
    ui->revisionNumber->setMaximum(mainWindow()->novel()
                                   ->revisionCount() + mNewRevisions);
    ui->revisionNumber->setValue(ui->revisionNumber->maximum());
}

void RevisionDialog::on_revisionNumber_valueChanged(int arg1)
{
    qDebug() << "revision value changed:" << arg1;
    mRevision = arg1 - 1;
}

void RevisionDialog::on_buttonBox_accepted()
{
    for (int i = 0; i < mNewRevisions; ++i)
        mainWindow()->novel()->addRevision();
    if (mNewRevisions > 0)
        mRevision = mainWindow()->novel()->revisionCount()-1;
    qDebug() << "Revisions changed:" << "\n"
             << "New revisions:" << mNewRevisions << "\n"
             << "Selected revision:" << mRevision;
    mainWindow()->novel()->setCurrentRevision(mRevision, true);
    emit mainWindow()->novelChanged();
}
