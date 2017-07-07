#include <QApplication>
#include "winmine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinMine w;
    w.show();

    return a.exec();
}
