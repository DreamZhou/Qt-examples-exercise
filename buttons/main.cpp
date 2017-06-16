#include "mywidget_btn.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget_Btn w;
    w.show();

    return a.exec();
}
