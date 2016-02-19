#include "styleproxy.h"

StyleProxy::StyleProxy(bool bold, bool italic, int relSize,
                       QColor foreground,
                       QColor background,
                       QObject *parent) : QObject(parent)
{
    mBold = bold;
    mItallic = italic;
    mRelSize = relSize;
    mForeground = foreground;
    mBackground = background;
}

bool StyleProxy::bold() const
{
    return mBold;
}

void StyleProxy::setBold(bool bold)
{
    mBold = bold;
}

bool StyleProxy::itallic() const
{
    return mItallic;
}

void StyleProxy::setItallic(bool itallic)
{
    mItallic = itallic;
}

int StyleProxy::relSize() const
{
    return mRelSize;
}

void StyleProxy::setRelSize(int relSize)
{
    mRelSize = relSize;
}

QColor StyleProxy::foreground() const
{
    return mForeground;
}

void StyleProxy::setForeground(const QColor &foreground)
{
    mForeground = foreground;
}

QColor StyleProxy::background() const
{
    return mBackground;
}

void StyleProxy::setBackground(const QColor &background)
{
    mBackground = background;
}

StyleProxy *StyleProxy::parse(QJsonObject object)
{
    bool bold = false, italic = false;
    int relSize = 0;
    QColor foreground, background;

    if (object.contains("bold")){
        bold = object["bold"].toBool();
        qDebug() << "  found bold=" << bold;
    }if (object.contains("italic")){
        italic = object["italic"].toBool();
        qDebug() << "  found italic=" << italic;
    }if (object.contains("relSize")){
        relSize = object["relSize"].toInt();
        qDebug() << "  found relSize=" << relSize;
    }if (object.contains("foreground") && !object["foreground"].isNull()){
        if (object["foreground"].isArray()){
            QJsonArray arr = object["foreground"].toArray();
            int r = arr[0].toInt(), g = arr[1].toInt(), b = arr[2].toInt(),
                    a = arr[3].toInt();
            foreground = QColor(r, g, b, a);
        } else {
            foreground = QColor(object["background"].toString());
        }

        if (!foreground.isValid())
            qWarning() << "Invalid fg color:" << object["background"].toString();
        qDebug() << "  found foreground=" << foreground;
    }
    if (object.contains("background") && !object["background"].isNull()){
        if (object["background"].isArray()){
            QJsonArray arr = object["background"].toArray();
            int r = arr[0].toInt(), g = arr[1].toInt(), b = arr[2].toInt(),
                    a = arr[3].toInt();
            background = QColor(r, g, b, a);
        } else {
            background = QColor(object["background"].toString());
        }
        if (!background.isValid())
            qWarning() << "Invalid bg color:" << object["foreground"].toString();
        qDebug() << "  found background=" << background;
    }

    qDebug() << "Leaving styleProxy::parse";

    return new StyleProxy(bold, italic, relSize, foreground, background);
}

QTextCharFormat StyleProxy::toFormat(const QTextCharFormat &base) const
{
    QTextCharFormat fmt;

    QFont font = base.font();

    font.setBold(mBold);
    font.setItalic(mItallic);
    font.setPointSize(font.pointSize() + mRelSize);
    fmt.setFont(font);

    if (mForeground.isValid())
        fmt.setForeground(QBrush(mForeground));
    if (mBackground.isValid())
        fmt.setBackground(QBrush(mBackground));

    qDebug() << "Entering toFormat";
    qDebug() << "is bold?" << fmt.font().bold();
    qDebug() << "is Italic?" << fmt.font().italic();
    qDebug() << "point size:" << fmt.font().pointSize();

    return fmt;
}

