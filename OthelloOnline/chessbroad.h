#ifndef CHESSBROAD_H
#define CHESSBROAD_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

typedef struct eat_chess
{
        int x;            //��������
        int y;
        int EatChess_Num; //���Ӹ���
}EatChess;

class ChessBroad : public QWidget
{
    int chessWidth;   //��
    int chessFrame;   //�߿�
    int x,y;
    int black,white;//��ǰ�ڰ����Ӹ���
    int user; //pcAfter��������֮��
    QTimer *timer;
    Q_OBJECT
public:
    explicit ChessBroad(QWidget *parent = 0);
    int chess[8][8];
    int oldChess[64][8][8],k;//k�Ǹ������ĵ�1���±�
    bool pc;
    int flag;
    int pcAfter;
    void printBroad();
    void initBroad();
    void initOldChess();
    void printChessNum();
    void printNum();
    int whoWin();      //�ж���Ӯ�ĺ���
    int judge(int,int,int); //�����㷨�ĺ���
    void saveChess(); //�������̵ĺ���
    EatChess pc_ergod(); //���Ա����ҳ������ĵ�
    EatChess* thing();    //�����Է��ж������㷨
signals:
    void disNum(int,int,int);
    void backEnable();
public slots:
    int backChess();  //����ۺ���
    void init();  //����������
    void pcPlay();    //��������
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // CHESSBROAD_H
