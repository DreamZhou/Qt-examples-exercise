#ifndef FORMLAYOUTWIDGET_H
#define FORMLAYOUTWIDGET_H

#include <QWidget>

namespace Ui {
class FormLayoutWidget;
}

class FormLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FormLayoutWidget(QWidget *parent = 0);
    ~FormLayoutWidget();

private:
    Ui::FormLayoutWidget *ui;
};

#endif // FORMLAYOUTWIDGET_H
