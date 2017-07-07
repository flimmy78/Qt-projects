#ifndef AGAINGAME_H
#define AGAINGAME_H

#include <QWidget>
#include <board.h>
#include <QMovie>
#include <QTimer>

namespace Ui {
    class AgainGame;
}

class AgainGame : public QWidget
{
    int num;
    Q_OBJECT

public:
    explicit AgainGame(QWidget *parent = 0);
    ~AgainGame();

private:
    Ui::AgainGame *ui;
    QMovie *movie;
    QTimer *timer;
    board *chess;

signals:
    int sendTime(int);
private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonStart_2_clicked();
    void disTime();
    void gameOver();
};

#endif // AGAINGAME_H
