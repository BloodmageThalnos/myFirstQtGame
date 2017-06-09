#ifndef MAIN_H
#define MAIN_H

#include <Qt>
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QThread>
#include <QList>

//#include <vector>
#include <algorithm>

const int __game_dps=10;                 //refreshing interval in milliseconds
const double __game_gravity=4000.0;        //speed dropping down
const int __ch_size=100;            //size of the running charactor(affects both apperance and collapsition)
const int __ch_jump=1250;           //strength of AoDaCat's leg
const int __ch_doublejump=900;     //strength of AoDaCat's Chakra
const int __ch_panx1=30,
          __ch_panx2=70,
          __ch_pany1=10,
          __ch_pany2=100;
const int __ch_shadow=10;

const int __create_inteval=2000;    //in milliseconds

const double __monster_speed=400;   //pixel every second
const double __monster_accel=0;    //every second

const int __game_mapCnt=5,
          __game_difficulty=2;
const int __game_map[__game_difficulty][__game_mapCnt][1000]={
{
    {1500,1,0,60,100,   1100,2,0,40,60, 600,2,0,40,60 },
    {1500,1,0,60,100,   450,2,0,40,60,  300,1,0,60,100},
    {1500,1,0,60,100,   300,2,0,40,60,  300,1,0,60,100},
    {1500,1,0,100,150   },
    {1500,1,0,60,100,   540,1,0,60,100, 540,1,0,60,100, 540,1,0,60,100}
},{
    {1000,1,0,60,100,   1100,2,0,40,60, 600,2,0,40,60 },
    {1000,1,0,60,100,   360,2,0,40,60,  360,1,0,60,100},
    {1000,1,0,60,100,   300,2,0,40,60,  300,1,0,60,100},
    {1000,1,0,120,180   },
    {1200,1,0,60,100,   540,1,0,60,100, 540,1,0,60,100, 540,1,0,60,100}
}
};


#include <game.h>

#endif // MAIN_H
