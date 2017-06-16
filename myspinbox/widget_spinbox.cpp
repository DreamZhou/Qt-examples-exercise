#include "widget_spinbox.h"
#include "ui_widget_spinbox.h"

Widget_spinbox::Widget_spinbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_spinbox)
{
    ui->setupUi(this);
}

Widget_spinbox::~Widget_spinbox()
{
    delete ui;
}
