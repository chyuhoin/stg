#ifndef MAP_H
#define MAP_H

#include "gameobj.h"

class Map : public GameObj
{
public:
    //构造函数
    Map();

    virtual ~Map() {};

    virtual void draw(QWidget *) override;
    virtual void updatePos() override;

    //地图图片对象
    QPixmap m_map1[2];
    QPixmap m_map2[2];

    //地图Y轴坐标
    int m_map1_posY[2];
    int m_map2_posY[2];

    //地图滚动幅度
    int m_scroll_speed[2];
};

#endif // MAP_H
