#ifndef MYWIDGET_BTN_H
#define MYWIDGET_BTN_H

#include <QWidget>

namespace Ui {
class MyWidget_Btn;
}

class MyWidget_Btn : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget_Btn(QWidget *parent = 0);
    ~MyWidget_Btn();

private slots:
    void on_pushButton_clicked(bool checked);

    void on_helpbtn_clicked();

private:
    Ui::MyWidget_Btn *ui;
};

#endif // MYWIDGET_BTN_H
