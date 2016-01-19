#include "completable.h"

Completable::Completable(QObject *parent) : QObject(parent)
{
    this->mComplete = false;
}

bool Completable::isCompleted()
{
    return this->isCompleted();
}

void Completable::markCompleted()
{
    this->mComplete = true;
}

void Completable::unmarkCompleted()
{
    this->mComplete = false;
}

void Completable::toggleCompleted()
{
    this->mComplete = !this->mComplete;
}

void Completable::setCompleted(int state)
{
    this->mComplete = (state == Qt::Checked);
}

Completable::Completable(const Completable &c) : QObject(c.parent())
{
    this->mComplete = c.mComplete;
}
