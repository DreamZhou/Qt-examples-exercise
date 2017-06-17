#include "mysyntaxhighlighter.h"
#include <QTextCharFormat>
MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{

}

void MySyntaxHighlighter::highlightBlock(const QString &text)  // 高亮文本快
{
    QTextCharFormat myFormat;                   //字符格式
    myFormat.setFontWeight(QFont::Bold);
    myFormat.setForeground(Qt::green);
    QString pattern = "\\bchar\\b";             //要匹配的字符串 "char"
    QRegExp expression(pattern);                //创建正则表达式
    int index = text.indexOf(expression);       //从0开始匹配字符串
    //如果匹配成功,那么返回值为字符串的起始位置,他大于或等于0
    while (index > 0) {
        int length = expression.matchedLength(); //要匹配字符串的长度
        setFormat(index,length,myFormat);
        index = text.indexOf(expression,index +1);
    }
}
