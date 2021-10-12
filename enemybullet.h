#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"

class EnemyBullet : public Bullet
{
public:
    EnemyBullet();

    void updatePos() override;
    void draw(QWidget *) override;

    void onHit() override;

    void setPos(MyPoint<double>) override;
    MyPoint<double> getPos() override;

    void appear(MyPoint<double>, MyPoint<double>, int);
    static QImage img;

    MyPoint<int> picPos = MyPoint<int>(0, 352);
    const MyPoint<double> outPos = MyPoint<double>(-1000, -1000);

    MyPoint<double> speed;

    EnemyBullet operator= (const EnemyBullet&);
};

#endif // ENEMYBULLET_H
