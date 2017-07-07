#ifndef BROAD_H
#define BROAD_H

#include <QWidget>
#include <QMouseEvent>

class broad : public QWidget
{

    Q_OBJECT
public:
    explicit broad(QWidget *parent = 0);
    int p_flag;
    int tmp_x,tmp_y;//存要走的棋子坐标
    int oldSignx,oldSigny,newSignx,newSigny;//棋子移动标志
    int chess[9][10];
    bool pitch;//棋子被选中的状态
    void initBroad();
    void flushSign();//刷新辅助标志
    int judge(int oldx,int oldy,int x,int y,int flag);
    int judge_ma(int oldx,int oldy,int x,int y);
    int che_pao(int oldx,int oldy,int x,int y,int fflag,int flag);
    int judge_zu(int oldx,int oldy,int x,int y,int flag);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

};

#endif // BROAD_H
