#ifndef GAME_H
#define GAME_H

#include"mapdata.h"
#include"tank.h"
#include<QMainWindow>
#include<list>
#include<string>
#include<QPainter>
class Game:public QObject
{
    Q_OBJECT

public:
    Game(std::string filename="map.dat");
    virtual ~Game();

    int getAllEnemy();
    bool getIsStarted();
    void draw(QPainter& pen);
    //
    static void start(Game* game,QMainWindow *w);
    void stop();
    void input(int key);
    //
private:
    int allEnemy;
    MapData mapData;
    Tank player;
    std::list<Tank> enemy;
    int keyInput;
    bool isStarted;
    bool gameOver;
signals:
    void up();
};

#endif // GAME_H
