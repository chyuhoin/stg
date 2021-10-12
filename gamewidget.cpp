#include "gamewidget.h"
#include <QSound>
#include "config.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    //初始化窗口大小
   setFixedSize(GAME_WIDTH, GAME_HEIGHT);

   //设置窗口标题
   setWindowTitle("DanmakuGame v2.0");

   //键盘焦点设置
   setFocusPolicy(Qt::StrongFocus);

   //初始化参数
   flameCnt = 0;

}

void GameWidget::init()
{
    //定时器设置
    m_Timer = new QTimer();
    dieTimer = new QTimer();
    m_Timer->setInterval(GAME_RATE);
    dieTimer->setInterval(2000);

    for(int i = 0; i < 198; i++)
    {
        yose[i].disappear();
        redYose[i].disappear();
        if(i < 48) boss[i].disappear();
    }
    flameCnt = 0;
    reimu.died = 0;
    reimu.setPos((MyPoint<double>(GAME_WIDTH / 2, GAME_HEIGHT / 2 + GAME_HEIGHT / 3)));
}

void GameWidget::playGame()
{
    init();

    //背景音乐开始
    QSound *bgm = new QSound("bgm.wav");
    bgm->play();

    //定时器设置
    m_Timer->stop();
    dieTimer->setInterval(2000);

    //启动定时器
    m_Timer->start();//qDebug() << "www";

    //监听定时器
    connect(m_Timer, &QTimer::timeout, [=](){
        qDebug() << flameCnt;
        flameCnt++;

        if(flameCnt >= 3000)
        {
            if(flameCnt % 1000 == 0)
            for(int i = 0; i < 48; i++)
            if(boss[i].isOnScreen == false)
            {
                boss[i].appear(MyPoint<double>((qrand() % (GAME_WIDTH - 300)) + 300, 30));
                break;
            }
            goto judge;
        }

        if(flameCnt % 70 == 0)
        for(int i = 0; i < 198; i++)
        if(yose[i].isOnScreen == false)
        {
            yose[i].appear(MyPoint<double>((qrand() % (GAME_WIDTH - 50)) + 20, 30));
            break;
        }

        if(flameCnt % 1000 <= 100 && flameCnt % 10 == 0)
        {
            for(int i = 0; i < 198; i++)
            if(redYose[i].isOnScreen == false)
            {
                redYose[i].appear(MyPoint<double>(90, GAME_HEIGHT - 50));
                break;
            }
            for(int i = 0; i < 198; i++)
            if(redYose[i].isOnScreen == false)
            {
                redYose[i].appear(MyPoint<double>(GAME_WIDTH - 110, GAME_HEIGHT - 50));
                break;
            }
        }

        judge:

        reimu.move(press, release);

        //判定
        for(auto it = reimu.buls.begin(); it != reimu.buls.end(); it++)
        if(it->isOnScreen)
        {
            for(int i = 0; i < 198; i++)
            if(yose[i].isOnScreen && yose[i].died == 0)
            {
                double deltaX = yose[i].getPos().x - it->getPos().x;
                double deltaY = yose[i].getPos().y - it->getPos().y;
                if(deltaX *deltaX + deltaY * deltaY < 10000)
                {
                    yose[i].onHitBy(it);
                    it->onHit();
                    break;
                }
            }

            for(int i = 0; i < 198; i++)
            if(redYose[i].isOnScreen && redYose[i].died == 0)
            {
                double deltaX = redYose[i].getPos().x - it->getPos().x;
                double deltaY = redYose[i].getPos().y - it->getPos().y;
                if(deltaX *deltaX + deltaY * deltaY < 10000)
                {
                    redYose[i].onHitBy(it);
                    it->onHit();
                    break;
                }
            }

            for(int i = 0; i < 48; i++)
            if(boss[i].isOnScreen && boss[i].died == 0)
            {
                double deltaX = boss[i].getPos().x - it->getPos().x;
                double deltaY = boss[i].getPos().y - it->getPos().y;
                if(deltaX *deltaX + deltaY * deltaY < 10000)
                {
                    boss[i].onHitBy(it);
                    it->onHit();
                    break;
                }
            }
        }

        for(int i = 0; i < 198; i++)
        if(yose[i].isOnScreen)
        {
            for(auto it = yose[i].buls.begin(); it != yose[i].buls.end(); it++)
            {
                double deltaX = reimu.getPos().x - it->getPos().x;
                double deltaY = reimu.getPos().y - it->getPos().y;
                if(deltaX *deltaX + deltaY * deltaY < (8 + 2) * (8 + 2)) reimu.onHitBy(it);
            }
        }

        for(int i = 0; i < 198; i++)
        if(redYose[i].isOnScreen)
        {
            for(auto it = redYose[i].buls.begin(); it != redYose[i].buls.end(); it++)
            {
                double deltaX = reimu.getPos().x - it->getPos().x;
                double deltaY = reimu.getPos().y - it->getPos().y;
                if(deltaX *deltaX + deltaY * deltaY < (8 + 2) * (8 + 2)) reimu.onHitBy(it);
            }
        }

        for(int i = 0; i < 48; i++)
        if(boss[i].isOnScreen)
        {
            for(auto it = boss[i].buls.begin(); it != boss[i].buls.end(); it++)
            {
                double deltaX = reimu.getPos().x - it->getPos().x;
                double deltaY = reimu.getPos().y - it->getPos().y;
                if(deltaX *deltaX + deltaY * deltaY < (8 + 2) * (8 + 2)) reimu.onHitBy(it);
            }
        }

        press.clear();
        release.clear();

        //更新游戏中元素的坐标
        updatePosition();
        //重新绘制图片
        update();

        if(reimu.died)
        {
            dieTimer->start();
            m_Timer->stop();
            connect(dieTimer,&QTimer::timeout,[=](){
                bgm->stop();dieTimer->stop(); emit endGame();});
        }
    });

}

void GameWidget::updatePosition()
{
    m_map.updatePos();

    reimu.updatePos();
    for(int i = 0; i < 198; i++)
    {
        yose[i].updatePos();
        if(!yose[i].died && yose[i].shootCnt % 40 == 0)
        yose[i].shootDirected(reimu.getPos());
    }
    for(int i = 0; i < 198; i++)
    {
        redYose[i].updatePos();
        if(!redYose[i].died && redYose[i].shootCnt % 10 == 0)
        redYose[i].shootDirected(reimu.getPos());
    }
    for(int i = 0; i < 48; i++)
    {
        boss[i].updatePos();
        if(!boss[i].died && boss[i].shootCnt % 400 <= 40 && boss[i].shootCnt % 20 == 0)
        boss[i].shootDirected(reimu.getPos());
    }
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    m_map.draw(this);
    reimu.draw(this);

    for(int i = 0; i < 198; i++)
       yose[i].draw(this);
    for(int i = 0; i < 198; i++)
       redYose[i].draw(this);
    for(int i = 0; i < 48; i++)
        boss[i].draw(this);

    reimu.drawPoint(this);
}


void GameWidget::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << event->key();
    if(!event->isAutoRepeat())
    press.push_back(event->key());
}

void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    //qDebug() << event->key();
    if(!event->isAutoRepeat())
    release.push_back(event->key());
}
