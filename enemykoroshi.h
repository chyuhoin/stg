#ifndef ENEMYKOROSHI_H
#define ENEMYKOROSHI_H

#include "enemy.h"
#include "config.h"

class EnemyKoroshi : public Enemy
{
public:
    EnemyKoroshi();

    void shootDirected(MyPoint<double>) override;

    void updatePos() override;
};

#endif // ENEMYKOROSHI_H
