#ifndef JUDGE_H
#define JUDGE_H

#include <QWidget>
#include "broad.h"

class judge : public broad
{
    Q_OBJECT
public:
    explicit judge();
    int chessJudge(int oldx,int oldy,int x,int y,int flag);
signals:

public slots:

};

#endif // JUDGE_H
