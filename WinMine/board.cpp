#include "board.h"
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <time.h>
#include <QPushButton>

static int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},\
{-1,0},{-1,1},{0,1},{1,1}};

typedef struct piont
{
    int x;
    int y;
}POINT;

board::board(QWidget *parent) :
    QWidget(parent)
{
    dis = 1;
    flag = 0;
    firstClick = false;
    qsrand(time(0));
    this->initBroad();
    this->initSign();
 //   this->initButton();
}


void board::paintEvent(QPaintEvent *)  //棋盘的绘图事件
{
    int i,j,w,h;
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);

    for(i=0 ; i<11 ; i++)  //画网格
    {
        painter.drawLine(0,i*this->height()/10,this->width(),i*this->height()/10);
        painter.drawLine(i*this->width()/10,0,i*this->width()/10,this->height());
    }
    w = this->width()/10;
    h = this->height()/10;

    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            if(chess[i][j] == -2 || chess[i][j] == -1)
                painter.drawPixmap((i*((this->width()+4)/10)+2),
                (j*((this->height()+4)/10))+2,this->width()/10-2,
                      this->height()/10-2,QPixmap(":/new/prefix1/button_click.bmp"));
            else if(chess[i][j] == 0)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap("../img/00.bmp"));
            else if(chess[i][j] == 1)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap(":/new/prefix1/1.bmp"));
            else if(chess[i][j] == 2)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap(":/new/prefix1/2.bmp"));

            else if(chess[i][j] == 3)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap(":/new/prefix1/3.bmp"));

            else if(chess[i][j] == 4)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap(":/new/prefix1/4.bmp"));

            else if(chess[i][j] == 5)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap(":/new/prefix1/5.bmp"));

            else if(chess[i][j] == 6)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap(":/new/prefix1/6.bmp"));
            if(sign[i][j] == 1)
                painter.drawPixmap((i*w+2),(j*h+2),
                w-2,h-2,QPixmap(":/new/prefix1/qq.gif"));
            if(chess[i][j] == -1 && dis == -1) //dis=-1 显示地雷
                 painter.drawPixmap((i*(this->width()/10)+2),
                 (j*(this->height()/10))+2,this->width()/10-2,
                       this->height()/10-2,QPixmap(":/new/prefix1/bc.png"));
        }
    }
}

void board::mousePressEvent(QMouseEvent *e)  //鼠标点击事件
{
    int x,y,num;
    if(firstClick == 0)
        return;
    switch(e->button())
        {
        case Qt::LeftButton:
            x = e->x()/(this->width()/10);   //画棋子的起始坐标
            y = e->y()/(this->height()/10);
            qDebug()<<"x="<<x<<"y="<<y;
            if(sign[x][y] == 1) //点到红旗 无效
                break;
            if((num = judge(x,y)) != -1)
            {
                if(num != 0)
                    update();
                if(num == 0)
                    search(x,y);
                if(win() == 0)
                    qDebug()<<"you win!";
            }
            else
                emit this->sig_lose();
            break;
        case Qt::RightButton: //右键画红旗
            x = e->x()/(this->width()/10);
            y = e->y()/(this->height()/10);
            if(chess[x][y] == -1 || chess[x][y] == -2)
            {
                if(sign[x][y] == 0)
                {
                    sign[x][y] = 1;
                }
                else if(sign[x][y] == 1)
                    sign[x][y] = 0;
            }
            update();
            break;
        default:
            break;
        }
}


void board::initBroad()  //初始化棋盘 生成10个雷
{
    int i,j,num[12];
    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            chess[i][j] = -2; //空位 = -2
        }
    }
    for(i=0 ; i<12 ; i++)
    {
        num[i] = qrand()%100;
        chess[num[i]/10][num[i]%10] = -1;
        qDebug()<<"***"<<num[i]<<"***";
    }
}
void board::initSign()
{
    int i,j;
    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ;j <10 ; j++)
        {
            sign[i][j] = 0;
        }
    }
    qDebug()<<"done";
}

int board::judge(int x,int y)
{
    int tmp_x = x,tmp_y = y;
    int num = 0,i;
    if(chess[x][y] == -1)
      return -1;       //点到雷返回-1
    for(i=0 ; i<8 ; i++)
    {
        tmp_x = x,tmp_y = y;
        tmp_x = tmp_x + dir[i][0];  //棋子移动
        tmp_y = tmp_y + dir[i][1];
        if(tmp_x == -1 || tmp_x == 10  //如果越界 进行下一次循环
           || tmp_y == -1 || tmp_y == 10)
            continue;
        if(chess[tmp_x][tmp_y] == -1)
            num++;
    }
 //   qDebug()<<"num="<<num;
    chess[x][y] = num;
    return num;
}

void board::display()
{
    dis = -dis;
    update();
}

int board::search(int x,int y) //扩大区域
{
    int tmp_x = x,tmp_y = y;
    int num,count = 1000;  //打乱次数 相当于移动了300次图片
    while(count--)
    {
        do
        {
            num = qrand()%8;
            tmp_x = x,tmp_y = y;

            tmp_x = tmp_x + dir[num][0];
            tmp_y = tmp_y + dir[num][1];
            if(tmp_x == -1 || tmp_x == 10
               || tmp_y == -1 || tmp_y == 10)
                continue;
            if(judge(tmp_x,tmp_y) == 0)
                x = tmp_x,y = tmp_y;
        }while(tmp_x == 1 || tmp_x == 4
               || tmp_y == -1 || tmp_y == 4);
    }
    update();
}

void board::initButton()
{
    int i,j,k = 0;
    QPushButton *button[100];
    for(i=0 ; i<100 ; i++)
    {
        button[i] = new QPushButton(this);
        button[i]->resize(23,23);
    }
    qDebug()<<"width="<<this->width();
    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            button[k++]->move(i*25,j*25);
        }
    }
}

int board::win()
{
    int i,j;
    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            if(chess[i][j] == -2)
                return -1;
        }
    }
     emit this->gameDone();
    return 0;

}
