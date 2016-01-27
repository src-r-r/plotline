#include "utils.h"

QJsonValue jsonValFromPixmap(const QPixmap & p) {
  QByteArray data;
  QBuffer buffer { &data };
  buffer.open(QIODevice::WriteOnly);
  p.save(&buffer, "PNG");
  auto encoded = buffer.data().toBase64();
  return QJsonValue(QString::fromLatin1(encoded));
}

QPixmap pixmapFrom(const QJsonValue & val) {
  QByteArray encoded = val.toString().toLatin1();
  QPixmap p;
  p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
  return p;
}

QImage imageFrom(const QJsonValue &val)
{
    return pixmapFrom(val).toImage();
}

QJsonValue jsonValFromImage(const QImage &i)
{
    return jsonValFromPixmap(QPixmap::fromImage(i));
}
