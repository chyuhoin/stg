#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QWidget>
#include <QKeyEvent>
#include <cmath>
#include <QTimer>

#define MAP_SCROLL_SPEED 2  //下方地图滚动速度
#define MAP_SCROLL_SPEED_2 4  //上方地图滚动速度
#define GAME_WIDTH  1024  //宽度
#define GAME_HEIGHT 960  //高度
#define GAME_RATE  16  //刷新率

#define MYPLANE_HEIGHT 96 //自机图片的高度
#define MYPLANE_WIDTH 64 //自机图片的宽度
#define MYPOINT_HEIGHT 128 //自机判定点图片的高度
#define MYPOINT_WIDTH 128  //自机判定点图片的宽度

#define GIF_INTERVAL 5 //“动图”每隔这么多帧刷新一次

#define MY_BULLET_HEIGHT 128 //自机子弹的高度（注意是旋转之后）
#define MY_BULLET_WIDTH 32 //自机子弹图片的宽度

#define ENEMY_WIDTH 64 //妖精敌人的图片的宽度
#define ENEMY_HEIGHT 64 //妖精敌人的图片的高度

#define SMALL_BULLET_WIDTH 32//小玉的图片的宽度
#define SMALL_BULLET_HEIGHT 32//小玉的图片的高度

#endif // CONFIG_H
