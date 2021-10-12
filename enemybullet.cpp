#include "enemybullet.h"
QImage EnemyBullet::img = QImage(":/pics/etama.png");

EnemyBullet::EnemyBullet()
{
    isOnScreen = 0;
    pos = outPos;
}

void EnemyBullet::appear(MyPoint<double> poi, MyPoint<double> speed, int clr)
{
    isOnScreen = 1;
    setPos(poi);
    this->speed = speed;
    picPos = MyPoint<int>(clr * SMALL_BULLET_WIDTH, 3 * SMALL_BULLET_HEIGHT);
}

void EnemyBullet::setPos(MyPoint<double> pos)
{
    this->pos = MyPoint<double>(pos.x - SMALL_BULLET_WIDTH / 2, pos.y - SMALL_BULLET_HEIGHT / 2);
    if(pos.x + SMALL_BULLET_WIDTH < 0) isOnScreen = 0;
    else if(pos.x > GAME_WIDTH) isOnScreen = 0;
    else if(pos.y + SMALL_BULLET_HEIGHT < 0) isOnScreen = 0;
    else if(pos.y > GAME_HEIGHT) isOnScreen = 0;
    if(isOnScreen == 0) this->pos = outPos;
}

MyPoint<double> EnemyBullet::getPos()
{
    if(!isOnScreen) return this->pos = outPos;
    return MyPoint<double>(pos.x + SMALL_BULLET_WIDTH / 2, pos.y + SMALL_BULLET_HEIGHT / 2);
}

void EnemyBullet::draw(QWidget *board)
{
    QPainter painter(board);
    //painter.setPen(Qt::transparent);
    painter.translate(pos.x, pos.y);
    painter.drawImage(0, 0, img, picPos.x, picPos.y, SMALL_BULLET_HEIGHT, SMALL_BULLET_WIDTH);
}

void EnemyBullet::updatePos()
{
    MyPoint<double> newPos = getPos();
    newPos.x += speed.x;
    newPos.y += speed.y;
    this->setPos(newPos);
}

void EnemyBullet::onHit()
{

}

EnemyBullet EnemyBullet::operator=(const EnemyBullet& k)
{
    this->isOnScreen = k.isOnScreen;
    this->picPos = k.picPos;
    this->speed = k.speed;
    this->pos = k.pos;
    return *this;
}
