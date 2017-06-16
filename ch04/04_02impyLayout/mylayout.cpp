#include "mylayout.h"
#include "ui_mylayout.h"

Mylayout::Mylayout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mylayout)
{
    ui->setupUi(this);
    ui->textEdit->hide(); // 默认隐藏 配合pushButton 显示
}

Mylayout::~Mylayout()
{
    delete ui;
}

void Mylayout::on_pushButton_toggled(bool checked)
{
    ui->textEdit->setVisible(checked);
    if(checked) ui->pushButton->setText(tr("隐藏可扩展窗口"));
    else ui->pushButton->setText(tr("显示可扩展窗口"));
}
