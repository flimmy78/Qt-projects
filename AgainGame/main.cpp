#include "againgame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AgainGame w;
    w.show();

    return a.exec();
}
