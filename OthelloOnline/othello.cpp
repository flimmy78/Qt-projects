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
    connect(timer,SIGNAL(timeout()),this,SLOT(myTime()));//��ʱ
    connect(this,SIGNAL(sendTime(int)),ui->lcdNumber,
            SLOT(display(int)));//��ʾʱ�亯��
    connect(chess,SIGNAL(disNum(int,int,int)),this,
            SLOT(disChessNum(int,int,int))); //��ʾ˫��������
    connect(timerFlag,SIGNAL(timeout()),this,SLOT(currentPlayer()));//��˸
    connect(ui->pushButtonBack,SIGNAL(clicked()),
            chess,SLOT(backChess()));//����
    connect(chess,SIGNAL(backEnable()),this,
            SLOT(buttonBackEnable()));//���һ�¿��Ի���
    connect(ui->pushButtonQuit,SIGNAL(clicked()),
            this,SLOT(close()));  //�˳�
    connect(ui->pushButtonRestart,SIGNAL(clicked())
            ,this,SLOT(reStart())); //���¿�ʼ
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

void Othello::disChessNum(int white,int black,int flag) //��ʾ˫��������
{
    ui->lcdNumber_2->display(white);
    ui->lcdNumber_3->display(black);
    player = flag;
    timerFlag->start(200);
    if(black + white == 64)
    {
        timerFlag->stop(); //ͷ������
        qDebug()<<"The Winer is :";
        int button;
        int winer = (black > white) ? black:white;
        QString str;
        if(winer == black)
            str = "black win!";
        else if (winer == white)
            str = "white win!";

        chess->initBroad();
        button = QMessageBox::question(this,"��Ϸ������",
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

void Othello::on_pushButton_4_clicked()  //�л�����
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
