#ifndef DOUDIZHU_H
#define DOUDIZHU_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include "board.h"

namespace Ui {
    class douDiZhu;
}

class douDiZhu : public QWidget
{
    Q_OBJECT

public:
    explicit douDiZhu(QWidget *parent = 0);
    ~douDiZhu();

private:
    Ui::douDiZhu *ui;
    board *pork;
protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButtonQuit_clicked();
};

#endif // DOUDIZHU_H
