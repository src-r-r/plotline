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

void setEnabledRecursive(QLayout *layout, bool enabled)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            widget->setEnabled(enabled);
        if (QLayout* childLayout = item->layout())
            setEnabledRecursive(childLayout, enabled);
    }
}

void setDisabledRecursive(QLayout *layout, bool disabled)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            widget->setDisabled(disabled);
        if (QLayout* childLayout = item->layout())
            setDisabledRecursive(childLayout, disabled);
    }
}

/**
 * @brief multilineOffset Given an offset in a multi-line string, determine
 * the line and column number of that offset. Useful for error messages.
 * @param string
 * @param offset Location within the string.
 * @return A pair of integers (line, col) where line is the line number and
 * col is the column number within the line where the error occurrs.
 */
QPair<int, int> multilineOffset(QString string, int offset)
{
    int nLines = -1, nCols = -1;
    for (int i = 0; i < offset && offset < string.length(); ++i){
        ++nCols;
        if (string[i] == '\n'){
            nCols = -1;
            ++nLines;
        }
    }
    return QPair<int, int>(nLines, nCols);
}

/**
 * @brief reflowParagraph Given a paragraph, reflow the paragraph so that
 * the line length is no more that `width` characters.
 * @param paragraph Paragraph to reflow.
 * @param width Width of the paragraph.
 * @return The paragraph reflowed.
 */
QString reflowParagraph(const QString &paragraph, const int width)
{
    QString p2 = paragraph;
    p2.replace('\n', ' ');
    QStringList words = p2.split(" ");

    p2.clear();
    QString line;
    for (QString word : words){
        if (line.length() + word.length() > width){
            p2 += line + QString("\n");
            line.clear();
        }
        if (!line.isEmpty()) line += " ";
        line += word;
    }
    if (!line.isEmpty()) p2 += line;
    return p2;
}

/**
 * @brief reflowParagraphs Given several paragraphs, reflow each one so that
 * for each paragraph, the line length is no more than `width` characters. This
 * assumes Markup formatting, so that a real paragraph is seperated by 2 line
 * break.s
 * @param content content to reflow.
 * @param width maximum width of the line.
 * @return Content with each paragraph reflowed.
 */
QString reflowParagraphs(const QString &content, const int width){
    QStringList paragraphs = content.split("\n\n");
    QString content2;
    for (int i = 0; i < paragraphs.count(); ++i){
        content2 += reflowParagraph(paragraphs[i], width);
        if (i < paragraphs.count()-1)
            content2 += "\n\n";
    }
    return content2;
}

QString toRomanNumeral(const int number)
{
    return QString();
}

QString toWord(const int number)
{
    return QString();
}
