#include "chinesechess.h"
#include "ui_chinesechess.h"

ChineseChess::ChineseChess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChineseChess)
{
    ui->setupUi(this);
    chess = new broad(this);
    ui->gridLayout->addWidget(chess,1,2,1,1);
    this->resize(750,700);
    ui->label->hide();
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(over()));
}

ChineseChess::~ChineseChess()
{
    delete ui;
}

void ChineseChess::over()
{
    movie = new QMovie(":/new/prefix1/shale.gif");
    ui->label->setMovie(movie);
    ui->label->setScaledContents(true);
    movie->start();
    ui->label->show();
}
