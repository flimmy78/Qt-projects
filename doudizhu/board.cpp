#include "board.h"
#include <QDebug>
#include <time.h>
#include <QPainter>
#include <QTimer>
#include <QLabel>


board::board(QWidget *parent) :
    QWidget(parent)
{
    qsrand(time(0));
    tt = 0;
    timer = new QTimer(this);
    passButton1 = new QPushButton(this);
    passButton2 = new QPushButton(this);
    flag = 1;back = false;
    this->initButton();
    this->initPork();
    this->px();
    connect(this->entry,SIGNAL(clicked()),this,SLOT(exec_judge()));
    connect(this,SIGNAL(sendTimer()),this,SLOT(timerStart()));
    connect(timer,SIGNAL(timeout()),this,SLOT(pc()));
}

void board::timerStart()
{
    timer->start(1000);
}
void board::pc()
{
    label1 = new QLabel(this);
//    label2 = new QLabel(this);

    passButton1->move(180,200);
    passButton1->setText("PASS!");
    passButton1->show();

    passButton2->move(530,200);
    passButton2->setText("PASS!");
    passButton2->show();
    if(tt++ == 2)
    {
        passButton1->hide();
        passButton2->hide();
        timer->stop();
        tt = 0;
    }
}

void board::paintEvent(QPaintEvent *)
{
    if(back == false)
        return;
    int i,j,z=0;
    QString path = "";
    QString str = "";
    QPainter painter(this);
    for(i=0 ; i<13 ; i++)
        painter.drawPixmap(50,90+i*15,100,140,QPixmap(":new/bei1.png"));
    for(i=0 ; i<13 ; i++)
        painter.drawPixmap(this->width()-150,90+i*15,\
                           100,140,QPixmap(":new/bei1.png"));

    for(i=0 ; i<3 ; i++) //三张底牌
    {   path = ":new/";
        str = QString::number(num[52+i]);
        str += ".png";
        path += str;
        painter.drawPixmap((this->width()/3+20)+80*i,20,62,90,QPixmap(path));
    }
    for(i=0 ; i<17 ; i++)//显示我的13张牌
    {
        for(j=1 ; j<55 ; j++)
        {
            str = "";
            path = ":new/";
            if(j == player.p[i])
            {
                str += QString::number(j);
                str += ".png";
                path += str;

                if(player.state[i] == 1)//未选中
                    painter.drawPixmap(this->width()/4+i*22,\
                                   this->height()-125,80,120,QPixmap(path));
                else if(player.state[i] == -1)//选中
                    painter.drawPixmap(this->width()/4+i*22,\
                                   this->height()-140,80,120,QPixmap(path));
                else if(player.state[i] == 0 &&
                        player.p[i] != 0)//出牌
                {
                    painter.drawPixmap(this->width()/2+(z++)*22-70,\
                                   this->height()/2-30,80,120,QPixmap(path));
                    player.p[i] = 0; //=1
                }
            }
        }
    }
}

void board::mousePressEvent(QMouseEvent *e)
{
    int x,y;
    if(e->button() == Qt::LeftButton)
    {
        x = e->x()-195;
        y = e->y()-425;
        if(x < 0 || x > 378 || y <0 || y > 70)
            return;
        x = x/22;
        if(player.state[x] == 1)  //改变牌的状态
            player.state[x] = -1;
        else
            player.state[x] = 1;
        qDebug()<<"x="<<x<<player.state[x];
        update();
    }
}

void board::initButton()
{
    int buttonX = this->parentWidget()->width()/2;
    int buttonY = this->parentWidget()->height()/5*3;
    qDebug()<<"width="<<this->width()<<"height="<<this->height();
    pass = new QPushButton(this);
    entry = new QPushButton(this);

    pass->setText("pass");
    entry->setText("entry");
    pass->resize(50,30);
    pass->move(buttonX,buttonY);
    entry->resize(50,30);
    entry->move(buttonX-this->width(),buttonY);
}

int board::judge()//判断出牌是否符合规则
{
    int i,j = 0,num[17],sum = 0,p[17];//p[17]储存要出的牌
    for(i=0 ; i<17 ; i++)
    {
        if(-1 == player.state[i])
        {
            p[j] = i; //储存被点中的牌
            sum++;
            num[j++] = player.p[i]; //存放选中的牌
            qDebug()<<j<<player.p[i];
        }
    }
    if(oneJudge(num,j) == 0)
    {
        player.state[p[0]] = 0;
        return 1;
    }
    if(twoJudge(num,j) == 0)
    {
        for(i=0 ; i<j ; i++)
            player.state[p[i]] = 0;
        qDebug()<<"two pairs";
        return 2;
    }
    if(threeJudge(num,j) == 0)
    {
        for(i=0 ; i<j ; i++)
            player.state[p[i]] = 0;
        qDebug()<<"three pairs";
        return 3;
    }
    if(lianJudge(num,j) == 0)
    {
        for(i=0 ; i<j ; i++)
            player.state[p[i]] = 0;
        qDebug()<<"lian xian";
        return 6;
    }
    if(fourJudge(num,j) == 0)
    {
        for(i=0 ; i<j ; i++)
            player.state[p[i]] = 0;
        qDebug()<<"zha dan!";
        return 0;
    }
    if(san_oneJudge(num,j) == 0)
    {
        for(i=0 ; i<j ; i++)
            player.state[p[i]] = 0;
        qDebug()<<"3 - 1";
        return 4;
    }
    if(san_twoJudge(num,j) == 0)
    {
        for(i=0 ; i<j ; i++)
            player.state[p[i]] = 0;
        qDebug()<<"3 - 2";
        return 5;
    }
    if(lian_duiJudge(num,j) == 0)
    {
        for(i=0 ; i<j ; i++)
            player.state[p[i]] = 0;
        qDebug()<<"3 - 2";
        return 7;
    }
    return -1;
}

int board::exec_judge()
{
    int type;
    if((type = judge()) == -1)
        return -1;
    pcJudge(type);
    qDebug()<<"pc";
    update();
}

int board::oneJudge(int num[],int j)//单张
{
    if(j != 1)
        return -1;
    else
        return 0;
}

int board::twoJudge(int num[],int j)//判断对子
{
    if(j != 2)
        return -1;
    if((num[0]-1)/4 != (num[1]-1)/4)
        return -1;
    else
        return 0;
}

int board::threeJudge(int num[],int j)//判断三张
{
    if(j != 3)
        return -1;
    if((num[0]-1)/4 == (num[1]-1)/4 &&
       (num[1]-1)/4 == (num[2]-1)/4)
        return 0;
}

int board::fourJudge(int num[],int j)//炸弹
{
    if(j != 4)
        return -1;
    if((num[0]-1)/4 == (num[1]-1)/4 &&
       (num[1]-1)/4 == (num[2]-1)/4 &&
       (num[2]-1)/4 == (num[3]-1)/4)
        return 0;
}

int board::lianJudge(int num[],int j)//连线
{
    if(j < 5)
        return -1;
    for(int i=j-1 ; i>0 ; i--)
    {
        qDebug()<<"5555"<<num[i];
        if(((num[i]-1)/4)-1 == (num[i-1]-1)/4)
            continue;
        else
            return -1;
    }
    return 0;
}

int board::san_oneJudge(int num[],int j)//三带1
{
    int sum;
    if(j != 4)
        return -1;
    for(int i=0 ; i<4 ; i++)
    {
        sum = 0;
        for(int k=0 ; k<4 ; k++)
        {
            if((num[i]-1)/4 == (num[k]-1)/4)
                sum++;
        }
        if(sum == 3)
            return 0;
    }
    return -1;
}

int board::san_twoJudge(int num[],int j)//三带2
{
    int sum,doubleSum,san;
    if(j != 5)
        return -1;
    for(int i=0 ; i<5 ; i++)
    {
        sum = 0;
        doubleSum = 0;
        for(int k=0 ; k<5 ; k++)
        {
            if((num[i]-1)/4 == (num[k]-1)/4)
                sum++;
        }
        if(sum == 3) //如果有3张一样的在找那2张是否一样
        {
            san = (num[i]-1)/4;//储存三张一样的牌
            qDebug()<<"san="<<san;
            for(int i=0 ; i<5 ; i++)//找2张一样的
            {
                doubleSum = 0;
                for(int k=0 ; k<5 ; k++)
                {
                    if((num[i]-1)/4 == (num[k]-1)/4)
                        doubleSum++;
                }
                if(san != ((num[i]-1)/4) && doubleSum == 2)//找到
                {
                    qDebug()<<"er="<<(num[i]-1)/4;
                    return 0;
                }
            }
        }
    }
    return -1;
}

int board::lian_duiJudge(int num[],int j)//连对
{
    if(j < 6 || (j%2) == 1)
        return -1;
    for(int i=0 ; i<j ; i+=2)
    {
        if((num[i]-1)/4 == (num[i+1]-1)/4)
            continue;
        else
            return -1;
    }
    return 0;
}

int board::pcJudge(int type)//电脑的算法
{
    switch(type)
    {
    default:
        search0();
        qDebug()<<"pc";
    }

}

int board::search0()
{
    this->sendTimer();
}

int board::search1()
{

}

int board::search2()
{

}

int board::search3()
{

}

int board::search4()
{

}

int board::search5()
{

}

int board::search6()
{

}

int board::search7()
{

}

void board::initPork()//初始化牌
{
    int i,j=54,sum = 0;

    for(i=54 ; i>0 ; i--)
    {
        do
        {
            sum++;
            num[i] = qrand()%54+1;
            for(j=i+1 ; j<55 ; j++)
            {
                if(num[i] == num[j])
                    break;
            }
        }while(num[i] == num[j]);
   //     qDebug()<<"***"<<i<<"="<<num[i]<<"***";
    }
    for(i=0 ; i<17 ; i++)
    {
        pc1[i] = num[i+1];
        pc2[i] = num[i+18];
        player.p[i] = num[i+35];
        player.state[i] = 1;
    }
    qDebug()<<"sum="<<sum;
}

void board::px() //牌排序
{
    int tmp;
    for(int i=0 ; i<16 ; i++)
    {
        for(int j=i+1 ; j<17 ; j++)
        {
            if(player.p[i] > player.p[j])
            {
                tmp = player.p[i];
                player.p[i] = player.p[j];
                player.p[j] = tmp;
            }
        }
    }
    for(int i=0 ; i<17 ; i++)
    {
        qDebug()<<i<<player.p[i];
    }
}

void board::startGame()
{
    back = true;
    update();
}
