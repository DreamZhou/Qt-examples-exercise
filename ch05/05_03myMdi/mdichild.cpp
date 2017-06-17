#include "mdichild.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QApplication>
#include <QFileDialog>
#include <QPushButton>
#include <QDebug>
#include <QtAlgorithms>
MdiChild::MdiChild(QWidget *parent):QTextEdit(parent)

{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;

    lineNumberArea = new LineNumberArea(this);

    // 文本快数量变化，更新行号区宽度
    connect(this, QTextDocument::blockCountChanged,this,updateLineNumberAreaWidth);
    connect(this,QEvent::UpdateRequest,this,updateLineNumberAreaWidth);
    connect(this,cursorPositionChanged,this,highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void MdiChild::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(),QT::lightGray);

    QTextDocument block = document()->firstBlock();
    int blockNumber = block.blockCount();
    int top = (int) blockBoundingGeometry(block).translated

}

int MdiChild::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1,QTextDocument::blockCount());
    while(max >= 10){
        max /= 10 ;
        ++digits;
    }
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void MdiChild::newFile()
{
    static int sequenceNumber = 1;
    isUntitled = true ;
    curFile = tr("NewFile%1.txt").arg(sequenceNumber++);
//    qDebug() << curFile ;
    setWindowTitle(curFile + "[*]" + tr(" - 多文档编辑器"));
    connect(document(),QTextDocument::contentsChanged,
            this,documentWasModified);

}
bool MdiChild::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
     QMessageBox::warning(this,tr("MDIEdit"),
                            tr("Can not read file%1:\n %2")
                            .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream  in(&file);
    //设置鼠标状态为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //读取文件的全部文本内容，并添加到编辑器中
    setPlainText(in.readAll());
    //恢复鼠标状态
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    connect(document(),QTextDocument::contentsChanged,
            this,MdiChild::documentWasModified);
    return true;

}

bool MdiChild::save()
{
    //如过文件没有被保存过,则执行另存为操作,否则直接保存文件.
    if (isUntitled)
        return saveAs();
    else
        return saveFile(curFile);
}

bool MdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,tr("MDIEdit"),tr("Cannot write file %1:\n%2")
                             .arg(QDir::toNativeSeparators(fileName),file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    return true;
}


bool MdiChild::maybeSave()
{
    if (document()->isModified()){
        QMessageBox msgbox;
        msgbox.setWindowTitle(tr("MDIEdit"));
        msgbox.setText(tr("'%1' has been modified.\n"
                          "Do you Want to save your changes?")
                       .arg(userFriendlyCurrentFile()));
        msgbox.setIcon(QMessageBox::Warning);
        QPushButton * yesBtn = msgbox.addButton(tr("&Yes"),QMessageBox::YesRole);
        msgbox.addButton(tr("&No"),QMessageBox::NoRole);
        QPushButton * cancelBtn = msgbox.addButton(tr("&Cancel"),
                                        QMessageBox::RejectRole);
        msgbox.exec();
        if (msgbox.clickedButton() == yesBtn)
            return save();
        else if (msgbox.clickedButton() == cancelBtn)
            return false;
    }
    return true;
}

void MdiChild::setCurrentFile(const QString &fileName)
{
    //canonicalFilePath() 可以去除路径中的符号链接，"." 和".."等
    curFile = QFileInfo(fileName).canonicalFilePath();
    // file has been saved.
    isUntitled = false ;
    // 文档没有被更改过
    document()->setModified(false);
    //窗口不显示被更改标志
    setWindowModified(false);
    // 设置窗口标题,userFriendlyCurrentFile() 返回文件名
    setWindowTitle(userFriendlyCurrentFile() + "[*]" +tr(" - 多文档编辑器"));
    qDebug()<< userFriendlyCurrentFile() + "[*]" +tr(" - 多文档编辑器");
}
QString MdiChild::userFriendlyCurrentFile()
{
    //从文件路径中提取文件名
//    qDebug() << QFileInfo(curFile).fileName();
    return QFileInfo(curFile).fileName();
}

void MdiChild::closeEvent(QCloseEvent *event)
{
    //如果maybeSave()函数返回true，则关闭窗口，否则忽略改时间
    if (maybeSave()){
        event->accept();
    }else {
        event->ignore();
    }
}

void MdiChild::resizeEvent(QResizeEvent *event)
{
    MdiChild::resizeEvent(event);
    QRect cr = contentsRect(); //内部区域
    lineNumberArea->setGeometry(Rect(cr.left(),cr.top()),lineNumberAreaWidth(),cr.height());

}

void MdiChild::documentWasModified()
{
    setWindowModified(document()->isModified());
}

void MdiChild::updateLineNumberAreaWidth(int newBlockCount)
{
    //可视区域到边框的距离。这个区域时行号栏用的
    setViewportMargins(lineNumberAreaWith(),0,0,0);


}

void MdiChild::highlightCurrentLine()
{
    QList<MdiChild::ExtraSelection> extraSelections;
    if (!isReadOnly()){
        MdiChild::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection,true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);

}

void MdiChild::updateLineNumberArea(const QRect & rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0,dy);
    else
        lineNumberArea->update(0,rect.y(),lineNumberArea->width(),rect.height());
    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

