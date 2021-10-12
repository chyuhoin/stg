#include "enemykoroshi.h"

EnemyKoroshi::EnemyKoroshi()
{
    picPos = MyPoint<int>(0, 576);

    died = 1, isOnScreen = shouldReverse = 0;
    this->pos = outPos;

    for(int i = 1; i <= 4; i++)
    {
        stopPicPosition[i] = MyPoint<int>((i - 1) * (ENEMY_WIDTH), 576);
        intervalPicPosition[i] = MyPoint<int>((i + 3) * ENEMY_WIDTH, 576);
        movePicPosition[i] = MyPoint<int>((i + 7) * (ENEMY_WIDTH), 576);
    }

    for(int i = 1; i <= 8; i++)
    {
        diePicPosition[i] = MyPoint<int>((i + 7) * (ENEMY_WIDTH), 6 * ENEMY_HEIGHT);
    }
}

void EnemyKoroshi::updatePos()
{
    for(auto it = buls.begin(); it != buls.end(); it++)
        it->updatePos();

    if(!isOnScreen || died) return;

    MyPoint<double> newpos = getPos();
    newpos.y -= 10;

    anime(newpos);
    shootCnt++;

    setPos(newpos);
}

void EnemyKoroshi::shootDirected(MyPoint<double> reimu)
{
    MyPoint<double> spd = MyPoint<double>(reimu.x - getPos().x, reimu.y - getPos().y);

    bool ok = 0;
    double angle = 0;

    PolarPoint<double> polarSpd(spd);
    polarSpd.t += angle, polarSpd.r = 5;

    for(auto it = buls.begin(); it != buls.end(); it++)
        if(!it->isOnScreen) {it->appear(getPos(), polarSpd.turnXYPoint(), 9); ok = 1; break;}
    if(ok) return;

    EnemyBullet newbul;
    newbul.appear(getPos(), polarSpd.turnXYPoint(), 9);
    buls.push_back(newbul);
}
