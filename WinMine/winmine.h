#ifndef WINMINE_H
#define WINMINE_H

#include <QWidget>
#include "board.h"
#include <QMovie>
#include <QTimer>

namespace Ui {
    class WinMine;
}

class WinMine : public QWidget
{
    Q_OBJECT

public:
    explicit WinMine(QWidget *parent = 0);
    ~WinMine();

signals:
    void sendTime(int);
private:
    Ui::WinMine *ui;
    board *chess;
    QMovie *movie;
    QTimer *timer;
    QMovie *movieWin;
    int num;
private slots:
    void on_pushButton_clicked();
    void slot_lose();
    void disTime();
    void disWin();
};

#endif // WINMINE_H
