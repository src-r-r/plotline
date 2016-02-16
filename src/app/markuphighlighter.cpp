#include "markuphighlighter.h"

const QString MarkupHighlighter::DEFAULT_STYLE_FILE = ":/styles/styles/default.json";
const QMap<QString, MarkupHighlighter::MarkupToken> MarkupHighlighter::TOKENS = tokens();
const QMap<MarkupHighlighter::MarkupToken, const StyleProxy *> MarkupHighlighter::FORMATTING = formatting();

QMap<QString, MarkupHighlighter::MarkupToken> MarkupHighlighter::tokens()
{
    QMap<QString, MarkupHighlighter::MarkupToken> tokens;
    const QString URL_RE = "(https?\\:\\/\\/)?[\\:\\;\\w\\d\\-\\.\\/\\?\\&]+";
    const QString BRACKET_RE = "\\[[^\\]]+\\]";
    tokens = QMap<QString, MarkupToken>();

    tokens["\\&[\\w\\d]+;"] = HtmlEscape;
    tokens["^#+.+$"] = Header;
    tokens["^>+.+$"] = BlockQuote;
    tokens["^((\\d\\.)|[\\*\\+\\-])\\s.*\\n[^\n]*$"] = List; // Careful here
    tokens["^\\s{4,}.+$"] = CodeBlock;
    tokens["^\\-{3,}"] = HorizontalRule;
    tokens[BRACKET_RE + "\\(" + URL_RE + "\\)"] = InlineLink;
    tokens["(" + BRACKET_RE + "){2}"] = LinkSource;
    tokens[BRACKET_RE + "\\:\\s+" + URL_RE + "\"[^\"\n]+\""] = LinkTarget;
    tokens["(?<!\\*)(\\*)[^\\*\\n]+(\\*)(?!\\*)|(?<!\\_)(\\_)[^\\_\\n]+(\\_)(?!\\_)"] = Emphasis;
    tokens["(\\*{2}[^\\*\n]+\\*{2}|\\_{2}[^\\_\n]+\\_{2})"] = Strong;
    tokens["`[^`]+`"] = InlineCode;
    tokens["\\!" + BRACKET_RE + "\\([^\\)]+\\)"] = Image;
    tokens["\\<" + URL_RE + "\\>"] = AutomaticLink;
    tokens["\\."] = BackslashEscape;

    return tokens;
}

QMap<MarkupHighlighter::MarkupToken, const StyleProxy*> MarkupHighlighter::formatting()
{
    Q_INIT_RESOURCE(plotline);
    QMap<MarkupHighlighter::MarkupToken, const StyleProxy *> formatting;
    QFile *f = new QFile(DEFAULT_STYLE_FILE);

    if (!f->open(QFile::ReadOnly)){
        qWarning() << "Could not open" << DEFAULT_STYLE_FILE;
        return formatting;
    }

    QByteArray raw = f->readAll();
    QJsonDocument jDoc = QJsonDocument::fromJson(raw);
    f->close();

    QJsonObject obj = jDoc.object();
    StyleProxyParser parser = StyleProxyParser(obj);

    formatting[HtmlEscape] = parser.parse("HtmlEscape");
    formatting[Header]  = parser.parse("Header");
    formatting[BlockQuote] = parser.parse("BlockQuote");
    formatting[List] = parser.parse("List");
    formatting[CodeBlock] = parser.parse("CodeBlock");
    formatting[HorizontalRule] = parser.parse("HorizontalRule");
    formatting[InlineLink] = parser.parse("InlineLink");
    formatting[LinkSource] = parser.parse("LinkSource");
    formatting[LinkTarget] = parser.parse("LinkTarget");
    formatting[Emphasis] = parser.parse("Emphasis");
    formatting[Strong] = parser.parse("Strong");
    formatting[InlineCode] = parser.parse("InlineCode");
    formatting[Image] = parser.parse("Image");
    formatting[AutomaticLink] = parser.parse("AutomaticLink");
    formatting[BackslashEscape] = parser.parse("BackslashEscape");

    return formatting;
}


MarkupHighlighter::MarkupHighlighter(QObject *parent)
    : QSyntaxHighlighter(parent)
{
    Q_INIT_RESOURCE(plotline);

}

MarkupHighlighter::MarkupHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    Q_INIT_RESOURCE(plotline);

}

MarkupHighlighter::MarkupHighlighter(const MarkupHighlighter::MarkupLanguage language, QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    Q_INIT_RESOURCE(plotline);
    mLanguage = language;
}

void MarkupHighlighter::highlightBlock(const QString &text)
{

    if (text.isEmpty()) return;

    int start=0, end=0, highlightLength = 0;


    QRegularExpression re;
    QTextCharFormat textFormat;
    for (QString exp : TOKENS.keys()){
        setCurrentBlockState(0);

        if (previousBlockState() != 1)
            start = re.match(text).capturedStart();

        re = QRegularExpression(exp);
        if (!re.isValid()){
            QString message = "Invalid regular expression \""
                    + re.pattern() + "\" :" + re.errorString();
            qFatal("%s", message.toStdString().data());
            return;
        }
        start = 0, end = 0;
        while (start >= 0){
            QRegularExpressionMatch match = re.match(text, start);
            end = match.capturedEnd();
            if (end == -1 || (end == start && end != 0)){
                setCurrentBlockState(1);
                highlightLength = text.length();
            } else {
                highlightLength = match.capturedLength();
            }
            QTextCharFormat baseFormat = currentBlock().blockFormat().toCharFormat();
            MarkupHighlighter::MarkupToken tok = TOKENS[exp];
            if (!FORMATTING.contains(tok)){
                qWarning() << "Could not find" << tok;
                break;
            }
            const StyleProxy *styleProxy = FORMATTING[tok];
            textFormat = styleProxy->toFormat(baseFormat);
            setFormat(start, highlightLength, textFormat);
            start = re.match(text, end).capturedStart();
            // This should not be 0 again. If it is, that means our search has
            // come up empty.
            if (start == 0)
                start = -1;
        }
    }
}

MarkupHighlighter::MarkupLanguage MarkupHighlighter::getLanguage() const
{
    return mLanguage;
}

void MarkupHighlighter::setLanguage(const MarkupHighlighter::MarkupLanguage &value)
{
    mLanguage = value;
}


