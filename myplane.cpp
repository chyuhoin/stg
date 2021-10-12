#include "myplane.h"

MyPlane::MyPlane()
{
    //设置灵梦的初始位置
    setPos(MyPoint<double>(GAME_WIDTH / 2, GAME_HEIGHT / 2 + GAME_HEIGHT / 3));

    //加载灵梦点绘和判定点
    if(chara.width() == 0)
    chara.load(":/pics/pl00.png");
    pointImg1.load(":/pics/etama2.png");

    //设置各个子图在整个图的位置
    for(int i = 0; i < 8; i++)
    {
        stopPicPosition[i].x = MYPLANE_WIDTH * i;
        stopPicPosition[i].y = 0;

        leftPicPosition[i].x = MYPLANE_WIDTH * i;
        leftPicPosition[i].y = MYPLANE_HEIGHT * 1;

        rightPicPosition[i].x = MYPLANE_WIDTH * i;
        rightPicPosition[i].y = MYPLANE_HEIGHT * 2;
    }
    pointPosition.x = 0, pointPosition.y = 32;

    //初始化各项参数
    flameCnt = 0;
    isUp = isDown = isLeft = isRight = isLowSpeed = isshooting = 0;

    //初始化子弹
    MyBullet bul;
    buls.push_back(bul);
}

MyPoint<double> MyPlane::getPos() {return MyPoint<double>(pos.x + MYPLANE_WIDTH / 2.0, pos.y + MYPLANE_HEIGHT / 2.0);}

void MyPlane::setPos(MyPoint<double> pos)
{
    double x = std::min(std::max(pos.x - MYPLANE_WIDTH / 2.0, 0.0), (double)GAME_WIDTH - MYPLANE_WIDTH);
    double y = std::min(std::max(pos.y - MYPLANE_HEIGHT / 2.0, 0.0), (double)GAME_HEIGHT - MYPLANE_HEIGHT);
    this->pos = MyPoint<double>(x, y);

}

void MyPlane::draw(QWidget *board)
{
    QPainter painter(board);

    painter.drawImage(pos.x, pos.y, chara, picPos.x, picPos.y, MYPLANE_WIDTH, MYPLANE_HEIGHT);

    for(auto it = buls.begin(); it != buls.end(); it++)
        if(it->isOnScreen) it->draw(board);
}

void MyPlane::drawPoint(QWidget *board)
{
    flameCnt++;
    QPainter painter(board);
    if(isLowSpeed)
    {
        double angle1 = (flameCnt) % 360;//qDebug() << "low";

        //极坐标，把判定中心作为极点，Ox方向作为极轴，这样r=w/sqrt(2)
        double r = MYPOINT_WIDTH / sqrt(2);
        double drawX = getPos().x + r * cos(angle1 * M_PI / 180);
        double drawY = getPos().y + r * sin(angle1 * M_PI / 180);

        //用初中几何xjb整了一通
        painter.translate(drawX, drawY);
        painter.rotate(angle1 + 135);
        painter.drawImage(0, 0, pointImg1, pointPosition.x, pointPosition.y, MYPOINT_WIDTH, MYPOINT_HEIGHT);
        painter.resetTransform();
    }
}

void MyPlane::updatePos()
{
    static int cnt = 0, piccnt = 0, stopcnt = 0;
    cnt++;

    //先是动画的处理
    if(cnt % GIF_INTERVAL == 0
            || (abs(piccnt) < 4 && piccnt && piccnt % 2 == 0)
            || (!isLeft && !isRight && piccnt && piccnt % 2 == 0))
    {
        if(isLeft) piccnt--;
        else if(isRight) piccnt++;
        else if(piccnt < 0) piccnt++;
        else if(piccnt > 0) piccnt--;
        else stopcnt++;

        if(piccnt < 0)
        {
            if(piccnt <= -8) piccnt = -4;
            picPos = leftPicPosition[-piccnt];
        }
        else if(piccnt > 0)
        {
            if(piccnt >= 8) piccnt = 4;
            picPos = rightPicPosition[piccnt];
        }
        else
        {
            if(stopcnt >= 8) stopcnt = 0;
            picPos = stopPicPosition[stopcnt];
        }
    }

    //再是移动的处理
    double speed = isLowSpeed ? lowSpeed : highSpeed;
    if(isLeft && isUp) setPos(MyPoint<double>(getPos().x - speed * 0.7, getPos().y - speed * 0.7));
    else if(isLeft && isDown) setPos(MyPoint<double>(getPos().x - speed * 0.7, getPos().y + speed * 0.7));
    else if(isRight && isUp) setPos(MyPoint<double>(getPos().x + speed * 0.7, getPos().y - speed * 0.7));
    else if(isRight && isDown) setPos(MyPoint<double>(getPos().x + speed * 0.7, getPos().y + speed * 0.7));
    else if(isLeft) setPos(MyPoint<double>(getPos().x - speed, getPos().y));
    else if(isUp) setPos(MyPoint<double>(getPos().x, getPos().y - speed));
    else if(isRight) setPos(MyPoint<double>(getPos().x + speed, getPos().y));
    else if(isDown) setPos(MyPoint<double>(getPos().x, getPos().y + speed));

    //最后处理自机的子弹
    for(auto it = buls.begin(); it != buls.end(); it++)
        if(it->isOnScreen) it->updatePos();
    if(isshooting) shoot();
}

void MyPlane::move(QVector<int> press, QVector<int> release)
{
    for(int i = 0; i < press.size(); i++)
    {//qDebug() << operations.at(i)->key();
        if(press.at(i) == Qt::Key_Shift) isLowSpeed = 1;
        else if(press.at(i) == Qt::Key_Down) isDown = 1;
        else if(press.at(i) == Qt::Key_Up) isUp = 1;
        else if(press.at(i) == Qt::Key_Left) isLeft = 1;
        else if(press.at(i) == Qt::Key_Right) isRight = 1;
        else if(press.at(i) == Qt::Key_Z) isshooting = 1;
    }

    for(int i = 0; i < release.size(); i++)
    {//qDebug() << operations.at(i)->key();
        if(release.at(i) == Qt::Key_Shift) isLowSpeed = 0;
        else if(release.at(i) == Qt::Key_Down) isDown = 0;
        else if(release.at(i) == Qt::Key_Up) isUp = 0;
        else if(release.at(i) == Qt::Key_Left) isLeft = 0;
        else if(release.at(i) == Qt::Key_Right) isRight = 0;
        else if(release.at(i) == Qt::Key_Z) isshooting = 0;
    }
}

void MyPlane::shoot()
{
    static int flamecnt = 0;
    if((++flamecnt) % 2 == 0) return;
    int newBulletCnt = 0;
    for(auto it = buls.begin(); it != buls.end(); it++)
    {
        if(it->isOnScreen == false)
        {
            if(newBulletCnt == 0)
            it->appear(MyPoint<double>(getPos().x - MY_BULLET_WIDTH, getPos().y)),
            newBulletCnt++;
            else
            {
                it->appear(MyPoint<double>(getPos().x, getPos().y));
                newBulletCnt++;
                break;
            }
        }
    }
    if(newBulletCnt == 0)
    {
        MyBullet newbul;
        newbul.appear(MyPoint<double>(getPos().x - MY_BULLET_WIDTH, getPos().y));
        newBulletCnt++;buls.push_back(newbul);
    }
    if(newBulletCnt == 1)
    {
        MyBullet newbul;
        newbul.appear(MyPoint<double>(getPos().x, getPos().y));
        newBulletCnt++;buls.push_back(newbul);
    }
}

void MyPlane::onHitBy(GameObj * bul)
{
    died = 1;
}
