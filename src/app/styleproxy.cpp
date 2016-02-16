#include "styleproxy.h"

StyleProxy::StyleProxy(bool bold, bool itallic, int relSize,
                       QColor foreground,
                       QColor background,
                       QObject *parent) : QObject(parent)
{
    mBold = bold;
    mItallic = itallic;
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

    if (object.contains("bold"))
        bold = object["bold"].toBool();
    if (object.contains("italic"))
        italic = object["italic"].toBool();
    if (object.contains("relSize"))
        relSize = object["relSize"].toInt();
    if (object.contains("foreground") && !object["foreground"].isNull()){
        if (object["foreground"].isArray()){
            QJsonArray arr = object["foreground"].toArray();
            int r = arr[0].toInt(), g = arr[1].toInt(), b = arr[2].toInt(),
                    a = arr[3].toInt();
            foreground = QColor(r, g, b, a);
        } else {
            foreground = QColor(object["background"].toString());
        }
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
    }

    return new StyleProxy(bold, italic, relSize, foreground, background);
}

QTextCharFormat StyleProxy::toFormat(const QTextCharFormat &base) const
{
    QTextCharFormat fmt = base;

    QFont font = fmt.font();

    font.setBold(this->mBold);
    font.setItalic(this->mItallic);
    font.setPointSize(fmt.font().pointSize() + this->mRelSize);
    fmt.setFont(font);
    fmt.setForeground(QBrush(this->mForeground));
    fmt.setBackground(QBrush(this->mBackground));

    return fmt;
}

