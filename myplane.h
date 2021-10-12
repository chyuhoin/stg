#ifndef MYPLANE_H
#define MYPLANE_H

#include "flyer.h"
#include "mybullet.h"

class MyPlane : public Flyer
{
    //自机判定点
    QImage pointImg1, pointImg2;
    MyPoint<int> pointPosition;

    QImage chara;
    //自机所使用的立绘们在整合图中的位置（选取左上角作为代表）
    MyPoint<int> stopPicPosition[8];
    MyPoint<int> leftPicPosition[8];
    MyPoint<int> rightPicPosition[8];

    //记录已经经历过的帧数，用来画图
    int flameCnt;

    //记录这一帧里来自键盘的输入
    bool isLowSpeed;
    bool isRight;
    bool isLeft;
    bool isUp;
    bool isDown;
    bool isshooting;

    const double highSpeed = 8.0;
    const double lowSpeed = 3.5;

public:
    MyPlane();
    virtual ~MyPlane() {}

    //这个是自机的中心坐标，也是判定点的中心位置
    MyPoint<double> getPos() override;
    void setPos(MyPoint<double>) override;

    void updatePos() override;
    void draw(QWidget *) override;
    void drawPoint(QWidget *);//这个是专门用来画判定点的，因为判定点的显示优先级最高

    //处理来自键盘的输入
    void move(QVector<int>, QVector<int>);
    void shoot() override;

    //碰撞：被击操作
    void onHitBy(GameObj *) override;

    //自机发出的子弹
   QVector<MyBullet> buls;

   bool died = 0;
};

#endif // MYPLANE_H
