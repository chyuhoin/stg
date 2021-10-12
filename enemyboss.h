#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H

#include "config.h"
#include "enemy.h"

class EnemyBoss : public Enemy
{
public:
    EnemyBoss();

    void updatePos() override;

    void shoot() override;

    void appear(MyPoint<double>) override;

    double startAng;
};

#endif // ENEMYBOSS_H
