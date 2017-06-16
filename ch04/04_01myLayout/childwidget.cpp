#include "childwidget.h"
#include "ui_childwidget.h"
#include <QGridLayout>
ChildWidget::ChildWidget(QWidget *parent) :
    QWidget(parent)
{
    pushButton_1 = new QPushButton(tr("pushButton_1"));
    pushButton_2 = new QPushButton(tr("pushButton_2"));
    pushButton_3 = new QPushButton(tr("pushButton_3"));
    pushButton_4 = new QPushButton(tr("pushButton_4"));

    QGridLayout *mainGridLayout = new QGridLayout;
    mainGridLayout->addWidget(pushButton_1,0,0,1,1);        //位置
    mainGridLayout->addWidget(pushButton_2,0,1,1,1);
    mainGridLayout->addWidget(pushButton_3,1,0,1,1);
    mainGridLayout->addWidget(pushButton_4,1,1,1,1);
    mainGridLayout->setSpacing(50);                        // 子部件间距离
    mainGridLayout->setContentsMargins(50,50,100,50);      // 四周空白大小
    setLayout(mainGridLayout);


}

ChildWidget::~ChildWidget()
{
    delete pushButton_1 ;
    delete pushButton_2 ;
    delete pushButton_3 ;
    delete pushButton_4 ;
}

