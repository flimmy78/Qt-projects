#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include <QLabel>

typedef struct pp
{
    int p[17];
    int state[17];
}PLAYER;

class board : public QWidget
{
    Q_OBJECT
public:
    QPushButton *pass;
    QPushButton *entry;
    QPushButton *passButton1;
    QPushButton *passButton2;
    QLabel *label1;
    int num[55],tt;
    QTimer *timer;
    PLAYER player;
    int flag;//牌的选中状态
    bool back;//开始游戏状态
    int pc1[17],pc2[17];

    void initButton();
    void initPork();
    void px();
    int judge();
    int pcJudge(int type);
    int oneJudge(int num[],int j);
    int twoJudge(int num[],int j);
    int threeJudge(int num[],int j);
    int fourJudge(int num[],int j);
    int lianJudge(int num[],int j);
    int san_oneJudge(int num[],int j);
    int san_twoJudge(int num[],int j);
    int lian_duiJudge(int num[],int j);
    int search0();
    int search1();
    int search2();
    int search3();
    int search4();
    int search5();
    int search6();
    int search7();
    explicit board(QWidget *parent = 0);

signals:
    void sendTimer();
public slots:
    void startGame();
    int exec_judge();
    void timerStart();
    void pc();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // BOARD_H
