#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "map.h"
#include "config.h"
#include "myplane.h"
#include "enemy.h"
#include "enemykoroshi.h"
#include "enemyboss.h"

class GameWidget : public QWidget
{
    Q_OBJECT
    //整个游戏经过的时间（帧数）
    int flameCnt;

public:
    GameWidget(QWidget *parent = nullptr);
    virtual ~GameWidget() {};

    QTimer *m_Timer, *dieTimer;

    //启动游戏  用于启动定时器对象
    void playGame();

    //初始化
    void init();

    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);

    //地图对象
    Map m_map;

    //自机
    MyPlane reimu;

    //读取来自键盘的输入
    QVector<int> press, release;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //敌机
    Enemy yose[200];
    EnemyKoroshi redYose[200];
    EnemyBoss boss[50];

signals:
    void endGame();
};

#endif // GAMEWIDGET_H
