#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class board : public QWidget
{
    int chess[4][4];

    Q_OBJECT
public:
    explicit board(QWidget *parent = 0);
    void initNum();//���������
    void initBoard();//��ʼ������
    void picMove(int x,int y);//ͼƬ�ƶ�
    int judge();//�ж���Ӯ
    int flag; //�����ʼ��ť�ı�־
    int win;
    void makeBoard();
signals:
    void end();
public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

};

#endif // BOARD_H
