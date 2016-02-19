#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H

#include <QtCore>
#include <QtDebug>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

#include "styleproxy.h"
#include "styleproxyparser.h"
#include "preferencesdialog.h"

class MarkupHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:

    enum MarkupLanguage {
        NoLanguage = 0,
        MarkDown,
        ReStructuredText
    };

    enum MarkupToken {
        Document = 0, // only used for styling/parsing style file.
        HtmlEscape,
        Header,
        BlockQuote,
        List,
        CodeBlock,
        HorizontalRule,
        InlineLink,
        LinkSource,
        LinkTarget,
        Emphasis,
        Strong,
        InlineCode,
        Image,
        AutomaticLink,
        BackslashEscape
    };

    explicit MarkupHighlighter(QObject *parent = 0);
    explicit MarkupHighlighter(QTextDocument *parent);
    explicit MarkupHighlighter(const MarkupLanguage language, QTextDocument *parent=0);

    virtual void highlightBlock(const QString & text);

    MarkupLanguage getLanguage() const;
    void setLanguage(const MarkupLanguage &value);

private:

    static const QString DEFAULT_STYLE_FILE;

    static const QMap<QString, MarkupToken> TOKENS;
    static const QMap<MarkupToken, const StyleProxy *> FORMATTING;
    MarkupLanguage mLanguage;

    static QMap<QString, MarkupHighlighter::MarkupToken> tokens();
    static QMap<MarkupToken, const StyleProxy *> formatting();
    QTextCharFormat parseFormat(const QTextCharFormat &baseFormat,
                                const QJsonObject &obj);

    static MarkupLanguage detectLanguage(const QSettings &settings);

signals:

public slots:
};

#endif // MARKDOWNHIGHLIGHTER_H
