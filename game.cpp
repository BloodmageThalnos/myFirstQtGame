#include "game.h"

const double eps=1e-6;
double addrate=1.0;

game::game(int _w,int _h,int _horiz,QWidget* pa)
    :QWidget(pa),
     width(_w),
     height(_h),
     horiz(_horiz),
     bitMap(_w,_h),
     dps(__game_dps),
     isGameOver(false),
     difficulty(0),
     timeTot(0),
     vecM()
{
    for(QPixmap*& qp:bitCh){
        qp=new QPixmap(_w,_h);
        qp->fill();
    }
}

void game::init(){
    bitMap.fill(QColor(0xff,0xeb,0xcd));
    QPainter painter(&bitMap);
    painter.drawLine(0,horiz,width,horiz);
    resize(width,height);
    show();
}

void game::start(){
    timerUpdate=startTimer(dps,Qt::PreciseTimer);
}

void game::restart(){
    vecM.clear();
    Mobj1 temp;
    ch=temp;
    addrate=1.0;

    start();
}

void game::gameover(){
    static QPixmap p1(":/test/res/1.jpg");
    ch.bitShape=&p1;
    UPDATE();
    killTimer(timerUpdate);
    isGameOver=true;
}

game::Mobj::Mobj(int _w, int _h, int _v, int _d, int _sw, int _sh)
    :w(_w),h(_h),v(_v),d(-_d),sizw(_sw),sizh(_sh)
{
    static QPixmap q4(":/test/res/4.jpg");
    bitShape=&q4;
}

game::Mobj1::Mobj1()
    :Mobj(),
     isJumped(false),
     isDoubleJumped(false),
     panx1(__ch_panx1),
     panx2(__ch_panx2),
     pany1(__ch_pany1),
     pany2(__ch_pany2)
{
}

void game::Mobj1::update(int t /* ms */){
    if(h<eps && v<eps){
        v=0;
        h=0;
        return;
    }
    h=h+v*t/1000;
    v+=d*t/1000;
    if(h<eps){
        static QPixmap p4(":/test/res/4.jpg");
        h=0;
        bitShape=&p4;
        isJumped=false;
        isDoubleJumped=false;
    }
}

void game::Mobj1::jump(){
    if(!isJumped++){
        v=__ch_jump;
        static QPixmap p3(":/test/res/3.jpg");
        bitShape=&p3;
    }else{
        if(isDoubleJumped++)return;
        v=__ch_doublejump;
    }
}

void game::timerEvent(QTimerEvent *event){
//    register int _id=event->timerId();
//    if(_id == timerUpdate)
//    {
    timeTot+=dps;

    ch.update(dps);
    for(auto it=vecM.begin();it!=vecM.end();++it)
        (*it)->update(dps);
    for(auto it=vecM.begin();it!=vecM.end();){
        Mobj *t=*it;
        if(t->w + t->sizw < 0){
            delete *it;
            it=vecM.erase(it);
            continue;
        }
        if(ch.w+ch.panx1 < t->w+t->sizw && ch.w+ch.panx2 > t->w && ch.h+ch.panx1 < t->h+t->sizh && ch.h+ch.panx2 > t->h){
            gameover();
        }
        ++it;
    }

    static struct{
                int t;
                Mobj* m;
            }arrMap[200];
    static int L=0,R=0;
    if(L==R){
        R=getNextScene((int *)&arrMap);
        L=0;
    }
    if( (arrMap[L].t-=dps) < 0){
        vecM.push_back(arrMap[L].m);
        ++L;
    }

    if(addrate<1.5)addrate+=0.1/dps;
    if(difficulty==0 && timeTot>10000)difficulty=1;

    UPDATE();
//    }
}

int game::getNextScene(int* p,int g){
    for(int a,*f=(int*)__game_map[difficulty][rand()%__game_mapCnt];a=*f++;g++){
        int b=*f++,h=*f++,c=*f++,d=*f++;
        *p++=a;
        *p++=(int)([=]()->game::Mobj*{
            switch(b){
            case 1:
                return new game::Nobj1(1000,h,__monster_speed,__monster_accel,c,d);
            case 2:
                return new game::Nobj2(1000,h,__monster_speed,__monster_accel,c,d);
            }
        })();
    }
    return g;
}

void game::paintEvent(QPaintEvent *event){
    static int _y=0;
    _y = (_y+1) % __ch_shadow;
    QPainter painter(this),painter2(bitCh[_y]);

    bitCh[_y]->fill();
    painter2.setOpacity(0.6);
    painter2.drawPixmap(0,0,*bitCh[_y?_y-1:__ch_shadow-1],10,0,width,height);
    painter2.setOpacity(1);
    painter2.setCompositionMode(QPainter::RasterOp_SourceAndDestination);
    painter2.drawPixmap(ch.w,horiz-(int)ch.h-ch.sizh,ch.sizw,ch.sizh,*ch.bitShape);

    painter.drawPixmap(0,0,bitMap);
    painter.setCompositionMode(QPainter::RasterOp_SourceAndDestination);
    for(auto it=vecM.begin();it!=vecM.end();++it){
        Mobj *t=*it;
        painter.drawPixmap(t->w,horiz-(t->h)-(t->sizh),t->sizw,t->sizh,*(t->bitShape));
    }
    painter.drawPixmap(0,0,*bitCh[_y]);
}

void game::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Space:
    {
        ch.jump();
        break;
    }
    case Qt::Key_Return:
    {
        if(isGameOver){
            isGameOver=false;
            restart();
            break;
        }
    }
    default:;
    }
}

game::Nobj1::Nobj1(int _w, int _h, int _v, int _d, int _sw, int _sh)
    :Mobj(_w,_h,_v,_d,_sw,_sh)
{
    static QPixmap q2(":/test/res/2.jpg");
    bitShape=&q2;
}

void game::Nobj1::update(int tm){
    w-=v*addrate*tm/1000;
}

game::Nobj2::Nobj2(int _w, int _h, int _v, int _d, int _sw, int _sh)
    :Mobj(_w,_h,_v,_d,_sw,_sh)
{
    static QPixmap q5(":/test/res/5.jpg");
    bitShape=&q5;
}

void game::Nobj2::update(int tm){
    w-=v*addrate*tm/1000;
}
