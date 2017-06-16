#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
private slots:
       void showWidgetm();
       void showFromWidget();
private:
    Ui::MyWidget *ui;
    QPushButton *showWidget;
    QPushButton *showFormLayoutWidget;
};

#endif // MYWIDGET_H
