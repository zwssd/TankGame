#include "game.h"
#include<Qt>
#include"settings.h"
#include<QDebug>
#include<QMainWindow>
#include<unistd.h>
#include<sys/time.h>
Game::Game(std::string filename):
    allEnemy(Settings::allEnemy),
    mapData(Settings::width,Settings::height,filename),
    player(TankType::PLAYER,5*Settings::blockLength,(Settings::height-2)*Settings::blockLength,Direction::UP),
    keyInput(-1),isStarted(false),gameOver(false){
}
Game::~Game(){}
void Game::draw(QPainter &pen){
    mapData.draw(pen);
    player.draw(pen);
    for(Tank& e:enemy){
        e.draw(pen);
    }
    if(player.getBullet()){
        player.getBullet()->draw(pen);
    }
    for(Tank& e:enemy){
        if(e.getBullet()){
            e.getBullet()->draw(pen);
        }
    }
    mapData.drawGrass(pen);
}
//Getter start
/*
MapData &Game::getMapData(){
    return mapData;
}
*/
int Game::getAllEnemy(){
    return allEnemy;
}
bool Game::getIsStarted(){
    return isStarted;
}

//保存输入按键
void Game::input(int key){
    keyInput=key;
}
//开始停止
void Game::stop(){
    isStarted=false;
}
//启动新进程
void Game::start(Game *game,QMainWindow *w){
    qDebug()<<"Game Start!!!";
    Game::connect(game,SIGNAL(up()) ,w,SLOT(update()));
    //
    game->isStarted=true;
    time_t lastAction=time(nullptr);
    timeval lastMoveTime;
    gettimeofday(&lastMoveTime,nullptr);
    timeval lastTankMoveTime;
    gettimeofday(&lastTankMoveTime,nullptr);
    //
    while(game->isStarted&&!game->gameOver){

        //处理坦克速度
        timeval currentTankMoveTime;
        gettimeofday(&currentTankMoveTime,nullptr);
        int distanceTank=(currentTankMoveTime.tv_sec*1000+currentTankMoveTime.tv_usec/1000          //ms
                  -lastTankMoveTime.tv_sec*1000-lastTankMoveTime.tv_usec/1000)                  //ms
                *Settings::tankSpeed/1000;
        qDebug()<<"tankSpeed="<<Settings::tankSpeed;
        qDebug()<<"distanceTank="<<distanceTank;
        qDebug()<<"currentTankMoveTime.tv_sec="<<currentTankMoveTime.tv_sec;
        qDebug()<<"currentTankMoveTime.tv_usec="<<currentTankMoveTime.tv_usec;
        qDebug()<<"lastTankMoveTime.tv_sec="<<lastTankMoveTime.tv_sec;
        qDebug()<<"lastTankMoveTime.tv_usec="<<lastTankMoveTime.tv_usec;
        lastTankMoveTime=currentTankMoveTime;

        //处理输入
        switch (game->keyInput) {
        case Qt::Key_Up:
            game->player.moveOn(game->mapData,Direction::UP,distanceTank);
            break;
        case Qt::Key_Down:
            game->player.moveOn(game->mapData,Direction::DOWN,distanceTank);
            break;
        case Qt::Key_Left:
            game->player.moveOn(game->mapData,Direction::LEFT,distanceTank);
            break;
        case Qt::Key_Right:
            game->player.moveOn(game->mapData,Direction::RIGHT,distanceTank);
            break;
        case Qt::Key_Space:
            qDebug()<<"Piu Piu Piu!!!";
            game->player.shoot();
            break;
        default:
            break;
        }

        game->keyInput=-1;
        usleep(20000);//休息50ms
        //补充敌人
        while(game->enemy.size()<Settings::maxExist&&game->allEnemy>0){
            game->enemy.emplace_back(Tank(TankType::ENERMY,0,0,Direction::DOWN));
            game->allEnemy--;
        }
        //

        //
        bool pbShouldDestroy=false;

        //
        timeval currentMoveTime;
        gettimeofday(&currentMoveTime,nullptr);
        int distance=(currentMoveTime.tv_sec*1000+currentMoveTime.tv_usec/1000          //ms
                  -lastMoveTime.tv_sec*1000-lastMoveTime.tv_usec/1000)                  //ms
                *Settings::bulletSpeed/1000;
        lastMoveTime=currentMoveTime;
        //更新玩家子弹移动
        Bullet* pbullet=game->player.getBullet();
        if(pbullet!=nullptr){
            pbullet->move(distance);
            pbShouldDestroy=pbullet->isCollideWall(game->mapData);
            if(pbullet->isOutside())pbShouldDestroy=true;
        }

        //
        for(auto e=game->enemy.begin();e!=game->enemy.end();){
            //敌军被击杀
            if(pbullet!=nullptr&&pbullet->isCollideTank(*e)){
                e=game->enemy.erase(e);
                pbShouldDestroy=true;
                continue;
            }
            //
            bool ebShouldDestroy=false;
            Bullet* ebullet=e->getBullet();
            if(ebullet!=nullptr){
                ebullet->move(distance);
                ebShouldDestroy=ebullet->isCollideWall(game->mapData);
                if(ebullet->isCollideTank(game->player)){
                    ebShouldDestroy=true;
                    game->gameOver=true;
                }
                if(pbullet!=nullptr&&ebullet->isCollideBullet(*pbullet)){
                    ebShouldDestroy=true;
                    pbShouldDestroy=true;
                }
                if(ebullet->isOutside())ebShouldDestroy=true;
                if(ebShouldDestroy)e->destroyBullet(); 
            }
            ++e;
        }
        if(pbShouldDestroy)game->player.destroyBullet();
        //敌军random动作更新
        time_t current=time(nullptr);
        if(current-lastAction>=1){
            for(Tank& e:game->enemy){
                e.action(game->mapData);
            }
            lastAction=current;
        }
        //更新画面
         emit game->up();
    }
    if(game->gameOver){
        qDebug()<<"OVER";
    }
}
