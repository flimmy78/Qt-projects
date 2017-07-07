#include "signalguess.h"
#include "ui_signalguess.h"
#include <time.h>
#include <QDebug>
#include <QString>


SignalGuess::SignalGuess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignalGuess)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(1000);
    tmp_num = 0;
    count = 30;
    qsrand(time(0));
    num = creatnumber();//%9000 + 1000;
    ui->widget->setEnabled(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(myClock()));
    connect(this,SIGNAL(SendNum(int)),ui->lcdNumber_2,SLOT(display(int)));
    connect(this,SIGNAL(SendQuit()),this,SLOT(close()));
    connect(ui->pushButtonQuit,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButtonBegin,SIGNAL(clicked()),this,SLOT(mySlot()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(myClick()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(myClick1()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(myClick2()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(myClick3()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(myClick4()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(myClick5()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(myClick6()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(myClick7()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(myClick8()));
    connect(ui->pushButton_10,SIGNAL(clicked()),this,SLOT(myClick9()));
    qDebug()<<"num="<<answer;
}

SignalGuess::~SignalGuess()
{
    delete ui;
}
/*
void SignalGuess::myClick()
{
    QString str(this->sender()->objectName());
    checkNum(atoi(strchr(str,'_')+1)-1);
}*/

void SignalGuess::myClick() { checkNum(0);}
void SignalGuess::myClick1() { checkNum(1); }
void SignalGuess::myClick2() { checkNum(2); }
void SignalGuess::myClick3() { checkNum(3); }
void SignalGuess::myClick4() { checkNum(4); }
void SignalGuess::myClick5() { checkNum(5); }
void SignalGuess::myClick6() { checkNum(6); }
void SignalGuess::myClick7() { checkNum(7); }
void SignalGuess::myClick8() { checkNum(8); }
void SignalGuess::myClick9() { checkNum(9); }

int SignalGuess::creatnumber(void)
{
  do
  {
      answer *= qrand();
      answer %= 10000;
  }while(answer < 999);
  return answer;
}

void SignalGuess::checkNum(int x)
{
    tmp_num = tmp_num*10 + x;
    ui->lcdNumber->display(tmp_num);
    if(tmp_num > 999)
    {
        Pk(tmp_num,num);
        tmp_num = 0;
    }
}

void SignalGuess::Pk(int tmp_num,int num)
{
  //  QString str("Perfect!");
    if(tmp_num == num){
        ui->textBrowser->append("Perfect!");
        ui->label->setText("Perfect!");
        ui->widget->setEnabled(false);
    }
    else if(tmp_num > num){
        ui->textBrowser->append("Very Big!");
        ui->label->setText("Very Big!");
    }
    else{
        ui->textBrowser->append("Very Small!");
        ui->label->setText("Very Small!");
    }
}

void SignalGuess::mySlot()
{
    ui->widget->setEnabled(true);
    ui->pushButtonBegin->setEnabled(false);
}

void SignalGuess::myClock()
{
    emit this->SendNum(count--);
    if(count == -1)
    {
        emit this->SendQuit();
    }
}
