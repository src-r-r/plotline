#include "characterhighlighter.h"

CharacterHighlighter::CharacterHighlighter(Novel *novel, QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    mNovel = novel;
}

void CharacterHighlighter::highlightBlock(const QString &text)
{
    // First grab the locations of the characters within the text.
    ParsedCharacterSet set = ParsedCharacterSet::parse(mNovel, text);

    for (int i : set.keys()){
        QTextCharFormat format;
        QColor bgColor = set.value(i)->color();
        QColor textColor = QColor(0, 0, 0);         // Black text.
        if ((255 / 2) < bgColor.value())
            textColor = QColor(255, 255, 255);      // White text.
        format.setFontWeight(QFont::Bold);
        format.setBackground(QBrush(bgColor));
        format.setForeground(QBrush(textColor));

        setFormat(i, set.value(i)->label().count(), format);
    }
}

