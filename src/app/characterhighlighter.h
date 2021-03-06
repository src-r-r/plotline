#ifndef CHARACTERHIGHLIGHTER_H
#define CHARACTERHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

#include "novel.h"
#include "characterparser.h"

class CharacterHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    CharacterHighlighter(Novel *novel, QTextDocument *parent = 0);
    CharacterHighlighter(Novel *novel, QObject *parent = 0);

    Novel *novel() const;
    void setNovel(Novel *novel);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    Novel *mNovel;
};

#endif // CHARACTERHIGHLIGHTER_H
