#include "game.h"
#include<Qt>
#include"settings.h"
#include<QDebug>
#include<QMainWindow>
#include<unistd.h>
Game::Game(std::string filename):
    allEnemy(Settings::allEnemy),
    mapData(Settings::width,Settings::height,filename),
    player(TankType::PLAYER,5,Settings::height-2,Direction::UP),
    keyInput(-1),isStarted(true),gameOver(false){
}
Game::~Game(){}
//获得地图
MapData &Game::getMapData(){
    return mapData;
}
//获得玩家
Tank& Game::getPlayer(){
    return player;
}
//获得敌人
std::list<Tank>& Game::getEnemy(){
    return enemy;
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
    time_t lastAction=time(nullptr);
    while(game->isStarted&&!game->gameOver){
        //处理输入
        switch (game->keyInput) {
        case Qt::Key_Up:
            game->player.moveOn(game->mapData,Direction::UP);
            break;
        case Qt::Key_Down:
            game->player.moveOn(game->getMapData(),Direction::DOWN);
            break;
        case Qt::Key_Left:
            game->player.moveOn(game->getMapData(),Direction::LEFT);
            break;
        case Qt::Key_Right:
            game->player.moveOn(game->getMapData(),Direction::RIGHT);
            break;
        case Qt::Key_Space:
            game->player.shoot();
            break;
        default:
            break;
        }
        game->keyInput=-1;
        usleep(50000);//休息50ms
        //补充敌人
        while(game->enemy.size()<Settings::maxExist&&game->allEnemy>0){
            game->enemy.emplace_back(Tank(TankType::ENERMY,0,0,Direction::DOWN));
            game->allEnemy--;
            qDebug()<<game->allEnemy;
        }
        //
        bool pbShouldDestroy=false;

        //更新玩家子弹移动
        Bullet* pbullet=game->player.getBullet();
        if(pbullet!=nullptr){
            pbullet->move();
            pbShouldDestroy=pbullet->isCollideWall(game->getMapData());
            if(pbullet->isOutside())pbShouldDestroy=true;
        }

        //
        for(auto e=game->getEnemy().begin();e!=game->getEnemy().end();){
            //敌军被击杀
            if(pbullet!=nullptr&&pbullet->isCollideTank(*e)){
                e=game->getEnemy().erase(e);
                pbShouldDestroy=true;
                continue;
            }
            //
            bool ebShouldDestroy=false;
            Bullet* ebullet=e->getBullet();
            if(ebullet!=nullptr){
                ebullet->move();
                ebShouldDestroy=ebullet->isCollideWall(game->getMapData());
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
            for(Tank& e:game->getEnemy()){
                e.action(game->getMapData());
            }
            lastAction=current;
        }
        //更新画面
        w->update();
    }
    game->isStarted=true;
    if(game->gameOver){
        qDebug()<<"OVER";
    }
}
