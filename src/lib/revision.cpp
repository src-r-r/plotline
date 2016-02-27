#include "revision.h"

const QString Revision::J_CONTENT = "content",
    Revision::J_CHAPTER = "chapter",
    Revision::J_IS_COMPLETE = "isComplete";

Revision::Revision(const QString &content, Chapter *chapter, bool isComplete,
                   const QUuid &id, QObject *parent)
    : QObject(parent), Serializable(id)
{
    mContent = content;
    mChapter = chapter;
    mIsComplete = isComplete;
}

QString Revision::content() const
{
    return mContent;
}

void Revision::setContent(const QString &content)
{
    mContent = content;
}

QJsonObject Revision::serialize() const
{
    const QUuid id = this->id();

    QJsonObject object = QJsonObject();
    object[JSON_ID] = id.toString();
    object[J_CONTENT] = mContent;
    object[J_IS_COMPLETE] = QJsonValue(mIsComplete);

    return object;
}

Revision *Revision::deserialize(Novel *novel, Chapter *chapter,
                                const QJsonObject &object)
{
    Q_UNUSED(novel);
    QString content = QString();
    bool isComplete = false;
    QUuid id;
    if (object.contains(J_CONTENT))
        content = object[J_CONTENT].toString();
    if (object.contains(J_IS_COMPLETE))
        isComplete = object[J_IS_COMPLETE].toBool();
    if (object.contains(JSON_ID))
        id = QUuid(object[JSON_ID].toString());
    Revision *revision = new Revision(content, chapter, isComplete, id);

    revision->setChapter(chapter);

    return revision;
}

QList<Revision *> Revision::deserialize(Novel *novel, Chapter *chapter,
                                        const QJsonArray &array)
{
    QList<Revision *> revisions = QList<Revision *>();
    for (QJsonValue obj : array)
        revisions << Revision::deserialize(novel, chapter, obj.toObject());

    return revisions;
}

bool Revision::isComplete() const
{
    return mIsComplete;
}

void Revision::setIsComplete(bool isComplete)
{
    mIsComplete = isComplete;
}

void Revision::toggleComplete()
{
    setIsComplete(!mIsComplete);
}

Chapter *Revision::chapter() const
{
    return mChapter;
}

void Revision::setChapter(Chapter *chapter)
{
    mChapter = chapter;
}
