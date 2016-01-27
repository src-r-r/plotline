#ifndef UTILS_H
#define UTILS_H

#include <QBuffer>
#include <QImage>
#include <QJsonValue>
#include <QPixmap>

// Thanks to http://stackoverflow.com/a/32378165

QJsonValue jsonValFromPixmap(const QPixmap &p);
QJsonValue jsonValFromImage(const QImage &i);
QPixmap pixmapFrom(const QJsonValue & val);
QImage imageFrom(const QJsonValue &val);

#endif // UTILS_H
