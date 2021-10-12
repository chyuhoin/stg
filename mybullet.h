#ifndef MYBULLET_H
#define MYBULLET_H

#include "bullet.h"

class MyBullet : public Bullet
{
public:
    MyBullet();
    virtual ~MyBullet() {}

    void updatePos() override;
    void draw(QWidget *) override;

    void onHit() override;

    void setPos(MyPoint<double>) override;
    MyPoint<double> getPos() override;

    void appear(MyPoint<double>);
    static QImage img;

    const MyPoint<int> picPos = MyPoint<int>(0, 352);
    const MyPoint<double> outPos = MyPoint<double>(-1000, -1000);

    double speed;

    MyBullet operator=(const MyBullet&);
};

#endif // MYBULLET_H
