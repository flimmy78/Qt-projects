#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class board : public QWidget
{
    int chess[4][4];

    Q_OBJECT
public:
    explicit board(QWidget *parent = 0);
    void initNum();//生成随机数
    void initBoard();//初始化棋盘
    void picMove(int x,int y);//图片移动
    int judge();//判断输赢
    int flag; //点击开始按钮的标志
    int win;
    void makeBoard();
signals:
    void end();
public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

};

#endif // BOARD_H
