#include "enemyboss.h"

EnemyBoss::EnemyBoss()
{
    picPos = MyPoint<int>(0, 640);

    died = 1, isOnScreen = shouldReverse = 0;
    this->pos = outPos;

    for(int i = 1; i <= 4; i++)
    {
        stopPicPosition[i] = MyPoint<int>((i - 1) * (ENEMY_WIDTH), 640);
        intervalPicPosition[i] = MyPoint<int>((i + 3) * ENEMY_WIDTH, 640);
        movePicPosition[i] = MyPoint<int>((i + 7) * (ENEMY_WIDTH), 640);
    }

    for(int i = 1; i <= 8; i++)
    {
        diePicPosition[i] = MyPoint<int>((i + 7) * (ENEMY_WIDTH), 6 * ENEMY_HEIGHT);
    }
}

void EnemyBoss::updatePos()
{
    for(auto it = buls.begin(); it != buls.end(); it++)
        it->updatePos();

    if(!isOnScreen || died) return;

    MyPoint<double> newPos = getPos();
    if(newPos.y < 100) newPos.y += 1;

    shootCnt++;

    anime(newPos);
    if(!died)
    {
        startAng = 0;
        shoot();
        startAng = M_PI * 2.0 / 3.0;
        shoot();
        startAng = M_PI * 4.0 / 3.0;
        shoot();
    }

    setPos(newPos);
}

void EnemyBoss::shoot()
{
    MyPoint<double> spd = MyPoint<double>(cos(startAng), sin(startAng));

    bool ok = 0;
    double angle = shootCnt / 15.0;

    PolarPoint<double> polarSpd(spd);
    polarSpd.t += angle, polarSpd.r = 3;

    for(auto it = buls.begin(); it != buls.end(); it++)
        if(!it->isOnScreen) {it->appear(getPos(), polarSpd.turnXYPoint(), 6 + startAng * 3 / M_PI); ok = 1; break;}
    if(ok) return;

    EnemyBullet newbul;
    newbul.appear(getPos(), polarSpd.turnXYPoint(), 9);
    buls.push_back(newbul);
}

void EnemyBoss::appear(MyPoint<double> pos)
{
    isOnScreen = 1;
    setPos(pos);
    HP = 1000;
    shootCnt = died = 0;
    startAng = 0;
}
