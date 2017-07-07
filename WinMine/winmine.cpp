#include "winmine.h"
#include "ui_winmine.h"
#include <QDebug>


WinMine::WinMine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinMine)
{
    ui->setupUi(this);
    num = 1;
    timer = new QTimer(this);
    chess = new board(this);
    ui->gridLayout->addWidget(chess,1,0,1,1);
    this->resize(423,449);
    ui->label->resize(this->width(),this->height());
    ui->label->hide();
    connect(chess,SIGNAL(sig_lose()),this,SLOT(slot_lose()));//输了
    connect(ui->pushButton_3,SIGNAL(clicked()),chess,SLOT(display()));
    connect(timer,SIGNAL(timeout()),this,SLOT(disTime()));
    connect(this,SIGNAL(sendTime(int)),ui->lcdNumber,SLOT(display(int)));//显示时间
    connect(chess,SIGNAL(gameDone()),this,SLOT(disWin()));

}

WinMine::~WinMine()
{
    delete ui;
}

void WinMine::slot_lose()
{
    movie = new QMovie(":/new/prefix1/boom.gif");

    ui->label->setMovie(movie);
    ui->label->setScaledContents(true);
    timer->stop();
    num = 1;
    movie->start();
    ui->label->show();
}

void WinMine::on_pushButton_clicked()
{
    chess->initBroad();
    chess->initSign();
    chess->firstClick = true;
    num = 1;
    timer->start(1000);
    ui->label->hide();
    update();
}

void WinMine::disTime()
{
    emit this->sendTime(num++);
}

void WinMine::disWin()
{
    timer->stop();
    movieWin = new QMovie(":/new/prefix1/win.bmp");
    ui->label->setMovie(movieWin);
    ui->label->setScaledContents(true);
    ui->label->show();
    movieWin->start();
}
