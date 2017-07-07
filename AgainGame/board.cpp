#include "board.h"
#include <QPainter>
#include <QPen>
#include <time.h>
#include <QDebug>
#include <QString>


int num[16] = {0};
static int dir[4][2] = {{1,0},{0,-1},{-1,0},{0,1}};

board::board(QWidget *parent) :
    QWidget(parent)
{
    flag = 0;//当点击开始按钮，才可以游戏
    win = 1; //win = 1 则显示最后一张图
    qsrand(time(0));
//    this->initNum();
    this->initBoard();
    this->makeBoard();
}

void board::paintEvent(QPaintEvent *)
{
    int i,j,k;
    QString str = "";
    QString path;
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    for(i=0 ; i<5 ; i++)  //画网格
      {
          painter.drawLine(0,this->height()/4*i,this->width(),this->height()/4*i);
          painter.drawLine(this->width()/4*i,0,this->width()/4*i,this->height());
      }

    for(i=0 ; i<4 ; i++)
    {
        for(j=0 ; j<4 ; j++)
        {
            str = "";
            path = ":/new/prefix1/";;
            for(k=1 ; k<16 ; k++)
            {
                if(chess[i][j] == k)
                {
                    str += QString::number(k);
                    str += ".jpg";
                    path += str;
                    painter.drawPixmap((i*(this->width()/4)+2),
                       (j*(this->height()/4)+2),this->width()/4-2,
                       this->height()/4-2,QPixmap(path));
                }
            }
        }
    }
    if(win == 1)
        painter.drawPixmap((3*(this->width()/4)+2),
           (3*(this->height()/4)+2),this->width()/4-2,
           this->height()/4-2,QPixmap(":/new/prefix1/16.jpg"));

}

void board::mousePressEvent(QMouseEvent *e)
{
    int x,y;
    if(flag == 0)
        return;
    if(e->button() == Qt::LeftButton)
    {
        x = e->x()/(this->width()/4);
        y = e->y()/(this->height()/4);
        picMove(x,y);
        if(judge() == 0)
            this->end();
     //   qDebug()<<"x="<<x<<"y="<<y;
    }
}

//生成1-15的数 *000并打乱顺序**（没用到！）
//用这种方法初始化时，玩到最后经常出现有最后2块拼不上！
void board::initNum()
{
    int i,j=15;

    for(i=15 ; i>0 ; i--)
    {
        do
        {
            num[i] = qrand()%15+1;
            for(j=i+1 ; j<16 ; j++)
            {
                if(num[i] == num[j])
                    break;
            }
        }while(num[i] == num[j]);
  //      qDebug()<<"***"<<i<<"="<<num[i]<<"***";
    }
}

void board::makeBoard()//初始化随机背景(这种方法解决了问题)
{
    int x = 3, y = 3,tmp_x,tmp_y;
    int num,count = 300;  //打乱次数 相当于移动了300次图片
    while(count--)
    {
        do
        {
            num = qrand()%4;
            tmp_x = x,tmp_y = y;
            switch(num)
            {
            case 0:
                tmp_x = tmp_x + dir[0][0];
                tmp_y = tmp_y + dir[0][1];
                if(tmp_x == -1 || tmp_x == 4
                   || tmp_y == -1 || tmp_y == 4)
                    continue;
                picMove(tmp_x,tmp_y);
                x = tmp_x,y = tmp_y;
                break;
            case 1:
                tmp_x = tmp_x + dir[1][0];
                tmp_y = tmp_y + dir[1][1];
                if(tmp_x == -1 || tmp_x == 4
                   || tmp_y == -1 || tmp_y == 4)
                    continue;
                picMove(tmp_x,tmp_y);
                x = tmp_x,y = tmp_y;
                break;
            case 2:
                tmp_x = tmp_x + dir[2][0];
                tmp_y = tmp_y + dir[2][1];
                if(tmp_x == -1 || tmp_x == 4
                   || tmp_y == -1 || tmp_y == 4)
                    continue;
                picMove(tmp_x,tmp_y);
                x = tmp_x,y = tmp_y;
                break;
            case 3:
                tmp_x = tmp_x + dir[3][0];
                tmp_y = tmp_y + dir[3][1];
                if(tmp_x == -1 || tmp_x == 4
                   || tmp_y == -1 || tmp_y == 4)
                    continue;
                picMove(tmp_x,tmp_y);
                x = tmp_x,y = tmp_y;
                break;
            }

        }while(tmp_x == 1 || tmp_x == 4
               || tmp_y == -1 || tmp_y == 4);
    }
    update();
}

void board::initBoard()//完整的背景
{
    int i,j,num = 1;
    for(i=0 ; i<4 ; i++)
    {
        for(j=0 ; j<4 ; j++)
        {
            chess[j][i] = num++;
        }
    }
 //   chess[3][3] = chess[2][3];
 //   chess[2][3] = 0;
    chess[3][3] = 0;
}

void board::picMove(int x, int y)//点击图片移动
{
    int tmp_x,tmp_y;
    int i;
    for(i=0 ; i<4 ; i++) //遍历上下左右四个方向
    {
        tmp_x = x;tmp_y = y;
        tmp_x = tmp_x + dir[i][0];  //图片移动
        tmp_y = tmp_y + dir[i][1];
        if(tmp_x == -1 || tmp_x == 4\
              || tmp_y == -1 || tmp_y == 4)
            continue;
        if(chess[tmp_x][tmp_y] == 0)
        {
            chess[tmp_x][tmp_y] = chess[x][y];
            chess[x][y] = 0;
        }
    }
    update();
}

int board::judge()//判断输赢
{
    int i,j,num=1;
    for(i=0 ; i<4 ; i++)
    {
        for(j=0 ; j<4 ; j++)
        {
            if(chess[j][i] == num++)
            {
                qDebug()<<"**"<<chess[j][i]<<"**";
                continue;
            }
            else
            {
                qDebug()<<"num="<<num;
                if(num == 17)
                    return 0;
                return -1;
            }
        }
    }
    return 0;
}
