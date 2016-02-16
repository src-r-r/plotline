#ifndef STYLEPROXY_H
#define STYLEPROXY_H

#include <QtCore>
#include <QColor>
#include <QTextCharFormat>

class StyleProxy : public QObject
{
    Q_OBJECT
public:
    explicit StyleProxy(bool bold=false, bool itallic=false, int relSize=0,
                        QColor foreground=QColor(),
                        QColor background=QColor(),
                        QObject *parent = 0);

    bool bold() const;
    void setBold(bool bold);

    bool itallic() const;
    void setItallic(bool itallic);

    int relSize() const;
    void setRelSize(int relSize);

    QColor foreground() const;
    void setForeground(const QColor &foreground);

    QColor background() const;
    void setBackground(const QColor &background);

    static StyleProxy* parse(QJsonObject object);
    QTextCharFormat toFormat(const QTextCharFormat &base) const;

private:
    bool mBold, mItallic;
    int mRelSize;
    QColor mForeground, mBackground;

signals:

public slots:
};

#endif // STYLEPROXY_H
