#ifndef NOVELFRAME_H
#define NOVELFRAME_H

#include "plotlineappframe.h"

namespace Ui {
class NovelFrame;
}

class NovelFrame : public PlotlineAppFrame
{
    Q_OBJECT

public:
    explicit NovelFrame(Novel *novel, QWidget *parent = 0);
    ~NovelFrame();

private slots:
    void on_tense_activated(int index);
    void on_pointofView_activated(int index);
    void on_workingTitle_textEdited(const QString &arg1);
    void on_genre_textEdited(const QString &arg1);
    void on_setting_textEdited(const QString &arg1);

public slots:
    void onNovelLoad();
    void onNovelNew();

private:
    Ui::NovelFrame *ui;
};

#endif // NOVELFRAME_H
