#ifndef COMPLETABLE_H
#define COMPLETABLE_H

#include <QObject>

class Completable : public QObject
{
    Q_OBJECT
public:
    explicit Completable(QObject *parent = 0);

    bool isCompleted();
    void markCompleted();
    void unmarkCompleted();
    void toggleCompleted();

    Completable(const Completable &c);

protected:
    bool mComplete;

signals:

public slots:
    void setCompleted(int state);
};

#endif // COMPLETABLE_H
