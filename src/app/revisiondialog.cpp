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

    ui->revisionNumber->setRange(1, count);
    ui->revisionNumber->setValue(rev);
    mRevision = rev;
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
    Novel *novel = mainWindow()->novel();
    mNewRevisions.append(QString());
    int n = novel->revisionCount() + mNewRevisions.count();
    ui->revisionNumber->setMaximum(n);
    ui->revisionNumber->setValue(n);
}

void RevisionDialog::on_revisionNumber_valueChanged(int arg1)
{
    qDebug() << "revision value changed:" << arg1;
    Novel *novel = mainWindow()->novel();
    mRevision = arg1 - 1;

    QString text = QString();

    int l = novel->revisionCount();

    if (mRevision < novel->revisionCount())
        text = novel->revisionComment(mRevision);
    else
        text = mNewRevisions[mRevision - l];
    ui->revisionComments->setPlainText(text);
}

void RevisionDialog::on_buttonBox_accepted()
{
    for (QString rev : mNewRevisions)
        mainWindow()->novel()->addRevision(rev);
    qDebug() << "Revisions changed:" << "\n"
             << "New revisions:" << mNewRevisions << "\n"
             << "Selected revision:" << mRevision;
    mainWindow()->novel()->setCurrentRevision(mRevision);
    emit mainWindow()->novelChanged();
}
