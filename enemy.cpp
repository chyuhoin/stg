#include "enemy.h"

QImage Enemy::chara = QImage(":/pics/enemy.png");

Enemy::Enemy()
{
    //if(chara.width() == 0)
    //chara.load(":/pics/enemy.png");

    picPos = MyPoint<int>(0, 512);

    died = 1, isOnScreen = shouldReverse = 0;
    this->pos = outPos;

    for(int i = 1; i <= 4; i++)
    {
        stopPicPosition[i] = MyPoint<int>((i - 1) * (ENEMY_WIDTH), 512);
        intervalPicPosition[i] = MyPoint<int>((i + 3) * ENEMY_WIDTH, 512);
        movePicPosition[i] = MyPoint<int>((i + 7) * (ENEMY_WIDTH), 512);
    }

    for(int i = 1; i <= 8; i++)
    {
        diePicPosition[i] = MyPoint<int>((i + 7) * (ENEMY_WIDTH), 6 * ENEMY_HEIGHT);
    }
}

void Enemy::setPos(MyPoint<double> pos)
{
    this->pos = MyPoint<double>(pos.x - ENEMY_WIDTH / 2, pos.y - ENEMY_HEIGHT / 2);
    if(pos.x + ENEMY_WIDTH < 0) isOnScreen = 0;
    else if(pos.x > GAME_WIDTH) isOnScreen = 0;
    else if(pos.y + ENEMY_HEIGHT < 0) isOnScreen = 0;
    else if(pos.y > GAME_HEIGHT) isOnScreen = 0;
    if(isOnScreen == 0) this->pos = outPos;
}

MyPoint<double> Enemy::getPos()
{
    if(!isOnScreen) return this->pos = outPos;
    return MyPoint<double>(pos.x + ENEMY_WIDTH / 2, pos.y + ENEMY_HEIGHT / 2);
}

void Enemy::anime(MyPoint<double> newPos)
{
    cnt++;

    //动画处理，精度要求较高时请求导，不要这么简单地相减
    bool isLeft = 0, isRight = 0;
    //qDebug() << getPos().x << " " << newPos.x;
    if(newPos.x - getPos().x < -0.1) isLeft = 1;
    else if(newPos.x -getPos().x > 0.1) isRight = 1;

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
            if(piccnt < -8) piccnt = -5;
            if(piccnt < -4) picPos = movePicPosition[-piccnt - 4];
            else picPos = intervalPicPosition[-piccnt];
            shouldReverse = 1;
        }
        else if(piccnt > 0)
        {
            if(piccnt > 8) piccnt = 5;
            if(piccnt > 4) picPos = movePicPosition[piccnt - 4];
            else picPos = intervalPicPosition[piccnt];
            shouldReverse = 0;
        }
        else
        {
            if(stopcnt > 4) stopcnt = 1;
            picPos = stopPicPosition[stopcnt];
            shouldReverse = 0;
        }
    }
}

void Enemy::updatePos()
{
    for(auto it = buls.begin(); it != buls.end(); it++)
        it->updatePos();

    if(!isOnScreen || died) return;

    MyPoint<double> newPos = getPos();
    newPos.y = 50 * sin(shootCnt / 500.0 * 2.0 *M_PI) + 100;
    newPos.x = 300 * cos(shootCnt / 500.0 * 2.0 *M_PI) + 400;

    shootCnt++;

    anime(newPos);
    if((shootCnt) % 50 == 0 && !died)
    shoot();

    setPos(newPos);
}

void Enemy::draw(QWidget *board)
{
    QPainter painter(board);

   /*if(!isOnScreen)
   {
       static int deathPicX = 0, deathPicY = ENEMY_HEIGHT;
       painter.drawImage(pos.x, pos.y, QImage(":pics/enemy2.png"), deathPicX, deathPicY, ENEMY_WIDTH, ENEMY_HEIGHT);
       deathPicX += ENEMY_WIDTH;
       return;
   }*/

//qDebug() << pos.x << pos.y;
    if(isOnScreen)
    {
        if(died)
        {
            painter.drawImage(pos.x, pos.y, chara, diePicPosition[died / 8].x, diePicPosition[died / 8].y, ENEMY_WIDTH, ENEMY_HEIGHT);
            if((++died) > 64) setPos(outPos);
        }
        else
        {
            if(shouldReverse)
            painter.drawImage(pos.x, pos.y, chara.mirrored(1,0), chara.width() - picPos.x - ENEMY_WIDTH, picPos.y, ENEMY_WIDTH, ENEMY_HEIGHT);
            else painter.drawImage(pos.x, pos.y, chara, picPos.x, picPos.y, ENEMY_WIDTH, ENEMY_HEIGHT);
        }
    }

    for(auto it = buls.begin(); it != buls.end(); it++)
        if(it->isOnScreen) it->draw(board);
}

void Enemy::appear(MyPoint<double> pos)
{
    isOnScreen = 1;
    setPos(pos);
    HP = 20;
    shootCnt = died = 0;
}

void Enemy::disappear()
{
    isOnScreen = 0;
    died = 1, isOnScreen = shouldReverse = 0;
    this->pos = outPos;
    buls.clear();
}

void Enemy::shoot()
{
    MyPoint<double> spd = MyPoint<double>(qrand(), qrand());
    spd.x = (spd.x / sqrt(spd.x * spd.x + spd.y * spd.y)) * 10;
    spd.y = (spd.y / sqrt(spd.x * spd.x + spd.y * spd.y)) * 10;
    //qDebug() << spd.x << spd.y << endl;

    for(double angle = 0; angle <= M_PI * 2; angle += M_PI / 4.0)
    {
        bool ok = 0;

        PolarPoint<double> polarSpd(spd);
        polarSpd.t += angle, polarSpd.r = 5;

        for(auto it = buls.begin(); it != buls.end(); it++)
            if(!it->isOnScreen) {it->appear(getPos(), polarSpd.turnXYPoint(), (qrand() % 10) + 1); ok = 1; break;}
        if(ok) continue;

        EnemyBullet newbul;
        newbul.appear(getPos(), polarSpd.turnXYPoint(), (qrand() % 10) + 1);
        buls.push_back(newbul);
    }
}

void Enemy::shootDirected(MyPoint<double> reimu)
{
    MyPoint<double> spd = MyPoint<double>(reimu.x - getPos().x, reimu.y - getPos().y);
    //spd.x = (spd.x / sqrt(spd.x * spd.x + spd.y * spd.y)) * 10;
    //spd.y = (spd.y / sqrt(spd.x * spd.x + spd.y * spd.y)) * 10;
    //qDebug() << spd.x << spd.y << endl;

    for(double angle = -M_PI / 12; angle <= M_PI / 12; angle += M_PI / 12.0)
    {
        bool ok = 0;

        PolarPoint<double> polarSpd(spd);
        polarSpd.t += angle, polarSpd.r = 5;

        for(auto it = buls.begin(); it != buls.end(); it++)
            if(!it->isOnScreen) {it->appear(getPos(), polarSpd.turnXYPoint(), 9); ok = 1; break;}
        if(ok) continue;

        EnemyBullet newbul;
        newbul.appear(getPos(), polarSpd.turnXYPoint(), 9);
        buls.push_back(newbul);
    }

}

void Enemy::onHitBy(GameObj *)
{
    HP--;
    if(HP == 0) died = 8;
    if(died) {for(int i = 1; i <= 2; i++) shoot();}
    //setPos(outPos);
}
