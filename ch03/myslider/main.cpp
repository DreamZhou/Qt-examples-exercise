#include "widget_slider.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget_slider w;
    w.show();

    return a.exec();
}
