#include "mainScreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainScreen w;
    w.show();
    return a.exec();
}
