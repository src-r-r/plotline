#ifndef NOVEL_H
#define NOVEL_H

#include <QObject>
#include <QtDebug>
#include <stdlib.h>
#include "plotline.h"
#include "chapter.h"
#include "serializable.h"
#include "revision.h"

class Chapter;
class Plotline;
class Character;
class Scene;
class Revision;

class Novel : public QObject, public Serializable
{
    Q_OBJECT

public:
    enum Tense {
        Past=0, Present, Future, OtherTense,
    };

    enum PointOfView {
        FirstPersonSingular=0, SecondPersonSingular, ThirdPersonSingular,
        FirstPersonPlural, SecondPersonPlural, ThirdPersonPlural,
        OtherPointOfView,
    };

    explicit Novel(const QString &mWorkingTitle,
                   const QString &mGenre = QString(),
                   const QString &mSetting = QString(),
                   const Novel::Tense tense = Past,
                   const Novel::PointOfView pov = ThirdPersonSingular,
                   const QList<Character *> characters = QList<Character *>(),
                   const QList<Scene *> scenes = QList<Scene *>(),
                   const QList<Chapter *> chapters = QList<Chapter *>(),
                   const QList<Plotline *> plotlines = QList<Plotline *>(),
                   const QStringList &revisions = QStringList(),
                   int currentRevision = -1,
                   int id = -1,
                   QObject *parent = 0);
    ~Novel();

    QString getWorkingTitle() const;

    QString getGenre() const;
    void setWorkingTitle(const QString &value);
    void setGenre(const QString &value);
    void setSetting(const QString &value);

    Novel::Tense getTense() const;
    void setTense(const Novel::Tense tense);

    QString getSetting() const;

    QList<Scene *> scenes() const;
    void setScenes(const QList<Scene *> &value);
    void addScene(Scene *scene, int i=-1);
    void removeScene(Scene *scene);
    void removeScene(int id);
    Scene *scene(int id) const;
    void moveScenes(int from, int to);

    QList<Chapter *> chapters() const;
    Chapter *chapterByNumber(int number);
    Chapter *chapter(int id) const;
    void setChapters(const QList<Chapter *> &value);
    void addChapter(Chapter *chapter, int loc = -1);
    Revision *chapterRevision(int chapter, int revision);
    void removeChapter(Chapter *chapter);
    void removeChapterAt(int index, bool doDelete=false);
    void moveChapter(int from, int to);

    Novel::PointOfView getPointOfView() const;
    void setPointOfView(const Novel::PointOfView &pointOfView);

    QList<Plotline *> plotlines() const;
    Plotline *plotline(int id) const;
    void setPlotlines(const QList<Plotline *> &plotlines);
    void addPlotline(Plotline *plotline, int before=-1);
    void removePlotline(Plotline *plotline);
    void removePlotline(const int id);

    QList<Character *> characters();
    QList<Character *> characters(const QRegularExpression &exp) const;
    QList<Character *> characters(const QString &label) const;
    QList<Character *> charactersByName(const QRegularExpression &exp) const;
    QList<Character *> charactersByName(const QString &name) const;
    void setCharacters(const QList<Character *> &characters);
    Character *character(int id) const;
    Character *character(const QString label) const;
    void addCharacter(Character *character, const int i=-1);

    QJsonObject serialize() const;
    static Novel *deserialize(const QJsonObject &object);
    QString writeTo(const QString &filePath);
    static Novel *readFrom(const QString &filePath, QString *error = 0);

    QStringList revisions() const;
    void addRevision(const QString &comment = QString());
    void addRevisions(const QStringList &comments);
    void removeRevision(const int index=-1);
    void setRevisions(const QStringList &revisions);
    void setRevisionComment(const int index, const QString &comment);
    void setRevisionComment(const QString &comment);
    QString revisionComment(const int index=-1) const;
    int revisionCount() const;
    void goToLatestRevision();

    int currentRevision() const;
    void setCurrentRevision(int currentRevison);

private:

    static const QString JSON_WORKING_TITLE,
    JSON_GENRE,
    JSON_SETTING,
        JSON_TENSE,
        JSON_POV,
        JSON_SCENES,
        JSON_CHARACTERS,
        JSON_CHAPTERS,
        JSON_PLOTLINES,
        JSON_REVISIONS,
        JSON_CURRENT_REVISION;

    QString mWorkingTitle,
        mGenre,
        mSetting;
    Novel::Tense mTense;
    Novel::PointOfView mPointOfView;
    QList<Character *> mCharacters;
    QList<Scene *> mScenes;
    QList<Chapter *> mChapters;
    QList<Plotline *> mPlotlines;

    QStringList mRevisions;
    int mCurrentRevision;

signals:

    void plotlinesChanged();

public slots:

};

#endif // NOVEL_H
