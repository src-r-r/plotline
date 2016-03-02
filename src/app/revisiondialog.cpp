#include "revisiondialog.h"
#include "ui_revisiondialog.h"

RevisionDialog::RevisionDialog(MainWindow *mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RevisionDialog)
{
    ui->setupUi(this);
    mMainWindow = mainWindow;

    Novel *novel = mainWindow->novel();
    int count = novel->revisionCount(),
            rev = novel->currentRevision();
    mTmpRevisions = novel->revisions();

    ui->revisionNumber->setRange(1, count);
    ui->revisionNumber->setValue(rev+1);
    ui->revisionComments->setPlainText(novel->revisionComment(rev));

    mTempRevision = rev;
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
//    Novel *novel = mainWindow()->novel();
    mTmpRevisions.append(QString());
    ui->revisionNumber->setMaximum(mTmpRevisions.count());
    ui->revisionNumber->setValue(mTmpRevisions.count());
}

void RevisionDialog::on_revisionNumber_valueChanged(int arg1)
{
    qDebug() << "revision value changed:" << arg1;
    mTempRevision = arg1 - 1;
    ui->revisionComments->setPlainText(mTmpRevisions[mTempRevision]);
}

void RevisionDialog::on_buttonBox_accepted()
{
    qDebug() << "Revisions changed:" << "\n"
             << "New revisions:" << mTmpRevisions << "\n"
             << "Selected revision:" << mTempRevision;
    if (mTempRevision != mainWindow()->novel()->currentRevision() ||
            mTmpRevisions != mainWindow()->novel()->revisions())
        emit mainWindow()->novelChanged();
    mainWindow()->novel()->setRevisions(mTmpRevisions);
    mainWindow()->novel()->setCurrentRevision(mTempRevision);
}

void RevisionDialog::on_revisionComments_textChanged()
{
    qDebug() << "revisions[" << mTempRevision << "] ="
             << ui->revisionComments->toPlainText();
    mTmpRevisions[mTempRevision] = ui->revisionComments->toPlainText();
}
