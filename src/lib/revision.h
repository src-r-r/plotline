#ifndef REVISION_H
#define REVISION_H

#include "novel.h"
#include "serializable.h"
#include "completable.h"
#include "chapter.h"

class Chapter;
class Novel;

class Revision : public QObject, public Serializable
{
    Q_OBJECT
public:
    explicit Revision(const QString &content = QString(),
                      Chapter *chapter = 0,
                      bool isComplete = false,
                      const QUuid &id = QUuid(),
                      QObject *parent = 0);

    QString content() const;
    Chapter *chapter() const;

    void setChapter(Chapter *chapter);
    void setContent(const QString &content);

    QJsonObject serialize() const;
    static Revision *deserialize(Novel *novel, Chapter *chapter,
                                 const QJsonObject &object);
    static QList<Revision *> deserialize(Novel *novel, Chapter *chapter,
                                         const QJsonArray &object);

    bool isComplete() const;
    void setIsComplete(bool isComplete);
    void toggleComplete();

private:
    QString mContent;
    Chapter *mChapter;
    bool mIsComplete;

    static const QString J_CONTENT,
        J_CHAPTER,
        J_IS_COMPLETE;

signals:

public slots:
};

#endif // REVISION_H
