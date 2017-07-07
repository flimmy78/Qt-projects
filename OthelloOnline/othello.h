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
    int player,flag; //��ǰ����
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
    void myTime();            //��ʾ����ʱ
    void disChessNum(int,int,int);//��ʾ��ǰ��ҵ�������
    void currentPlayer();  //��˸��ǰ��ҵ�ͷ��
    void buttonBackEnable();
    void backHome(); //��ʼ�����ֲ���
};

#endif // OTHELLO_H
