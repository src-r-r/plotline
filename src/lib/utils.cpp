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

QString friendlyList(const QStringList &stringList)
{
    QString result = QString();
    qWarning() << "friendlyList() Not implemented";
    return result;
}

void clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

/**
 * @brief findCharReverse Given an initial position, look backward in a string
 * for a given character.
 * @param chars Characters for which to search (e.g. "#@%")
 * @param s String in which to search (e.g. "We want to %eat something.")
 * @param from <i>last</i> position for the substring.
 * @param escape If we reach an escape character before the search character,
 * this function will return -1;
 * @return -1 if nothing is found before an escape character is reached.
 */
int findCharReverse(const QString &chars, const QString &s, const int from,
                    const QString &escape)
{
    int start = from;
    for (start = from; start >= 0; --start){
        if (chars.contains(s[start]))
            return start;
        if (escape.contains(s[start]))
            return -1;
    }
    return -1;
}

/**
 * @brief substring Get a substring of another String.
 * @param string String from which to get the substring.
 * @param start Index from which to start (less than the string length).
 * @param end End index of the substring (greater than the start).
 * @return
 */
QString substring(const QString &string, int start, int end)
{
    end = end < 0 ? string.length() : end;
    if (start > string.length()-1)
        return string;

    QString sub = QString();
    for (int i = start; i < end; ++i)
        sub += string[i];
    return sub;
}
