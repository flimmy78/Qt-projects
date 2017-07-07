#include "chessbroad.h"
#include <windows.h>
#include "othello.h"
#include <stdio.h>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>

#define UN_FLAG(x) (2-(x-1)*x/2)  //切换对方棋子

EatChess eat = {-1,-1,-1};
static int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},\
{-1,0},{-1,1},{0,1},{1,1}};

ChessBroad::ChessBroad(QWidget *parent) :
    QWidget(parent)
{
    x = 0,y = 0,k = 1,user = 0;
    flag = 1;pc = true;
    pcAfter = 0;
    this->initOldChess();
    this->initBroad();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(pcPlay()));
}

void ChessBroad::paintEvent(QPaintEvent *)  //棋盘的绘图事件
{
    int i,j;
    QPainter painter(this);
    QPen pen(Qt::blue);
    pen.setWidth(4);
    painter.setPen(pen);

    for(i=0 ; i<9 ; i++)  //画网格
    {
        painter.drawLine(0,this->height()/8*i,this->width(),this->height()/8*i);
        painter.drawLine(this->width()/8*i,0,this->width()/8*i,this->height());
    }

    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
        {
            if(chess[i][j] == 1)
                 painter.drawPixmap((i*(this->width()/8)+2),
                 (j*(this->height()/8))+2,this->width()/8-2,
                       this->height()/8-2,QPixmap("../image/wc.png"));
            else if(chess[i][j] == 2)
                painter.drawPixmap((i*(this->width()/8)+2),
                (j*(this->height()/8)+2),this->width()/8-2,
                           this->height()/8-2,QPixmap("../image/bc.png"));
        }
    }
    printNum();
}

void ChessBroad::mousePressEvent(QMouseEvent *e)  //鼠标点击事件
{
    int startX,startY;
    switch(e->button())
        {
        case Qt::LeftButton:
            x = e->x();
            y = e->y();
            startX = x/(this->width()/8);   //画棋子的起始坐标
            startY = y/(this->height()/8);
            if (pcAfter == 0 &&
                judge(startX,startY,flag) != 0)//pcAfter=0你才能下棋
            {
                pcAfter = 1;//pcAfter = 1; 保证电脑下的时候你不能下
                emit this->backEnable();
                saveChess();
                if(pc == false)//如果=false是人人对战
                {
                    flag = UN_FLAG(flag); //要交换棋手
                    user = 1;  //棋手=1  保证flag=2的时候可以进行翻转，
                               //因为电脑遍历时 也是用flag=2.
                    pcAfter = 0;//因为是人人对战，所以pcAfter要置回0,否则直接下一次
                }
                update();
                timer->start(500);//电脑延时0.5秒下棋
            }
            update();
            break;
        default:
            break;
        }
}

void ChessBroad::initBroad()  //初始化棋盘
{
    int i,j;
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
        {
            chess[i][j] = 0;
        }
    }
    chess[3][4] = 1;
    chess[4][3] = 1;
    chess[3][3] = 2;
    chess[4][4] = 2;
    qDebug()<<"??"<<chess[9][8]<<"??";//数组不越界？？？？
}

void ChessBroad::printChessNum()//打印棋盘状态
{
    int i,j;
    qDebug()<<"打--印--棋--盘：";
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
        {
            printf("%d ",chess[i][j]);
        }
        printf("\n");
    }
}

void ChessBroad::printBroad() //画棋盘
{
//    chess[x][]
}
int ChessBroad::judge(int x, int y, int flag)   //下棋算法
{
    int i,num = 0,state = 0,f;
    int tmp_x = x,tmp_y = y;
    if(flag == 4)
    {
        f = flag;
        flag = 2;
    }
    if(chess[x][y] != 0)  //不是空位 退出
        return 0;

    for(i=0 ; i<8 ; i++)
    {
        num = 0;
    //	printf("x=%d,y=%d\n",tmp_x,tmp_y);
        tmp_x = x;
        tmp_y = y;
        tmp_x = tmp_x + dir[i][0];  //棋子移动
        tmp_y = tmp_y + dir[i][1];
        while(tmp_x >= 0 && tmp_x < 8\
                && tmp_y >= 0 && tmp_y < 8)    //是否在棋盘内
        {
            if(chess[tmp_x][tmp_y] == flag) //是否为对方棋子
            {
                num++;   //统计要翻转棋子的个数
                tmp_x = tmp_x + dir[i][0];
                tmp_y = tmp_y + dir[i][1];        
    //		printf("num=%d\n",num);
            }
            else
                break;
        }
        if(!(tmp_x >= 0 && tmp_x < 8\
           && tmp_y >= 0 && tmp_y < 8))
            continue;
        if(chess[tmp_x][tmp_y] == UN_FLAG(flag) && num != 0) //如果是自己棋子可以下子
        {
            if(flag == 1 || f == 4 || user == 1)
            {
                chess[x][y] = UN_FLAG(flag);
                qDebug()<<"x="<<x<<"y="<<y<<"flag="<<flag;
            }
            while(num > 0)//翻转棋子
            {
                tmp_x = tmp_x - dir[i][0];
                tmp_y = tmp_y - dir[i][1];
                if(flag == 1 || f == 4 || user == 1)  //如果(flag=2)是电脑遍历 先不能翻转
                {
                    chess[tmp_x][tmp_y] = UN_FLAG(flag);
          //          printf("i=%d--%d--%d--\n",i,tmp_x,tmp_y);
                }
                    num--;
                    state++;      //标志是否能下子。并且统计吃棋子的个数
            //      printf("**test1**\n");
                }
            }
        }
    return state;
}

void ChessBroad::printNum()
{
    int i,j;
    black = 0;
    white = 0;
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
        {
            if(chess[j][i] == 1)
                black++;
            if(chess[j][i] == 2)
                white++;
        }
    }
    this->disNum(white,black,flag);
}

int ChessBroad::whoWin()  //判断谁赢
{
    int i,j;
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
        {
            if(chess[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

void ChessBroad::saveChess() //保存棋盘函数
{
    int i,j;
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j< 8 ; j++)
            oldChess[k][i][j] = chess[i][j];
    }
    k++;
    qDebug()<<"k = "<<k;
}

int ChessBroad::backChess() //悔棋
{
    int i,j;
    if(k == 1)      //k=1已经退到初始棋盘 直接退出
        return 0;
    if(pc == false) //人人下->悔棋
        k -= 2;
    if(pc == true) //人机下->悔棋 把电脑的棋也悔掉
    {
        k -= 3;
        flag = UN_FLAG(flag);   //交换了两次 所以还是玩家下棋
    }
        qDebug()<<"k==="<<k;

        for(i=0 ; i<8 ; i++)
        {
            for(j=0 ; j<8 ; j++)
                chess[i][j] = oldChess[k][i][j];
        }
        k++;

        flag = UN_FLAG(flag);

}

void ChessBroad::initOldChess()//初始化oldChess[0][i][j]
{
    int i,j;
    k = 1;
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
            oldChess[0][i][j] = 0;
    }
    oldChess[0][3][4] = 1;
    oldChess[0][4][3] = 1;
    oldChess[0][3][3] = 2;
    oldChess[0][4][4] = 2;
}

EatChess ChessBroad::pc_ergod() //吃子最多的算法
{
        int i,j,num[20] = {0},t = 0;
  //      printf("可以下子的位置:\n");
        for(i=0 ;i<8 ;i++)
        {
                for(j=0 ;j<8 ;j++)
                {
                        if((num[t] = judge(j,i,2)) != 0)
                        {
                                if(eat.EatChess_Num < num[t])//存吃子最多的下棋位置
                                {
                                        eat.EatChess_Num = num[t];
                                        eat.x=j;
                                        eat.y=i;
                                }
                                t++;                 //能下棋的位置有多少
                       //         printf("%d,%d  ",j,i);
                        }
                }
        }
   //     printf("\n");
        return eat;
}

void ChessBroad::pcPlay()//电脑下棋
{
    if(pc == true)
    {
        EatChess p;  //吃棋子的一个结构体
        p = pc_ergod();//电脑遍历棋盘但不下棋
        judge(p.x,p.y,4); //电脑找到最好的位置，下棋
        saveChess();
        qDebug()<<"p.x="<<p.x<<"p.y"<<p.y<<"eat="<<p.EatChess_Num;
        eat.x = -1;
        eat.y = -1;
        eat.EatChess_Num = -1;
        qDebug()<<"ffllaagg"<<flag;
        pcAfter = 0;  //电脑下棋后，玩家才可以下棋
    }
    timer->stop();
}

void ChessBroad::init()
{
    this->initBroad();
    this->initOldChess();
    flag = 1;
    user = 0;
}
/* }
    }
    return eat;
}*/