#ifndef CHESSBROAD_H
#define CHESSBROAD_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

typedef struct eat_chess
{
        int x;            //棋子坐标
        int y;
        int EatChess_Num; //吃子个数
}EatChess;

class ChessBroad : public QWidget
{
    int chessWidth;   //宽
    int chessFrame;   //边框
    int x,y;
    int black,white;//当前黑白棋子个数
    int user; //pcAfter电脑下完之后
    QTimer *timer;
    Q_OBJECT
public:
    explicit ChessBroad(QWidget *parent = 0);
    int chess[8][8];
    int oldChess[64][8][8],k;//k是该组数的第1个下标
    bool pc;
    int flag;
    int pcAfter;
    void printBroad();
    void initBroad();
    void initOldChess();
    void printChessNum();
    void printNum();
    int whoWin();      //判断输赢的函数
    int judge(int,int,int); //下棋算法的函数
    void saveChess(); //保存棋盘的函数
    EatChess pc_ergod(); //电脑遍历找吃子最多的点
    EatChess* thing();    //削减对方行动力的算法
signals:
    void disNum(int,int,int);
    void backEnable();
public slots:
    int backChess();  //悔棋槽函数
    void init();  //返回主界面
    void pcPlay();    //电脑下棋
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // CHESSBROAD_H
