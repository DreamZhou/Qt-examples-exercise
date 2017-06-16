#ifndef WIDGET_LINEEDIT_H
#define WIDGET_LINEEDIT_H

#include <QWidget>

namespace Ui {
class Widget_lineedit;
}

class Widget_lineedit : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_lineedit(QWidget *parent = 0);
    ~Widget_lineedit();

private:
    Ui::Widget_lineedit *ui;
};

#endif // WIDGET_LINEEDIT_H
