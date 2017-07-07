#include "judge.h"
#include <qmath.h>
#include <QDebug>

judge::judge()
{

}

int judge::chessJudge(int oldx,int oldy,int x,int y,int flag)
{

    switch(chess[oldx][oldy])
    {
    case 1://将
        if(flag == 1)
        {
            if(x==2 || x==5 || y==10 || y == 6)//越界
                break;
        }
        else if(flag == -1)
        {
            if(x==2 || x==5 || y==-1 || y == 3)
                break;
        }

            if((abs(oldx-x)==1) && (oldx==x) ||//下棋位置
               (abs(oldy-y)==1) && (oldy==y))
            {
                if(chess[x][y] <= 0) //空位或对方棋子才可以下
                {
                    chess[oldx][oldy] = 0;
                    chess[x][y] = 1;//下棋完成
                }
            }

        break;
    case 2://士
        if(flag == 1)
        {
            if(x==2 || x==5 || y==10 || y == 6)//越界
                break;
        }
        else if(flag == -1)
        {
            if(x==2 || x==5 || y==-1 || y == 3)
                break;
        }
        if((abs(oldx-x)==1) && (abs(oldy-y)==1))//下棋位置
        {
            if(chess[x][y] <= 0) //空位或对方棋子才可以下
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 2;//下棋完成
            }
        }
        break;
    case 3:
        if(flag == 1 && oldy <= 4)//象不能过河
            break;
        if(flag == -1 && oldy >=5)
            break;
        if(abs(oldx-x)==2 && (abs(oldy-y))==2)
        {
            if(flag == 1 && chess[x][y] <= 0)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 3;
            }
            if(flag == -1 && chess[x][y] >=0)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 3;
            }
        }
        break;
    case 4: //马
        if(abs(oldx-x)==1 && abs(oldy-y)==2 ||
           abs(oldx-x)==2 && abs(oldy-y)==1)
        {
            if(flag == 1 && chess[x][y] <=0)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 4;
            }
            if(flag == -1 && chess[x][y] >= 0)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 4;
            }
        }
        break;
    case 5://车
        if(oldx==x)
        {
            int min=(oldy>y)?y:oldy;
            int len = abs(oldy-y)-1;
            while(len--)
            {
                qDebug()<<chess[x][min]<<"[%d][%d]",x,min;
                if(chess[x][++min] != 0)//中间有子不能下
                    return -1;
            }
            chess[oldx][oldy] = 0;
            chess[x][y] = 5;
        }
        if(oldy==y)
        {
            int min=(oldx>x)?x:oldx;
            int len = abs(oldx-x)-1;
            while(len--)
            {
                if(chess[++min][y] != 0)
                    return -1;
            }
            chess[oldx][oldy] = 0;
            chess[x][y] = 5;
        }
        break;
    case 6:

        break;
    case 7:
        break;
    }
}
