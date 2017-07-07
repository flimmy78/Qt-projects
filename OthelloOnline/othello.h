#ifndef OTHELLO_H
#define OTHELLO_H

#include <QWidget>
#include "chessbroad.h"
#include <QMouseEvent>
#include <QTimer>
#include <QMovie>

namespace Ui {
    class Othello;
}

class Othello : public QWidget
{
    Q_OBJECT

public:
    explicit Othello(QWidget *parent = 0);
    ~Othello();
    void printNum();
protected:
    void paintEvent(QPaintEvent *);
private:
    int x,y;
    int a[8],b[8];
    int timeNum;
    int player,flag; //当前棋手
    Ui::Othello *ui;
    ChessBroad *chess;
    QTimer *timer,*timerFlag;
    QMovie *movie;

signals:
    void sendTime(int);
public slots:
    void reStart();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
    void myTime();            //显示倒计时
    void disChessNum(int,int,int);//显示当前玩家的棋子数
    void currentPlayer();  //闪烁当前玩家的头像
    void buttonBackEnable();
    void backHome(); //初始化各种参数
};

#endif // OTHELLO_H
