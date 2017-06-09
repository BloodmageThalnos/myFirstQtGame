#ifndef GAME_H
#define GAME_H

#include <main.h>

class game :public QWidget
{
private:
    int width,height,horiz;
    const int dps;
    QPixmap bitMap,*bitCh[__ch_shadow];
    class Mobj{
    public:
        double w,h,v,d;
        int sizw,sizh;
        QPixmap* bitShape;
        Mobj(int =100,int =0,int =0,int =__game_gravity,int =__ch_size,int =__ch_size);
        virtual void update(int ) = 0;
    };
    class Mobj1:public Mobj{
    public:
        Mobj1();
        int panx1,panx2,pany1,pany2;
        bool isJumped,isDoubleJumped;
        void jump();
        void update(int );
    }ch;
    class Nobj1:public Mobj{
    public:
        Nobj1(int, int, int, int, int, int);
        void update(int );
    };
    class Nobj2:public Mobj{
    public:
        Nobj2(int, int, int, int, int, int);
        void update(int );
    };
    QList<Mobj* > vecM;
    int timerUpdate;
    bool isGameOver;
    int difficulty,timeTot;
public:
    game(int ,int ,int ,QWidget* =0);
    void init();
    void start();
    void restart();
    void UPDATE(){
        update();
    }
    void gameover();
    int getNextScene(int* ,int =0);
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
};

#endif // GAME_H
