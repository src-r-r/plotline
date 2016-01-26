#include "revision.h"

const QString Revision::J_CONTENT = "content",
    Revision::J_CHAPTER = "chapter",
    Revision::J_IS_COMPLETE = "isComplete";

Revision::Revision(const QString &content, Chapter *chapter, bool isComplete,
                   int id, QObject *parent) : Serializable(id)
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
    int id = this->getId();

    QJsonObject object = QJsonObject();
    object[JSON_ID] = QJsonValue(id);
    object[J_CONTENT] = mContent;
    object[J_IS_COMPLETE] = QJsonValue(mIsComplete);

    return object;
}

Revision *Revision::deserialize(Novel *novel, Chapter *chapter,
                                const QJsonObject &object)
{
    QString content = QString();
    bool isComplete = false;
    int id = -1;
    if (object.contains(J_CONTENT))
        content = object[J_CONTENT].toString();
    if (object.contains(J_IS_COMPLETE))
        isComplete = object[J_IS_COMPLETE].toBool();
    if (object.contains(JSON_ID))
        id = object[JSON_ID].toInt();
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
