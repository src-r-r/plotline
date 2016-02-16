#ifndef STYLEPROXYPARSER_H
#define STYLEPROXYPARSER_H

#include <QtCore>
#include <QObject>
#include <styleproxy.h>

class StyleProxyParser
{
public:
    StyleProxyParser(const QJsonObject &object=QJsonObject());

    StyleProxy *parse(const QString &key) const;
    StyleProxy *parse(const char *key) const;

    QJsonObject object() const;
    void setObject(const QJsonObject &object);

private:
    QJsonObject mObject;
};

#endif // STYLEPROXYPARSER_H
