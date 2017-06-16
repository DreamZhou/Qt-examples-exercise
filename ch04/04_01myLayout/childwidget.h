#ifndef CHILDWIDGET_H
#define CHILDWIDGET_H
#include <QPushButton>
#include <QWidget>

// 不用不用设计师，手写界面。 没实现功能。
namespace Ui{
class ChildWidget;
}

class ChildWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChildWidget(QWidget *parent = 0);
    ~ChildWidget();

public slots:

private:
    QPushButton *pushButton_1 ;
    QPushButton *pushButton_2 ;
    QPushButton *pushButton_3 ;
    QPushButton *pushButton_4 ;
};

#endif // CHILDWIDGET_H
