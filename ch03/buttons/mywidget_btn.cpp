#include "mywidget_btn.h"
#include "ui_mywidget_btn.h"
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
MyWidget_Btn::MyWidget_Btn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget_Btn)
{
    ui->setupUi(this);
    ui->helpbtn->setText(tr("帮助(&H)"));
    ui->helpbtn->setIcon(QIcon("../buttons/images/help.png")); //构建目录要和源文件一个目录！
    ui->pushBtn_zoom->setText(tr("z&oom"));
    QMenu *menu = new QMenu(this);
    menu->addAction(QIcon("../buttons/images/zoom-in.png"),tr("放大"));
    ui->pushBtn_zoom->setMenu(menu);
}

MyWidget_Btn::~MyWidget_Btn()
{
    delete ui;
}

void MyWidget_Btn::on_pushButton_clicked(bool checked)
{
    if (checked)
        QMessageBox::information(this,tr("pushbtn1 was clicked"),tr("按钮被按下！")) ;

}

void MyWidget_Btn::on_helpbtn_clicked()
{
    qDebug() << tr("clicked!");
}
