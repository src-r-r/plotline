#include "plotlinedialog.h"
#include "ui_plotlinedialog.h"

PlotlineDialog::PlotlineDialog(Novel *novel, Plotline *plotline, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotlineDialog)
{
    ui->setupUi(this);
    mNovel = novel;
    if (!plotline){
        mPlotline = new Plotline("", "");
        mIsNew = true;
    }
    mIsNew = false;

    QList<Character *> characters = mNovel->characters();
    for (Character *c : characters){
        if (!c->getIsArchived()){
            qDebug() << "Fetching character" << c->id();
            ui->plotlineCharacterSelect->addItem(c->name(), QVariant(c->id()));
        }
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
    mPlotline->setColor(color);
    QImage image = QImage(30, 10, QImage::Format_RGB32);
    image.fill(mPlotline->getColor());
    QIcon icon = QIcon(QPixmap::fromImage(image));
    ui->plotlineColor->setIcon(icon);
}


void PlotlineDialog::on_clearPlotlineColor_clicked()
{
    mPlotline->setColor(QColor());
}

void PlotlineDialog::on_buttonBox_accepted()
{
    mPlotline->setBrief(ui->plotlineBrief->text());
    mPlotline->setSynopsis(ui->plotlineSynopsis->toHtml());
    // Color and character list is modified by slots.

    if (mIsNew)
        mNovel->addPlotline(mPlotline);

    emit mNovel->plotlinesChanged();
}

void PlotlineDialog::on_plotlineCharacterSelect_activated(int index)
{
    // We'll be sneaky here and hide the character ID within the list. This
    // way we can easily remove the user from the plotline.
    int charId = ui->plotlineCharacterSelect->itemData(index).toInt();

    // Remove the item from the combobox.
    ui->plotlineCharacterSelect->removeItem(index);

    Character *character = mNovel->character(charId);
    QListWidgetItem *item = new QListWidgetItem(character->name());
    item->setData(Qt::UserRole, QVariant(charId));
    item->setData(Qt::UserRole+1, QVariant(index));
    ui->plotlineCharacterList->addItem(item);
}

void PlotlineDialog::on_plotlineCharacterList_activated(const QModelIndex &index)
{
    // Remove the user from the list and add back to the QComboBox in the
    // original spot.
    QListWidgetItem *item = ui->plotlineCharacterList->item(index.row());
    int charId = item->data(Qt::UserRole).toInt();
    int row = item->data(Qt::UserRole+1).toInt();
    Character *c = mNovel->character(charId);
    ui->plotlineCharacterSelect->insertItem(row, c->name());

    // Also remove from the plotline character list.
    mPlotline->removeCharacter(c);
}
