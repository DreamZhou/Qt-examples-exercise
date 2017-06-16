#include "widget_lineedit.h"
#include "ui_widget_lineedit.h"

Widget_lineedit::Widget_lineedit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_lineedit)
{
    ui->setupUi(this);
}

Widget_lineedit::~Widget_lineedit()
{
    delete ui;
}
