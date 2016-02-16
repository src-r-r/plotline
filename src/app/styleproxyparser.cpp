#include "styleproxyparser.h"

StyleProxyParser::StyleProxyParser(const QJsonObject &object)
{
    mObject = object;
}

StyleProxy *StyleProxyParser::parse(const QString &key) const
{
    if (!mObject.contains(key)){
        qWarning() << "Missing key" << key;
        return 0;
    }
    return StyleProxy::parse(mObject[key].toObject());
}

StyleProxy *StyleProxyParser::parse(const char *key) const
{
    return parse(QString(key));
}

QJsonObject StyleProxyParser::object() const
{
    return mObject;
}

void StyleProxyParser::setObject(const QJsonObject &object)
{
    mObject = object;
}

