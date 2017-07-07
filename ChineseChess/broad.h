#ifndef BROAD_H
#define BROAD_H

#include <QWidget>
#include <QMouseEvent>

class broad : public QWidget
{

    Q_OBJECT
public:
    explicit broad(QWidget *parent = 0);
    int p_flag;
    int tmp_x,tmp_y;//��Ҫ�ߵ���������
    int oldSignx,oldSigny,newSignx,newSigny;//�����ƶ���־
    int chess[9][10];
    bool pitch;//���ӱ�ѡ�е�״̬
    void initBroad();
    void flushSign();//ˢ�¸�����־
    int judge(int oldx,int oldy,int x,int y,int flag);
    int judge_ma(int oldx,int oldy,int x,int y);
    int che_pao(int oldx,int oldy,int x,int y,int fflag,int flag);
    int judge_zu(int oldx,int oldy,int x,int y,int flag);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

};

#endif // BROAD_H
