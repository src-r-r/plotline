#include "plotlinedialog.h"
#include "ui_plotlinedialog.h"

PlotlineDialog::PlotlineDialog(PlotFrame *plotFrame, const QModelIndex &index,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotlineDialog)
{
    ui->setupUi(this);
    mPlotFrame = plotFrame;
    mIndex = index;
    mCharacterList = QMap<QCheckBox *, Character *>();
    if (index.isValid()){
        mIsNew = false;
        mPlotline = mPlotFrame->mainWindow()->novel()->plotlines()[index.row()];
        setWindowTitle(mPlotline->brief());
        ui->plotlineBrief->setText(mPlotline->brief());
        ui->plotlineSynopsis->setText(mPlotline->synopsis());
        onColorSelected(mPlotline->getColor());
    } else {
        mIsNew = true;

        mPlotline = new Plotline("", "");
        mPlotline->setNovel(plotFrame->mainWindow()->novel());
        setWindowTitle(tr("New Plotline"));
    }

    for (Character *c : mPlotline->novel()->characters()) {
        QCheckBox *checkbox = new QCheckBox(c->name());
        bool checked = (mPlotline->characters().indexOf(c) >= 0);
        checkbox->setChecked(checked);
        mCharacterList.insert(checkbox, c);
        ui->characterListLayout->addWidget(checkbox);
    }
}

PlotlineDialog::~PlotlineDialog()
{
    delete ui;
    // The plotline will be deleted with the novel.
}

void PlotlineDialog::on_plotlineColor_clicked()
{
    QColorDialog *dialog = new QColorDialog(this);
    connect(dialog, SIGNAL(colorSelected(QColor)),
            this, SLOT(onColorSelected(QColor)));
    dialog->exec();
}

void PlotlineDialog::onColorSelected(const QColor &color)
{
    mColor = color;
    QImage image = QImage(40, 30, QImage::Format_RGB32);
    image.fill(color);
    QIcon icon = QIcon(QPixmap::fromImage(image));
    ui->plotlineColor->setIcon(icon);
}


void PlotlineDialog::on_clearPlotlineColor_clicked()
{
    onColorSelected(QColor());
}

void PlotlineDialog::on_buttonBox_accepted()
{
    mPlotline->setBrief(ui->plotlineBrief->text());
    mPlotline->setSynopsis(ui->plotlineSynopsis->toPlainText());
    mPlotline->setColor(mColor);
    QList<Character *> characters = QList<Character *>();
    for (QCheckBox *cb : mCharacterList.keys())
        if (cb->isChecked())
            characters << mCharacterList.value(cb);
    mPlotline->setCharacters(characters);

    qDebug() << "Modified plotline: " << mPlotline->serialize();

    PlotlineItemModel *m = 0;
    m = mPlotFrame->model();
    if (mIsNew)
        mPlotFrame->mainWindow()->novel()->addPlotline(mPlotline);

    emit mPlotFrame->novelModified();
}
