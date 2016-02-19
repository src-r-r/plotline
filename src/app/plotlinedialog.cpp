#include "plotlinedialog.h"
#include "ui_plotlinedialog.h"

PlotlineDialog::PlotlineDialog(PlotlineItemModel *model,
                               const QModelIndex &index,
                               bool isNew,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotlineDialog)
{
    ui->setupUi(this);

    mModel = model;
    mIndex = index;
    mCharacterList = QMap<QCheckBox *, Character *>();
    mIsNew = isNew;
    QList<Character *> selectedCharacters;
    if (index.isValid() && !mIsNew){
        mIsNew = false;
        QString brief = mModel->data(index, PlotlineItemModel::BriefRole)
                                   .toString(),
                synopsis = mModel->data(index, PlotlineItemModel::SynopsisRole)
                                      .toString(),
                color = mModel->data(index, PlotlineItemModel::ColorRole)
                    .toString();
        QJsonArray jCharacters = mModel->data(index,
                                             PlotlineItemModel::CharacterRole)
                .toJsonArray();
        ui->plotlineBrief->setText(brief);
        ui->plotlineSynopsis->setText(synopsis);
        onColorSelected(QColor(color));

        for (QJsonValue v : jCharacters)
            selectedCharacters << mModel->novel()->character(v.toInt());
    } else {
        mIsNew = true;
        setWindowTitle(tr("New Plotline"));
    }

    for (Character *c : mModel->novel()->characters()) {
        QCheckBox *checkbox = new QCheckBox(c->name());
        bool checked = selectedCharacters.contains(c);
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
    if (mIsNew){
        if (!mModel->insertRows(mIndex.row(), 1))
            return;
        qDebug() << "plotline: insert new row at" << mIndex.row();
        if (!mIndex.isValid())
            mIndex = mModel->index(mModel->rowCount()-1, 0);
    }

    QJsonArray charIds;
    for (QCheckBox *cb : mCharacterList.keys())
        if (cb->isChecked())
            charIds << QJsonValue(mCharacterList[cb]->id());

    mModel->setData(mIndex, ui->plotlineBrief->text(), PlotlineItemModel
                    ::BriefRole);
    mModel->setData(mIndex, ui->plotlineSynopsis->toPlainText(),
                    PlotlineItemModel::SynopsisRole);
    mModel->setData(mIndex, charIds, PlotlineItemModel::CharacterRole);
    mModel->setData(mIndex, mColor, PlotlineItemModel::ColorRole);

    if (mIsNew)
        emit plotlineAdded(mIndex);
    else
        emit plotlineModified(mIndex);
}
