#include "widget_spinbox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget_spinbox w;
    w.show();

    return a.exec();
}
