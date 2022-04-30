#include "widget.h"
#include <QPaintEvent>
#include <QApplication>
#include <QMouseEvent>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
