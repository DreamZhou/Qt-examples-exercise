#include "widget_spinbox.h"
#include "ui_widget_spinbox.h"
#include <QDateTime>
Widget_spinbox::Widget_spinbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_spinbox)
{
    ui->setupUi(this);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEdit_2->setDisplayFormat("yy/MM/dd");
//    y year  M month  d day ddd week H hour
}

Widget_spinbox::~Widget_spinbox()
{
    delete ui;
}
