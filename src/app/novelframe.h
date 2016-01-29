#ifndef NOVELFRAME_H
#define NOVELFRAME_H

#include <QFrame>

namespace Ui {
class NovelFrame;
}

class NovelFrame : public QFrame
{
    Q_OBJECT

public:
    explicit NovelFrame(Novel *novel, QWidget *parent = 0);
    ~NovelFrame();

    Novel *novel() const;
    void setNovel(Novel *novel);

private:
    Ui::NovelFrame *ui;

    Novel *mNovel;
};

#endif // NOVELFRAME_H
