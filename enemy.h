#ifndef ENEMY_H
#define ENEMY_H

#include "flyer.h"
#include "enemybullet.h"

class Enemy : public Flyer
{
public:
    Enemy();
    ~Enemy() {}

    void updatePos() override;
    void draw(QWidget *) override;

    void setPos(MyPoint<double>) override;
    MyPoint<double> getPos() override;

    static QImage chara;
    //敌机所使用的立绘们在整合图中的位置（选取左上角作为代表）
    MyPoint<int> stopPicPosition[8];
    MyPoint<int> intervalPicPosition[8];
    MyPoint<int> movePicPosition[8];
    MyPoint<int> diePicPosition[8];
    int cnt = 0, stopcnt = 0, piccnt = 0;

    virtual void anime(MyPoint<double>);//动画处理

    virtual void shoot() override;
    virtual void shootDirected(MyPoint<double>);
    void onHitBy(GameObj *) override;
    int shootCnt;

    bool isOnScreen;
    const MyPoint<double> outPos = MyPoint<double>(-1000, -1000);
    virtual void appear(MyPoint<double>);
    virtual void disappear();

    bool shouldReverse;

    QVector<EnemyBullet> buls;

    int HP = 1, died = 0;
};

#endif // ENEMY_H
