#ifndef BULLET_H
#define BULLET_H

#include "gameobj.h"

class Bullet : public GameObj
{
public:
    //Bullet() {}
    //virtual ~Bullet() {}

    virtual void updatePos() override = 0;
    virtual void draw(QWidget *) override = 0;

    MyPoint<double> pos;

    virtual MyPoint<double> getPos() = 0;
    virtual void setPos(MyPoint<double>) = 0;

    //static QImage img;

    virtual void onHit() = 0;

    //子弹随时随地都存在，只是说“画”还是“不画”的问题
    bool isOnScreen;
    //virtual void appear(MyPoint<double>) = 0;
};

#endif // BULLET_H
