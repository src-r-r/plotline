#ifndef PLOTLINEDIALOG_H
#define PLOTLINEDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QPainter>
#include <QtCore>
#include <QtDebug>
#include <QModelIndex>
#include <QWidget>
#include <QCheckBox>
#include <QtWidgets>

#include "plotline.h"
#include "plotframe.h"
#include "plotlineitemmodel.h"

class PlotFrame;

namespace Ui {
class PlotlineDialog;
}

class PlotlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotlineDialog(QTableView *tableView,
                            Novel *novel,
                            bool isNew = false,
                            QWidget *parent = 0);
    ~PlotlineDialog();

private slots:
    void on_plotlineColor_clicked();
    void onColorSelected(const QColor &color);
    void on_clearPlotlineColor_clicked();
    void on_buttonBox_accepted();

    void on_characterSearch_textEdited(const QString &arg1);

signals:

    void plotlineAdded(const QModelIndex &index);
    void plotlineModified(const QModelIndex &index);
    void canceled();

private:
    Ui::PlotlineDialog *ui;

    Novel *mNovel;
    QTableView *mTableView;
    QMap<QCheckBox *, Character *> mCharacterList;

    QColor mColor;

    bool mIsNew;
};

#endif // PLOTLINEDIALOG_H
