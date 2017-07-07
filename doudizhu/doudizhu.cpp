#include "doudizhu.h"
#include "ui_doudizhu.h"
#include <QPainter>
#include <QDebug>

douDiZhu::douDiZhu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::douDiZhu)
{
    ui->setupUi(this);
    this->resize(800,600);
    pork = new board(this);
    ui->gridLayout->addWidget(pork,0,0,1,1);
    connect(ui->pushButtonStart,SIGNAL(clicked()),pork,SLOT(startGame()));
//    qDebug()<<"test88";
}

douDiZhu::~douDiZhu()
{
    delete ui;
}


void douDiZhu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),\
                       this->height(),QPixmap(":new/back.jpg"));
}



void douDiZhu::on_pushButtonQuit_clicked()
{
    this->close();
}
