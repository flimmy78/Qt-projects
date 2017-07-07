#include "chessbroad.h"
#include <windows.h>
#include "othello.h"
#include <stdio.h>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>

#define UN_FLAG(x) (2-(x-1)*x/2)  //�л��Է�����

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

void ChessBroad::paintEvent(QPaintEvent *)  //���̵Ļ�ͼ�¼�
{
    int i,j;
    QPainter painter(this);
    QPen pen(Qt::blue);
    pen.setWidth(4);
    painter.setPen(pen);

    for(i=0 ; i<9 ; i++)  //������
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

void ChessBroad::mousePressEvent(QMouseEvent *e)  //������¼�
{
    int startX,startY;
    switch(e->button())
        {
        case Qt::LeftButton:
            x = e->x();
            y = e->y();
            startX = x/(this->width()/8);   //�����ӵ���ʼ����
            startY = y/(this->height()/8);
            if (pcAfter == 0 &&
                judge(startX,startY,flag) != 0)//pcAfter=0���������
            {
                pcAfter = 1;//pcAfter = 1; ��֤�����µ�ʱ���㲻����
                emit this->backEnable();
                saveChess();
                if(pc == false)//���=false�����˶�ս
                {
                    flag = UN_FLAG(flag); //Ҫ��������
                    user = 1;  //����=1  ��֤flag=2��ʱ����Խ��з�ת��
                               //��Ϊ���Ա���ʱ Ҳ����flag=2.
                    pcAfter = 0;//��Ϊ�����˶�ս������pcAfterҪ�û�0,����ֱ����һ��
                }
                update();
                timer->start(500);//������ʱ0.5������
            }
            update();
            break;
        default:
            break;
        }
}

void ChessBroad::initBroad()  //��ʼ������
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
    qDebug()<<"??"<<chess[9][8]<<"??";//���鲻Խ�磿������
}

void ChessBroad::printChessNum()//��ӡ����״̬
{
    int i,j;
    qDebug()<<"��--ӡ--��--�̣�";
    for(i=0 ; i<8 ; i++)
    {
        for(j=0 ; j<8 ; j++)
        {
            printf("%d ",chess[i][j]);
        }
        printf("\n");
    }
}

void ChessBroad::printBroad() //������
{
//    chess[x][]
}
int ChessBroad::judge(int x, int y, int flag)   //�����㷨
{
    int i,num = 0,state = 0,f;
    int tmp_x = x,tmp_y = y;
    if(flag == 4)
    {
        f = flag;
        flag = 2;
    }
    if(chess[x][y] != 0)  //���ǿ�λ �˳�
        return 0;

    for(i=0 ; i<8 ; i++)
    {
        num = 0;
    //	printf("x=%d,y=%d\n",tmp_x,tmp_y);
        tmp_x = x;
        tmp_y = y;
        tmp_x = tmp_x + dir[i][0];  //�����ƶ�
        tmp_y = tmp_y + dir[i][1];
        while(tmp_x >= 0 && tmp_x < 8\
                && tmp_y >= 0 && tmp_y < 8)    //�Ƿ���������
        {
            if(chess[tmp_x][tmp_y] == flag) //�Ƿ�Ϊ�Է�����
            {
                num++;   //ͳ��Ҫ��ת���ӵĸ���
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
        if(chess[tmp_x][tmp_y] == UN_FLAG(flag) && num != 0) //������Լ����ӿ�������
        {
            if(flag == 1 || f == 4 || user == 1)
            {
                chess[x][y] = UN_FLAG(flag);
                qDebug()<<"x="<<x<<"y="<<y<<"flag="<<flag;
            }
            while(num > 0)//��ת����
            {
                tmp_x = tmp_x - dir[i][0];
                tmp_y = tmp_y - dir[i][1];
                if(flag == 1 || f == 4 || user == 1)  //���(flag=2)�ǵ��Ա��� �Ȳ��ܷ�ת
                {
                    chess[tmp_x][tmp_y] = UN_FLAG(flag);
          //          printf("i=%d--%d--%d--\n",i,tmp_x,tmp_y);
                }
                    num--;
                    state++;      //��־�Ƿ������ӡ�����ͳ�Ƴ����ӵĸ���
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

int ChessBroad::whoWin()  //�ж�˭Ӯ
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

void ChessBroad::saveChess() //�������̺���
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

int ChessBroad::backChess() //����
{
    int i,j;
    if(k == 1)      //k=1�Ѿ��˵���ʼ���� ֱ���˳�
        return 0;
    if(pc == false) //������->����
        k -= 2;
    if(pc == true) //�˻���->���� �ѵ��Ե���Ҳ�ڵ�
    {
        k -= 3;
        flag = UN_FLAG(flag);   //���������� ���Ի����������
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

void ChessBroad::initOldChess()//��ʼ��oldChess[0][i][j]
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

EatChess ChessBroad::pc_ergod() //���������㷨
{
        int i,j,num[20] = {0},t = 0;
  //      printf("�������ӵ�λ��:\n");
        for(i=0 ;i<8 ;i++)
        {
                for(j=0 ;j<8 ;j++)
                {
                        if((num[t] = judge(j,i,2)) != 0)
                        {
                                if(eat.EatChess_Num < num[t])//�������������λ��
                                {
                                        eat.EatChess_Num = num[t];
                                        eat.x=j;
                                        eat.y=i;
                                }
                                t++;                 //�������λ���ж���
                       //         printf("%d,%d  ",j,i);
                        }
                }
        }
   //     printf("\n");
        return eat;
}

void ChessBroad::pcPlay()//��������
{
    if(pc == true)
    {
        EatChess p;  //�����ӵ�һ���ṹ��
        p = pc_ergod();//���Ա������̵�������
        judge(p.x,p.y,4); //�����ҵ���õ�λ�ã�����
        saveChess();
        qDebug()<<"p.x="<<p.x<<"p.y"<<p.y<<"eat="<<p.EatChess_Num;
        eat.x = -1;
        eat.y = -1;
        eat.EatChess_Num = -1;
        qDebug()<<"ffllaagg"<<flag;
        pcAfter = 0;  //�����������Ҳſ�������
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