#ifndef BOARD_H
#define BOARD_H

#include <QWidget>

class board : public QWidget
{
    int answer,dis;
    int flag;
    int sign[10][10];
    int chess[10][10];


    Q_OBJECT
public:
    explicit board(QWidget *parent = 0);
    void initBroad();//��ʼ������
    void initSign();
    int judge(int x,int y);//�㷨
    int search(int x,int y);
    void initButton(); //��ʼ����ť
    int win();
    bool firstClick; //Ҫ�����ʼ������Ϸ ��־

signals:
    void sig_lose();
    void gameDone();
public slots:
    void display();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);

};

#endif // BOARD_H
