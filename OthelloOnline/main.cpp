#include <QtGui/QApplication>
#include "othello.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Othello w;
    w.resize(800,600);
    w.show();

    return a.exec();
}
