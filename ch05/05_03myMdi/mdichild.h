#ifndef MDICHILD_H
#define MDICHILD_H

#include <QObject>
#include <QTextEdit>
#include <QCloseEvent>
class QPaintEvent;
class QSize;
class QWidget;
class LineNumberArea;
class MdiChild : public QTextEdit
{
    Q_OBJECT
public:
    explicit MdiChild(QWidget * parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);  //
    int  lineNumberAreaWidth();                         //

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);   //保存文件
    QString userFriendlyCurrentFile();        // 提取文件名
    QString currentFile() {return curFile;}    //返回当前文件路径
protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;     //

private slots:
    void documentWasModified();

    void updateLineNumberAreaWidth(int newBlockCount);  //
    void highlightCurrentLine();                        //
    void updateLineNumberArea(const QRect &rect, int dy);      //

private:
    QWidget * lineNumberArea;
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString curFile;
    bool isUntitled;
};
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(MdiChild * editor) : QWidget(editor),editor_(editor)
    {  }
    QSize sizeHint() const override
    {
        return QSize(editor_->lineNumberAreaWidth(),0);
    }
private:
    MdiChild * editor_;
};
#endif // MDICHILD_H
