#ifndef CHINESECHESS_H
#define CHINESECHESS_H

#include <QWidget>
#include "broad.h"
#include <QMovie>

namespace Ui {
    class ChineseChess;
}

class ChineseChess : public QWidget
{
    Q_OBJECT

public:
    explicit ChineseChess(QWidget *parent = 0);
    ~ChineseChess();

private:
    Ui::ChineseChess *ui;
    broad *chess;
    QMovie *movie;
public slots:
    void over();
};

#endif // CHINESECHESS_H
