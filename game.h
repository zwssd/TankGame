#ifndef GAME_H
#define GAME_H

#include"mapdata.h"
#include"tank.h"
#include<QMainWindow>
#include<list>
#include<string>
class Game
{
public:
    Game(std::string filename="map.dat");
    ~Game();
    MapData& getMapData();
    Tank &getPlayer();
    std::list<Tank>& getEnemy();
    //
    static void start(Game* game,QMainWindow *w);
    void stop();
    void input(int key);
private:
    int allEnemy;
    MapData mapData;
    Tank player;
    std::list<Tank> enemy;
    int keyInput;
    bool isStarted;
    bool gameOver;
};

#endif // GAME_H
