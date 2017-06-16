#ifndef WIDGET_SPINBOX_H
#define WIDGET_SPINBOX_H

#include <QWidget>

namespace Ui {
class Widget_spinbox;
}

class Widget_spinbox : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_spinbox(QWidget *parent = 0);
    ~Widget_spinbox();

private:
    Ui::Widget_spinbox *ui;
};

#endif // WIDGET_SPINBOX_H
