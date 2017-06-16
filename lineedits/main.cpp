#include "widget_lineedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget_lineedit w;
    w.show();

    return a.exec();
}
