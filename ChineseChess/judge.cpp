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
    case 1://��
        if(flag == 1)
        {
            if(x==2 || x==5 || y==10 || y == 6)//Խ��
                break;
        }
        else if(flag == -1)
        {
            if(x==2 || x==5 || y==-1 || y == 3)
                break;
        }

            if((abs(oldx-x)==1) && (oldx==x) ||//����λ��
               (abs(oldy-y)==1) && (oldy==y))
            {
                if(chess[x][y] <= 0) //��λ��Է����Ӳſ�����
                {
                    chess[oldx][oldy] = 0;
                    chess[x][y] = 1;//�������
                }
            }

        break;
    case 2://ʿ
        if(flag == 1)
        {
            if(x==2 || x==5 || y==10 || y == 6)//Խ��
                break;
        }
        else if(flag == -1)
        {
            if(x==2 || x==5 || y==-1 || y == 3)
                break;
        }
        if((abs(oldx-x)==1) && (abs(oldy-y)==1))//����λ��
        {
            if(chess[x][y] <= 0) //��λ��Է����Ӳſ�����
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 2;//�������
            }
        }
        break;
    case 3:
        if(flag == 1 && oldy <= 4)//���ܹ���
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
    case 4: //��
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
    case 5://��
        if(oldx==x)
        {
            int min=(oldy>y)?y:oldy;
            int len = abs(oldy-y)-1;
            while(len--)
            {
                qDebug()<<chess[x][min]<<"[%d][%d]",x,min;
                if(chess[x][++min] != 0)//�м����Ӳ�����
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
