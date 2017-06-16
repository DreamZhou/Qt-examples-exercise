#ifndef MYLAYOUT_H
#define MYLAYOUT_H

#include <QDialog>

namespace Ui {
class Mylayout;
}

class Mylayout : public QDialog
{
    Q_OBJECT

public:
    explicit Mylayout(QWidget *parent = 0);
    ~Mylayout();

private slots:
    void on_pushButton_toggled(bool checked);

private:
    Ui::Mylayout *ui;
};

#endif // MYLAYOUT_H
