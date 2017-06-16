#include "formlayoutwidget.h"
#include "ui_formlayoutwidget.h"

FormLayoutWidget::FormLayoutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLayoutWidget)
{
    ui->setupUi(this);
}

FormLayoutWidget::~FormLayoutWidget()
{
    delete ui;
}
