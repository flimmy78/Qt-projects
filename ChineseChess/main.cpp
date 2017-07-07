#include <QtGui/QApplication>
#include "chinesechess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChineseChess w;
    w.show();

    return a.exec();
}
