#include "micromouseserver.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    microMouseServer w;
    w.show();

    return a.exec();
}
