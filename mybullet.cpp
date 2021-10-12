#include "mybullet.h"
QImage MyBullet::img = QImage(":/pics/pl00.png");
MyBullet::MyBullet()
{
    isOnScreen = 0;
    pos = outPos;
    speed = 30;
}

void MyBullet::appear(MyPoint<double> poi)
{
    isOnScreen = 1;
    pos = poi;
}

void MyBullet::setPos(MyPoint<double> pos)
{
    this->pos = pos;
    if(pos.x + MY_BULLET_WIDTH < 0) isOnScreen = 0;
    else if(pos.x > GAME_WIDTH) isOnScreen = 0;
    else if(pos.y + MY_BULLET_HEIGHT < 0) isOnScreen = 0;
    else if(pos.y > GAME_HEIGHT) isOnScreen = 0;
    if(isOnScreen == 0) this->pos = outPos;
}

MyPoint<double> MyBullet::getPos()
{
    if(!isOnScreen) return this->pos = outPos;
    return MyPoint<double>(pos.x + MY_BULLET_WIDTH / 2, pos.y - ENEMY_HEIGHT / 2);
}

void MyBullet::draw(QWidget *board)
{
    QPainter painter(board);
    //painter.setPen(Qt::transparent);
    painter.translate(pos.x, pos.y);
    painter.rotate(-90);
    painter.drawImage(0, 0, img, picPos.x, picPos.y, MY_BULLET_HEIGHT, MY_BULLET_WIDTH);
}

void MyBullet::updatePos()
{
    MyPoint<double> newPos = pos;
    newPos.y -= speed;
    this->setPos(newPos);
}

void MyBullet::onHit()
{
    setPos(outPos);
}

MyBullet MyBullet::operator=(const MyBullet &B)
{
    this->isOnScreen = B.isOnScreen;
    //this->img = B.img;
    this->speed = B.speed;
    this->pos = B.pos;
    return *this;
}
