#include "mywidget.h"
#include "ui_mywidget.h"
#include <QHBoxLayout>
#include "childwidget.h"
#include "formlayoutwidget.h"
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addWidget(ui->fontComboBox);
    mainlayout->addWidget(ui->textEdit);
    mainlayout->setSpacing(50);
    mainlayout->setContentsMargins(0,0,50,100);
    setLayout(mainlayout);

    showWidget = new QPushButton(tr("Show Child Widget")); // 如果要放到layout中可以不设置this
    showWidget->setObjectName(QStringLiteral("showWidget"));
    mainlayout->addWidget(showWidget);
    connect(showWidget,QPushButton::clicked,this,showWidgetm);

    showFormLayoutWidget = new QPushButton(tr("Show Form Layout"));
    mainlayout->addWidget(showFormLayoutWidget);
    connect(showFormLayoutWidget,QPushButton::clicked,this,showFromWidget);
}

MyWidget::~MyWidget()
{
    delete ui;
    delete showWidget;
}

void MyWidget::showWidgetm()
{
    ChildWidget * gridlayoutwidget = new ChildWidget();
    gridlayoutwidget->show();
}

void MyWidget::showFromWidget()
{
    FormLayoutWidget *formLayoutWidget = new FormLayoutWidget();
    formLayoutWidget->show();
}
