#include "othello.h"
#include "ui_othello.h"
#include "chessbroad.h"
#include <QDebug>
#include <stdio.h>
#include <QMessageBox>


Othello::Othello(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Othello)
{
    x = 0,y = 0,flag = 1;
    timeNum = 0;
    ui->setupUi(this);
    chess = new ChessBroad(this);
    timer = new QTimer(this);
    timerFlag = new QTimer(this);
    ui->pushButtonBack->setEnabled(false);
    ui->gridLayout->addWidget(chess,1,0,1,1);
    this->setAttribute(Qt::WA_PaintOutsidePaintEvent);
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(myTime()));//计时
    connect(this,SIGNAL(sendTime(int)),ui->lcdNumber,
            SLOT(display(int)));//显示时间函数
    connect(chess,SIGNAL(disNum(int,int,int)),this,
            SLOT(disChessNum(int,int,int))); //显示双方棋子数
    connect(timerFlag,SIGNAL(timeout()),this,SLOT(currentPlayer()));//闪烁
    connect(ui->pushButtonBack,SIGNAL(clicked()),
            chess,SLOT(backChess()));//悔棋
    connect(chess,SIGNAL(backEnable()),this,
            SLOT(buttonBackEnable()));//点击一下可以悔棋
    connect(ui->pushButtonQuit,SIGNAL(clicked()),
            this,SLOT(close()));  //退出
    connect(ui->pushButtonRestart,SIGNAL(clicked())
            ,this,SLOT(reStart())); //重新开始
    connect(ui->pushButtonHome,SIGNAL(clicked()),chess,SLOT(init()));
    connect(ui->pushButtonHome,SIGNAL(clicked()),this,SLOT(backHome()));
}

Othello::~Othello()
{
    delete ui;
}

void Othello::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen pen(Qt::red);
    pen.setColor(QColor(136,155,100));
    painter.setPen(pen);

    painter.drawPixmap(0,0,this->width(),
     this->height(),QPixmap("../image/background1.png"));
    if(player == 1)
    {
        painter.drawPixmap(ui->labelWhite->x(),ui->labelWhite->y(),
                       ui->labelWhite->width(),ui->labelWhite->width(),
                      QPixmap("../image/wc.png"));
        if(flag == 1)
        painter.drawPixmap(ui->labelBlack->x(),ui->labelBlack->y(),
                       ui->labelBlack->width(),ui->labelBlack->width(),
                      QPixmap("../image/bc.png"));
    }
    if(player == 2)
    {
        painter.drawPixmap(ui->labelBlack->x(),ui->labelBlack->y(),
                       ui->labelBlack->width(),ui->labelBlack->width(),
                      QPixmap("../image/bc.png"));
        if(flag == -1)
        painter.drawPixmap(ui->labelWhite->x(),ui->labelWhite->y(),
                       ui->labelWhite->width(),ui->labelWhite->width(),
                      QPixmap("../image/wc.png"));
    }

}


void Othello::on_pushButton_clicked()
{
    qDebug()<<"!!!";
}

void Othello::myTime()
{
    emit this->sendTime(timeNum++);;
    if(timeNum == 0)
        timer->stop();
}

void Othello::disChessNum(int white,int black,int flag) //显示双方棋子数
{
    ui->lcdNumber_2->display(white);
    ui->lcdNumber_3->display(black);
    player = flag;
    timerFlag->start(200);
    if(black + white == 64)
    {
        timerFlag->stop(); //头像闪动
        qDebug()<<"The Winer is :";
        int button;
        int winer = (black > white) ? black:white;
        QString str;
        if(winer == black)
            str = "black win!";
        else if (winer == white)
            str = "white win!";

        chess->initBroad();
        button = QMessageBox::question(this,"游戏结束！",
                                  str,
                                  QMessageBox::Yes | QMessageBox::No);
        switch(button){
            case QMessageBox::No:
                timerFlag->stop();
                break;
            case QMessageBox::Yes:
                timerFlag->stop();
                break;
            }
    }
}

void Othello::currentPlayer()
{
    update();
    flag = -flag;
}

void Othello::buttonBackEnable()
{
    ui->pushButtonBack->setEnabled(true);
}

void Othello::on_pushButton_4_clicked()  //切换界面
{
    ui->stackedWidget->setCurrentIndex(0);
    if(ui->radioButton->isChecked())
        chess->pc = false;
    if(ui->radioButton_2->isChecked())
        chess->pc = true;
}

void Othello::reStart()
{
    chess->initBroad();
    chess->initOldChess();
    timeNum = 0;
    chess->flag = 1;
    update();
}
void Othello::backHome()
{
    ui->stackedWidget->setCurrentIndex(1);
    timerFlag->stop();
}
