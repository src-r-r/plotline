#ifndef NOVEL_H
#define NOVEL_H

#include <QObject>
#include <novelpart.h>

class Novel : public QObject
{
private:
    QString
        *workingTitle,
        *genre,
        *tense,
        *setting;
    QLinkedList<NovelPart> *parts;

    Q_OBJECT
public:
    explicit Novel(QObject *parent = 0);

signals:

public slots:
};

#endif // NOVEL_H
