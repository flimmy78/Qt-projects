#include <QtGui/QApplication>
#include "doudizhu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    douDiZhu w;
    w.show();

    return a.exec();
}
