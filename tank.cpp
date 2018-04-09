#include "tank.h"
#include"settings.h"
#include<QDebug>
#include<cstdlib>
#include<sys/time.h>
#include<map>
Tank::Tank(TankType type,int x, int y, Direction direction)
    :type(type),x(x),y(y),direction(direction),bullet(nullptr),
      lastState(false),lastChoice(0)
{}
Tank::~Tank(){
    delete bullet;
}
bool Tank::moveOn(const MapData &mapData, Direction direction){
    if(this->direction!=direction){
        this->direction=direction;
        return true;
    }
    switch (direction) {
    case Direction::UP:
        if((!mapData.isSolid(x,y-1))&&(!mapData.isSolid(x+1,y-1))){
            y--;
            return true;
        }
        break;
    case Direction::DOWN:
        if(!mapData.isSolid(x,y+2)&&!mapData.isSolid(x+1,y+2)){
            y++;
            return true;
        }
        break;
    case Direction::LEFT:
        if(!mapData.isSolid(x-1,y)&&!mapData.isSolid(x-1,y+1)){
            x--;
            return true;
        }
        break;
    case Direction::RIGHT:
        if(!mapData.isSolid(x+2,y)&&!mapData.isSolid(x+2,y+1)){
            x++;
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}
void Tank::shoot(){
    if(bullet==nullptr){
        double bx=x*Settings::blockLength,by=y*Settings::blockLength;
        switch (direction) {
        case Direction::UP:
            bx+=Settings::blockLength;
            break;
        case Direction::DOWN:
            bx+=Settings::blockLength;
            by+=Settings::blockLength*2;
            break;
        case Direction::LEFT:
            by+=Settings::blockLength;
            break;
        case Direction::RIGHT:
            bx+=Settings::blockLength*2;
            by+=Settings::blockLength;
            break;
        default:
            break;
        }
        bullet=new Bullet(bx,by,direction,Settings::bulletSpeed);
    }
}
//
void Tank::action(const MapData&mapData){
    static Direction choice[4]={Direction::DOWN,Direction::LEFT,
                                Direction::RIGHT,Direction::UP};
    timeval t;
    gettimeofday(&t,nullptr);
    srand(t.tv_usec);
    if(!lastState)lastChoice=rand()%4;
    else{
        int i=rand()%9;
        if(i<4)lastChoice=i;
    }
    lastState=moveOn(mapData,choice[lastChoice]);
    if(rand()%3==2)shoot();         //1/3de jilv sheji
}
void Tank::destroyBullet(){
    delete bullet;
    bullet=nullptr;
}
//Getter
TankType Tank::getType() const{
    return type;
}
Direction Tank::getDirection() const{
    return direction;
}
int Tank::getX() const{
    return x;
}
int Tank::getY()const{
    return y;
}
Bullet* &Tank::getBullet(){
    return bullet;
}
