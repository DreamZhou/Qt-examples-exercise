#include "widget_slider.h"
#include "ui_widget_slider.h"

Widget_slider::Widget_slider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_slider)
{
    ui->setupUi(this);
}

Widget_slider::~Widget_slider()
{
    delete ui;
}
