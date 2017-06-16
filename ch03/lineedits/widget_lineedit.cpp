#include "widget_lineedit.h"
#include "ui_widget_lineedit.h"
#include <QCompleter>
#include <QDebug>
Widget_lineedit::Widget_lineedit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_lineedit)
{
    ui->setupUi(this);
    QValidator *validator = new QIntValidator(100,999,this);
    ui->lineEdit_3->setValidator(validator);

    QStringList wordlist;
    wordlist << "Qt" << "Qt Creator" << tr("你好");
    QCompleter * completer = new QCompleter(wordlist,this);
    completer->setCaseSensitivity(Qt::CaseInsensitive); // Qt::CaseInsensitive 大小写不敏感
    ui->lineEdit_4->setCompleter(completer);
}

Widget_lineedit::~Widget_lineedit()
{
    delete ui;
}
void Widget_lineedit::on_lineEdit_1_editingFinished()
{
    qDebug() << ui->lineEdit_1->text();
}
void Widget_lineedit::on_lineEdit_2_returnPressed()
{
    ui->lineEdit_3->setFocus();
    qDebug() << ui->lineEdit_2->text();
    qDebug() << ui->lineEdit_2->displayText();
}



void Widget_lineedit::on_lineEdit_3_editingFinished()
{
    qDebug() << ui->lineEdit_3->text();
}
