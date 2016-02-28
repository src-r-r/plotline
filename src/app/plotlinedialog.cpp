#include "plotlinedialog.h"
#include "ui_plotlinedialog.h"

PlotlineDialog::PlotlineDialog(QTableView *tableView,
                               Novel *novel,
                               bool isNew,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotlineDialog)
{
    ui->setupUi(this);

    mTableView = tableView;
    mNovel = novel;

    mCharacterList = QMap<QCheckBox *, Character *>();
    mIsNew = isNew;

    PlotlineItemModel *model = (PlotlineItemModel *) mTableView->model();
    QModelIndex index = mTableView->currentIndex();

    QList<Character *> selectedCharacters;
    if (index.isValid() && !mIsNew){
        mIsNew = false;
        QString brief = model->data(index, PlotlineItemModel::BriefRole)
                                   .toString(),
                synopsis = model->data(index, PlotlineItemModel::SynopsisRole)
                                      .toString(),
                color = model->data(index, PlotlineItemModel::ColorRole)
                    .toString();
        QJsonArray jCharacters = model->data(index,
                                             PlotlineItemModel::CharacterRole)
                .toJsonArray();
        ui->plotlineBrief->setText(brief);
        ui->plotlineSynopsis->setText(synopsis);
        onColorSelected(QColor(color));

        for (QJsonValue v : jCharacters)
            selectedCharacters << mNovel->character(QUuid(v.toString()));
    } else {
        mIsNew = true;
        setWindowTitle(tr("New Plotline"));
    }

    for (Character *c : mNovel->characters()) {
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
    PlotlineItemModel *model = (PlotlineItemModel *) mTableView->model();
    QModelIndex index = mTableView->currentIndex();
    if (mIsNew){
        if (!model->insertRows(index.row()+1, 1)){
            qWarning("[+] plotline - could not insert rows at [%d, %d]",
                     index.row(), index.column());
            return;
        }
        index = model->index(index.row()+1, 0); // go to the inserted row.
    }

    QJsonArray charIds;
    for (QCheckBox *cb : mCharacterList.keys())
        if (cb->isChecked())
            charIds << QJsonValue(mCharacterList[cb]->id().toString());

    model->setData(index, ui->plotlineBrief->text(), PlotlineItemModel
                    ::BriefRole);
    model->setData(index, ui->plotlineSynopsis->toPlainText(),
                    PlotlineItemModel::SynopsisRole);
    model->setData(index, charIds, PlotlineItemModel::CharacterRole);
    model->setData(index, mColor, PlotlineItemModel::ColorRole);

    emit mTableView->activated(index);

    if (mIsNew)
        emit plotlineAdded(index);
    else
        emit plotlineModified(index);
}

void PlotlineDialog::on_characterSearch_textEdited(const QString &arg1)
{
    if (!arg1.isEmpty())
        clearLayout(ui->characterListLayout, false);
    for (QCheckBox *cb : mCharacterList.keys()){
        if (arg1.isEmpty()){
//            ui->characterListLayout->addWidget(cb);
        } else {
            QString name = mCharacterList[cb]->name();
            QString label = mCharacterList[cb]->label();
            qDebug() << "[?] character search: " << arg1.mid(1) << "in"
                     << label;
            if ((arg1.startsWith("@") && label.contains(arg1.mid(1)))
                || name.contains(arg1)){
//                ui->characterListLayout->addWidget(cb);
            }
        }
    }
}
