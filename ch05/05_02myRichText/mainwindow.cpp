#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextFrame>
#include <QTextCursor>
#include <QDebug>
#include <QFileDialog>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include "mysyntaxhighlighter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextDocument * document = ui->textEdit->document();  // 获取文档对象
    QTextFrame *rootFrame = document->rootFrame();  //获取根框架
    QTextFrameFormat format;                        //获取框架格式
    format.setBorderBrush(Qt::red);                 //边界颜色
    format.setBorder(3);                            //边界宽度
    rootFrame->setFrameFormat(format);              //框架使用格式

    QTextFrameFormat frameFormat;
    frameFormat.setBackground(Qt::lightGray);           //设置背景
    frameFormat.setMargin(10);                          //设置边距
    frameFormat.setPadding(5);                          //设置填衬
    frameFormat.setBorder(2);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertFrame(frameFormat);

    QAction *action_textFrame = new QAction(tr("框架"),this);
    connect(action_textFrame,QAction::triggered,this,showTextFrame);
    ui->mainToolBar->addAction(action_textFrame);

    QAction *action_textBlock = new QAction(tr("Block"),this);
    connect(action_textBlock,QAction::triggered,this,showTextBlock);
    ui->mainToolBar->addAction(action_textBlock);

    QAction *action_font = new QAction(tr("setFont"),this);
    action_font->setCheckable(true);
    connect(action_font,QAction::toggled,this,setTextFont);
    ui->mainToolBar->addAction(action_font);

    QAction *action_textTable = new QAction(tr("表格"),this);
    QAction *action_textList = new QAction(tr("列表"),this);
    QAction *action_textImage = new QAction(tr("图片"),this);
    connect(action_textTable,QAction::triggered,this,insertTable);
    connect(action_textList,QAction::triggered,this,insertList);
    connect(action_textImage,QAction::triggered,this,insertImage);
    ui->mainToolBar->addAction(action_textTable);
    ui->mainToolBar->addAction(action_textList);
    ui->mainToolBar->addAction(action_textImage);

    QAction *action_textFind = new QAction(tr("查找"),this);
    connect(action_textFind,QAction::triggered,this,textFind);
    ui->mainToolBar->addAction(action_textFind);
    highlighter = new MySyntaxHighlighter(ui->textEdit->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()
{
    QTextDocument *document = ui->textEdit->document();
    QTextFrame *frame = document->rootFrame();
//    QTextFrame::iterator it;
    for (auto it = frame->begin(); !(it.atEnd()); ++it){
        QTextBlock childBlock = it.currentBlock();
        QTextFrame *childFrame = it.currentFrame();
        if (childBlock.isValid()){
            qDebug() << "block" << childBlock.text();
        }
        else if(childFrame)
            qDebug() << "frame";
    }
}

void MainWindow::showTextBlock()
{
    QTextBlock  block = ui->textEdit->document()->firstBlock();
    for (auto i = 0 ; i < ui->textEdit->document()->blockCount() ; ++i){
         qDebug() << tr("文本块 %1,文本快首行行号为: %2,长度为: %3,内容为: ")
                     .arg(i).arg(block.firstLineNumber()).arg(block.length())
                  << block.text();
         block = block.next();
    }
}

void MainWindow::setTextFont(bool checked)
{
    if (checked){
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignCenter);
        cursor.insertBlock(blockFormat);
        QTextCharFormat charFormat;
        charFormat.setBackground(Qt::red);
        charFormat.setForeground(Qt::white);
        charFormat.setFont(QFont(tr("宋体"),12,QFont::Bold,true));
        charFormat.setFontUnderline(true);
        cursor.setCharFormat(charFormat);
        cursor.insertText("测试字体asdljk");
    } else
        {/* 恢复默认的字体格式*/}

}

void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;
    format.setCellSpacing(2);
    format.setCellPadding(10);
    cursor.insertTable(2,2,format);
}

void MainWindow::insertList()
{
    QTextListFormat format;
    format.setStyle(QTextListFormat::ListDecimal);
    ui->textEdit->textCursor().insertList(format);
}

void MainWindow::insertImage()
{
    QTextImageFormat format;
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("选择要插入的图片"),"./",tr("Image (*.png *.xpm *.jpg)"));
    format.setName(fileName);
    ui->textEdit->textCursor().insertImage(format);
}

void MainWindow::textFind()
{
    QDialog *dlg = new QDialog(this);
    lineEdit = new QLineEdit(dlg);
    QPushButton * btn = new QPushButton(dlg);
    btn->setText(tr("查找下一个"));
    connect(btn,QPushButton::clicked,this,findNext);
    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    dlg->setLayout(layout);
    dlg->show();
}

// 有问题！
void MainWindow::findNext()
{
    QString string = lineEdit->text();
    bool isfind = ui->textEdit->find(string,QTextDocument::FindBackward);
    if(isfind){
        qDebug() << tr("行号：%1 列号：%2").arg(ui->textEdit->textCursor().blockNumber() + 1)
                    .arg(ui->textEdit->textCursor().columnNumber() + 1);
    }

}







