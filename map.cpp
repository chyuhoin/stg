#include "map.h"
#include "config.h"

Map::Map()
{
    //初始化加载地图对象
    m_map1[0].load(":/pics/stg3bg2.png");
    m_map2[0].load(":/pics/stg3bg2.png");
    m_map1[1].load(":/pics/stg3bg.png");
    m_map2[1].load(":/pics/stg3bg.png");
    for(int i = 0; i < 2; i++)
    {
        m_map1[i] = m_map1[i].scaled(GAME_WIDTH, GAME_HEIGHT);
        m_map2[i] = m_map2[i].scaled(GAME_WIDTH, GAME_HEIGHT);
    }


    //设置地图起始y轴坐标
    for(int i = 0; i <= 1; i++)
    {
        m_map1_posY[i] = -GAME_HEIGHT;
        m_map2_posY[i] = 0;
    }

    //设置地图滚动速度
    m_scroll_speed[0] = MAP_SCROLL_SPEED;
    m_scroll_speed[1] = MAP_SCROLL_SPEED_2;
}

void Map::updatePos()
{
    //qDebug() << "qqq";
    for(int i = 0; i < 2; i++)
    {
        //处理第一张图片滚动
        m_map1_posY[i] += m_scroll_speed[i];
        if(m_map1_posY[i] >= 0)
        {
            m_map1_posY[i] =-GAME_HEIGHT;
        }

        //处理第二张图片滚动
        m_map2_posY[i] += m_scroll_speed[i];
        if(m_map2_posY[i] >= GAME_HEIGHT )
        {
            m_map2_posY[i] =0;
        }
    }
}

void Map::draw(QWidget *board)
{
    QPainter painter(board);

    for(int i = 0; i < 2; i++)
    {
        //绘制地图
        painter.drawPixmap(0, m_map1_posY[i] , m_map1[i]);
        painter.drawPixmap(0, m_map2_posY[i] , m_map2[i]);
    }
}
