#ifndef FLYER_H
#define FLYER_H

#include "gameobj.h"

class Flyer : public GameObj
{
public:
    MyPoint<double> pos;
    MyPoint<int> picPos;

    //static QImage chara;

    void updatePos() override = 0;
    void draw(QWidget *) override = 0;

    virtual void onHitBy(GameObj *) = 0;
    virtual void shoot() = 0;

    virtual MyPoint<double> getPos() = 0;
    virtual void setPos(MyPoint<double>) = 0;

    Flyer() {}
    virtual ~Flyer() {}
};

#endif // FLYER_H
