#include "againgame.h"
#include "ui_againgame.h"
#include <QMessageBox>
#include <QString>

AgainGame::AgainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AgainGame)
{
    ui->setupUi(this);
    chess = new board(this);
    num = 1;
    movie = new QMovie(":/new/prefix1/yanzi.jpg");
    ui->gridLayout->addWidget(chess,0,0,1,1);
    this->resize(500,400);
    ui->label->setMovie(movie);
    ui->label->setScaledContents(true);
    movie->start();
    timer = new QTimer(this);
    connect(ui->pushButtonQuit,SIGNAL(clicked()),this,SLOT(close()));//�˳�
    connect(timer,SIGNAL(timeout()),this,SLOT(disTime()));
    connect(this,SIGNAL(sendTime(int)),ui->lcdNumber,SLOT(display(int)));
    connect(chess,SIGNAL(end()),this,SLOT(gameOver())); //������Ϸ������ʾ�õ�����
}

AgainGame::~AgainGame()
{
    delete ui;
}

void AgainGame::on_pushButtonStart_2_clicked()//��ʼ��Ϸ
{
    timer->start(1000);
    chess->win = 0;
    chess->flag = 1;
}

void AgainGame::disTime()
{
    emit this->sendTime(num++);
}

void AgainGame::on_pushButtonStart_clicked() //���²���
{
    timer->stop();
    ui->lcdNumber->display(0);
    num = 1;
    chess->initBoard();
    chess->makeBoard();
    chess->flag = 0;
    chess->win = 0;
    update();
}

void AgainGame::gameOver() //ƴͼ��� ���Ի���
{
    int button;
    QString second = "seconds";
    QString str ="win! use time ";
    num = ui->lcdNumber->intValue();
    QString str_num = QString("%1").arg(num);
    str += str_num;
    str += second;
    chess->win = 1;
    timer->stop();
    button = QMessageBox::question(this,\
        "congratulation!",str,QMessageBox::Yes);
}
