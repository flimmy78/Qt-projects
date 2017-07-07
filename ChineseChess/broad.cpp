#include "broad.h"
#include <QDebug>
#include <QPainter>
#include <QPen>


broad::broad(QWidget *parent) :
    QWidget(parent)
{
    p_flag = 1;
    pitch == false;
    tmp_x = -1;tmp_y = -1;
    oldSignx = -1,oldSigny = -1;
    newSignx = -1;newSigny = -1;
    this->initBroad();
}


void broad::paintEvent(QPaintEvent *)  //���̵Ļ�ͼ�¼�
{
    int i,j,w,h,k;
    QString str = "";
    QString path;
    QPainter painter(this);
    w = (this->width()/9)/2;
    h = (this->height()/10)/2;

    painter.drawPixmap((this->width()/9)/2,(this->height()/10)/2,
    this->width()-this->width()/9,this->height()-this->height()/10,
                       QPixmap(":/new/prefix1/chineseBoard.jpg"));

    for(i=0 ; i<9 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
 /*           if(chess[j][i] == 1)
                 painter.drawPixmap((i*(this->width()/9)),
                 (j*(this->height()/10)),this->width()/9,
                 this->height()/10,QPixmap("../image/china/1.png")); */

            str = "";
            path = ":/new/prefix1/";
            for(k=1 ; k<=7 ; k++) //�췽����
            {
                if(chess[i][j] == k)
                {
                    str += QString::number(k);
                    str += ".png";
                    path += str;
                    painter.drawPixmap((i*(this->width()/9)),
                        (j*(this->height()/10)),this->width()/9,
                                this->height()/10,QPixmap(path));
                }
            }
            for(k=-1 ; k>=-7 ; k--)//�ڷ�����
            {
                if(chess[i][j] == k)
                {
                    str += QString::number(k);
                    str += ".png";
                    path += str;
                    painter.drawPixmap((i*(this->width()/9)),
                        (j*(this->height()/10)),this->width()/9,
                                this->height()/10,QPixmap(path));
                }
            }
        }
    }
    flushSign();
}

void broad::flushSign()
{
    QPainter painter(this);
    QString path = ":/new/prefix1/bc.png";
    painter.drawPixmap((oldSignx*(this->width()/9)),
        (oldSigny*(this->height()/10)),this->width()/36,
                this->height()/40,QPixmap(path));
    painter.drawPixmap((newSignx*(this->width()/9)),
        (newSigny*(this->height()/10)),this->width()/36,
                this->height()/40,QPixmap(path));
}

void broad::mousePressEvent(QMouseEvent *e)
{
    int x,y;
    if(e->button() == Qt::LeftButton)
    {
        x = e->x()/(this->width()/9);
        y = e->y()/(this->height()/10);
        qDebug()<<"x="<<x<<"y="<<y;

        if(pitch == false)
        {
            if(p_flag==1 && chess[x][y]<0 || //�㵽����������Ч
               p_flag==-1 && chess[x][y]>0)
                return;
            if(chess[x][y] == 0)   //�㵽��λҲ��Ч
                return;
            qDebug()<<"first";
            oldSignx = x,oldSigny =y;
            newSignx = -1;newSigny = -1;
            tmp_x = x,tmp_y = y;   //����Ҫ�ߵ���������
            pitch = true;
            update();
        }
        else //��Ҫ�µ����� �����ƶ�
        {
            if(p_flag==1 && chess[x][y] > 0 ||
               p_flag==-1 && chess[x][y] < 0) //������Ҫ�µ�����
            {
                oldSignx = x,oldSigny =y;
                newSignx = -1;newSigny = -1;
                tmp_x = x;tmp_y = y;
                update();
                return;
            }
            qDebug()<<"flag="<<p_flag;
            if(judge(tmp_x,tmp_y,x,y,p_flag) == -1)
            {
                if(p_flag == -1)
                    chess[tmp_x][tmp_y] = -chess[tmp_x][tmp_y];
            }
            update();
        }
    }
}

/*7:�� 6:�� 5:�� 4:�� 3:�� 2:ʿ 1:�� */
void broad::initBroad()  //��ʼ������
{
    int i,j;
    for(i=0 ; i<9 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            chess[i][j] = 0;
            if(j == 0)
            {
                chess[0][j] = chess[8][j] = 5;
                chess[1][j] = chess[7][j] = 4;
                chess[2][j] = chess[6][j] = 3;
                chess[3][j] = chess[5][j] = 2;
                chess[4][j] = 1;
            }
            else if(j == 9)
            {
                chess[0][j] = chess[8][j] = -5;
                chess[1][j] = chess[7][j] = -4;
                chess[2][j] = chess[6][j] = -3;
                chess[3][j] = chess[5][j] = -2;
                chess[4][j] = -1;
            }
            else if(j == 3)
            {
                for(int i=0 ; i<9 ;i+=2)
                {
                    chess[i][j] = 7;
                }
            }
            else if(j == 6)
            {
                for(int i=0 ; i<9 ;i+=2)
                {
                    chess[i][j] = -7;
                }
            }
        }
    }
    chess[1][2] = chess[7][2] = 6;
    chess[1][7] = chess[7][7] = -6;
}

//�����㷨
int broad::judge(int oldx,int oldy,int x,int y,int flag)
{
    if(flag == -1)  //��Ϊ�����Ԫ��ֵΪ���� Ϊ�˽�ȥcase ת��������
        chess[oldx][oldy] = -chess[oldx][oldy];
    switch(chess[oldx][oldy])
    {
    case 1://��
        if(flag == 1)
        {
            if(x==2 || x==6 || y==3 || y == -1)//Խ��
                return -1;
        }
        else if(flag == -1)
        {
            if(x==2 || x==6 || y==6 || y == -1)
                return -1;
        }

            if((abs(oldx-x)==1) && (oldy==y) ||//����λ��
               (abs(oldy-y)==1) && (oldx==x))
            {
                if(flag == 1 && chess[x][y] <= 0) //��λ��Է����Ӳſ�����
                {
                    chess[oldx][oldy] = 0;
                    chess[x][y] = 1;//�������
                    oldSignx = oldx;oldSigny = oldy;//���������ƶ���λ��
                    newSignx = x;newSigny = y;
                    p_flag = -p_flag;
                    pitch = false;
                    break;
                }
                if(flag == -1 && chess[x][y] >= 0)
                {
                    chess[oldx][oldy] = 0;
                    chess[x][y] = -1;
                    oldSignx = oldx;oldSigny = oldy;
                    newSignx = x;newSigny = y;
                    p_flag = -p_flag;
                    pitch = false;
                    break;
                }
            }

        break;
    case 2://ʿ
        if(flag == 1)
        {
            if(x==2 || x==6 || y==3 || y == -1)//Խ��
                return -1;
        }
        else if(flag == -1)
        {
            if(x==2 || x==6 || y==6 || y == 10)
                return -1;
        }
        if((abs(oldx-x)==1) && (abs(oldy-y)==1))//����λ��
        {
            if(flag == 1 && chess[x][y] <= 0) //��λ��Է����Ӳſ�����
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 2;//�������
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                break;
            }
            if(flag == -1 && chess[x][y] >= 0) //��λ��Է����Ӳſ�����
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = -2;//�������
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                break;
            }
        }
        break;
    case 3:
        if(flag == 1 && y >= 5)//���ܹ���
            return -1;
        if(flag == -1 && y <= 4)
            return -1;
        if(abs(oldx-x)==2 && (abs(oldy-y))==2) //�ж��Ƿ�������
        {
            if(flag == 1 && chess[x][y] <= 0)
            {
                int midx = ((oldx>x)?x:oldx)+1;//��¼���Ӹ���м��ӷ�ֹ����
                int midy = ((oldy>y)?y:oldy)+1;
                if(chess[midx][midy] != 0) //��������м��Ӳ������� ��ֹ����
                {
                    return -1;
                    if(flag == -1)
                        chess[oldx][oldy] = -chess[oldx][oldy];
                }
                chess[oldx][oldy] = 0;
                chess[x][y] = 3;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                break;
            }
            if(flag == -1 && chess[x][y] >=0)
            {
                int midx = ((oldx>x)?x:oldx)+1;
                int midy = ((oldy>y)?y:oldy)+1;
                if(chess[midx][midy] != 0)
                {
                    return -1;
                }
                chess[oldx][oldy] = 0;
                chess[x][y] = -3;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                break;
            }
        }
        break;
    case 4://��
        if(abs(oldx-x)==1 && abs(oldy-y)==2 ||
           abs(oldx-x)==2 && abs(oldy-y)==1)
        {
            if(judge_ma(oldx,oldy,x,y) == -1)
                return -1;
            if(flag == 1 && chess[x][y] <=0) //����λ���ǿ�λ��Է�����
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 4;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                break;
            }
            if(flag == -1 && chess[x][y] >= 0)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = -4;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                break;
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
                if(chess[x][++min] != 0)//�м����Ӳ�����
                    return -1;
            }
            chess[oldx][oldy] = 0;
            if(flag == 1)
                chess[x][y] = 5;
            else if(flag == -1)
                chess[x][y] = -5;
            oldSignx = oldx;oldSigny = oldy;
            newSignx = x;newSigny = y;
            p_flag = -p_flag;
            pitch = false;
            break;
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
            if(flag == 1)
                chess[x][y] = 5;
            else if(flag == -1)
                chess[x][y] = -5;
            oldSignx = oldx;oldSigny = oldy;
            newSignx = x;newSigny = y;
            p_flag = -p_flag;
            pitch = false;
            break;
        }
        break;
    case 6://��

        if(che_pao(oldx,oldy,x,y,0,flag) == -1)//����-1˵����������
        {
            if(flag == -1)   //����һ��ʼ�Ѻ����ӽ�����ת�� ����Ҫת������
            chess[oldx][oldy] = -chess[oldx][oldy];
        }
        break;
    case 7://��
        if(judge_zu(oldx,oldy,x,y,flag) == -1)
        {
            if(flag == -1)
                chess[oldx][oldy] = -chess[oldx][oldy];
        }
        break;
    }
    qDebug()<<"!!!";
}

int broad::che_pao(int oldx,int oldy,int x,int y,int fflag,int flag)//�����ڵ��㷨
{
    int num = 0,eat = 0;
    if(oldx==x)
    {
        int min=(oldy>y)?y:oldy;
        int len = abs(oldy-y)-1;
        if(len == 0 && chess[x][y] != 0) //��ʼ�յ������1 �����Գ��� ���ڲ��ܳ��� ��ֹ�ڳ���λ��
            eat = 1;
        while(len--)
        {
            if(chess[x][++min] != 0)//ͳ���м��ж�����
                num++;
        }
        if(fflag == 1 && num == 0) //���µ����������м䲻������
        {
            chess[oldx][oldy] = 0;
            if(flag == 1)
                chess[x][y] = 5;
            else if(flag == -1)
                chess[x][y] = -5;
            oldSignx = oldx;oldSigny = oldy;
            newSignx = x;newSigny = y;
            p_flag = -p_flag;
            pitch = false;
            return 0;
        }
        if(fflag == 0) //fflag == 0 ����2���߷� num=0������ num=1����
        {
            if(num == 0 && eat == 0) //eat=0 ˵�����µĲ�����λ��������
            {
                if(flag == 1 && chess[x][y] < 0 || //������һ��ֱ�ӳ���
                   flag == -1 && chess[x][y] > 0)
                    return -1;
                chess[oldx][oldy] = 0;
                if(flag == 1)
                    chess[x][y] = 6;
                else if(flag == -1)
                    chess[x][y] = -6;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
            else if(num == 1)
            {
                if(flag == 1 && chess[x][y] >= 0 || //������� ����㵽�Է�����
                   flag == -1 && chess[x][y] <= 0)
                    return -1;
                chess[oldx][oldy] = 0;
                if(flag == 1)
                    chess[x][y] = 6;
                else if(flag == -1)
                    chess[x][y] = -6;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
        }
    }
    if(oldy==y)
    {
        int min=(oldx>x)?x:oldx;
        int len = abs(oldx-x)-1;
        if(len == 0 && chess[x][y] != 0)
            eat = 1;
        while(len--)
        {
            if(chess[++min][y] != 0)
                num++;
        }
        if(fflag == 1 && num == 0) //���µ����������м䲻������
        {
            chess[oldx][oldy] = 0;
            if(flag == 1)
                chess[x][y] = 5;
            else if(flag == -1)
                chess[x][y] = -5;
            oldSignx = oldx;oldSigny = oldy;
            newSignx = x;newSigny = y;
            p_flag = -p_flag;
            pitch = false;
            return 0;
        }
        if(fflag == 0) //��
        {
            if(num == 0 && eat == 0)
            {
                if(flag == 1 && chess[x][y] < 0 || //������һ��ֱ�ӳ���
                   flag == -1 && chess[x][y] > 0)
                    return -1;
                chess[oldx][oldy] = 0;
                if(flag == 1)
                    chess[x][y] = 6;
                else if(flag == -1)
                    chess[x][y] = -6;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
            else if(num == 1)
            {
                if(flag == 1 && chess[x][y] >= 0 || //������� ����㵽�Է�����
                   flag == -1 && chess[x][y] <= 0)
                    return -1;
                chess[oldx][oldy] = 0;
                if(flag == 1)
                    chess[x][y] = 6;
                else if(flag == -1)
                    chess[x][y] = -6;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
        }
    }
    return -1;
}

int broad::judge_zu(int oldx,int oldy,int x,int y,int flag)//����㷨
{
    if(flag == 1)
    {
        if(chess[x][y] > 0)  //�㵽�Լ�����
            return -1;
        if(oldy <= 4)//���Լ��Ľ� ����������
        {
            if((y-oldy) == 1 && oldx==x)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 7;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
        }
        else//С����ӿ���������
        {
            if((y-oldy) == 1 && oldx==x ||
               abs(oldx-x)==1 && oldy==y)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = 7;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
        }
    }
    else
    {
        if(chess[x][y] < 0)
            return -1;
        if(oldy<=6 && oldy>=5)
        {
            if((oldy-y)==1 && oldx==x)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = -7;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
        }
        else
        {
            if((oldy-y)==1 && oldx==x ||
               abs(oldx-x) == 1 && oldy==y)
            {
                chess[oldx][oldy] = 0;
                chess[x][y] = -7;
                oldSignx = oldx;oldSigny = oldy;
                newSignx = x;newSigny = y;
                p_flag = -p_flag;
                pitch = false;
                return 0;
            }
        }
    }
    return -1;
}


int broad::judge_ma(int oldx,int oldy,int x,int y) //��������㷨
{
    if((x-oldx) == 2)
    {
       if(chess[oldx+1][oldy] !=0)
           return -1;
    }
    if((oldx-x) == 2)
    {
        if(chess[oldx-1][oldy] != 0)
            return -1;
    }
    if((y-oldy) == 2)
    {
        if(chess[oldx][oldy+1] != 0)
            return -1;
    }
    if((oldy-y) == 2)
    {
        if(chess[oldx][oldy-1] != 0)
            return -1;
    }
    return 0;
}
