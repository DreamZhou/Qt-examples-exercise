#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPixmap>
#include <QDebug>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked(bool checked)
{
    qDebug()<< tr("按钮是否被按下") << checked ;
}
