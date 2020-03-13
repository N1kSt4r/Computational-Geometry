#include "widget.h"
#include <QApplication>

#include <vector>
#include <random>
#include <utility>
#include <iostream>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
