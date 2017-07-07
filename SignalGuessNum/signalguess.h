#ifndef SIGNALGUESS_H
#define SIGNALGUESS_H

#include <QWidget>
#include <QTimer>

namespace Ui {
    class SignalGuess;
}

class SignalGuess : public QWidget
{
    Q_OBJECT

public:
    explicit SignalGuess(QWidget *parent = 0);
    ~SignalGuess();

public slots:
    void myClick();
    void myClick1();
    void myClick2();
    void myClick3();
    void myClick4();
    void myClick5();
    void myClick6();
    void myClick7();
    void myClick8();
    void myClick9();
    void checkNum(int);
    void Pk(int tmp_num,int num);
    void mySlot();
    void myClock();
    int creatnumber();
signals:
    void SendNum(int);
    void SendQuit();
private:
    unsigned int answer;
    int num,count;
    int tmp_num;
    QTimer *timer;
    Ui::SignalGuess *ui;
};

#endif // SIGNALGUESS_H
