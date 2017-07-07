#include <QtGui/QApplication>
#include "signalguess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignalGuess w;
    w.show();

    return a.exec();
}
