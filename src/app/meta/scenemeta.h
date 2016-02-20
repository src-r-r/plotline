#ifndef SCENEMETA_H
#define SCENEMETA_H

#include <QtCore>
#include <QDebug>
#include "scene.h"

class SceneMeta : public QMetaObject
{
public:
    SceneMeta();

    const char *className() const;
    const QMetaObject * superClass() const;
    QMetaMethod method(int index) const;
    int methodCount() const;
    QMetaEnum enumerator(int index) const;
    int propertyCount() const;
    QMetaMethod constructor(int index) const;
    int constructorCount() const;

signals:

public slots:
};

#endif // SCENEMETA_H
