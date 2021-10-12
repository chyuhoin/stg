#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "config.h"

class GameObj
{
public:
    virtual void draw(QWidget *) = 0;
    virtual void updatePos() = 0;

    virtual ~GameObj() {}

    GameObj() {}
};

template <typename T>
class MyPoint
{
public:
    T x, y;
    MyPoint(T x = 0, T y = 0):x(x),y(y){}
    MyPoint operator= (MyPoint k) {x = k.x; y = k.y; return *this;}
};

template <typename T>
class PolarPoint
{
public:
    T r, t;
    PolarPoint(T r = 0, T t = 0) : r(r), t(t) {}
    PolarPoint(MyPoint<T> p) {r = sqrt(p.x * p.x + p.y * p.y), t = atan(p.y / p.x) + M_PI * (p.x < 0);}
    MyPoint<T> turnXYPoint() {return MyPoint<T>(r * cos(t), r * sin(t));}
};

#endif // GAMEOBJ_H
