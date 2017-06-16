#ifndef WIDGET_SLIDER_H
#define WIDGET_SLIDER_H

#include <QWidget>

namespace Ui {
class Widget_slider;
}

class Widget_slider : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_slider(QWidget *parent = 0);
    ~Widget_slider();

private:
    Ui::Widget_slider *ui;
};

#endif // WIDGET_SLIDER_H
