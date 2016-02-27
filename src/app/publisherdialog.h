#ifndef PUBLISHERDIALOG_H
#define PUBLISHERDIALOG_H

#include <QDialog>
#include "novel.h"

namespace Ui {
class PublisherDialog;
}

class PublisherDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PublisherDialog(Novel *novel, QWidget *parent = 0);
    ~PublisherDialog();

private slots:
    void on_chooseDirectory_clicked();

    void on_chapterHeaderCombo_activated(int index);

    void on_chapterHeaderText_cursorPositionChanged(int arg1, int arg2);

    void on_titleText_cursorPositionChanged(int arg1, int arg2);

    void on_titleCombo_activated(int index);

private:
    Ui::PublisherDialog *ui;

    Novel *mNovel;

    static const QStringList Extensions, ChapterPlaceholders,
        HeaderPlaceholders;

    static const int Blank = 0,
        NewLine = 1,
        RomanNumber = 2,
        LatinNumber = 3,
        TextNumber = 4,
        ChapterTitle = 5;

    int chapterTextPos = 0, headerTextPos = 0;
};

#endif // PUBLISHERDIALOG_H
