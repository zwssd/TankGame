#include "bullet.h"
#include<sys/time.h>
#include"settings.h"
#include<QDebug>
Bullet::Bullet(int x,int y,Direction direction,int speed)
    :x(x),y(y),direction(direction),speed(speed){
    gettimeofday(&moveTime,nullptr);
}
void Bullet::move(){
    timeval current;
    gettimeofday(&current,nullptr);
    int distance
            =(current.tv_sec*1000+current.tv_usec/1000          //ms
              -moveTime.tv_sec*1000-moveTime.tv_usec/1000)      //ms
            *speed/1000;
    switch (direction) {
    case Direction::UP:
        y-=distance;
        break;
    case Direction::DOWN:
        y+=distance;
        break;
    case Direction::LEFT:
        x-=distance;
        break;
    case Direction::RIGHT:
        x+=distance;
        break;
    default:
        break;
    }
    moveTime=current;
}
int Bullet::getX()const{
    return x;
}
int Bullet::getY()const{
    return y;
}
Direction Bullet::getDirection()const{
    return direction;
}
bool Bullet::isOutside()const{
    if(x<0||y<0
            ||x>=Settings::width*Settings::blockLength
            ||y>=Settings::height*Settings::blockLength)
        return true;
    return false;
}
bool Bullet::isCollideWall(MapData &mapData){
    int xAt,yAt;
    bool result=false;
    switch(direction){
    case Direction::UP:
        xAt=(x-Settings::bulletRadius)/Settings::blockLength;
        yAt=(y-Settings::bulletRadius)/Settings::blockLength;
        switch (mapData.getType(xAt,yAt)) {
        case FillType::WALL:
            mapData.fillWith(xAt,yAt,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        switch (mapData.getType(xAt+1,yAt)) {
        case FillType::WALL:
            mapData.fillWith(xAt+1,yAt,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        return result;
    case Direction::DOWN:
        xAt=(x-Settings::bulletRadius)/Settings::blockLength;
        yAt=(y+Settings::bulletRadius)/Settings::blockLength;
        switch (mapData.getType(xAt,yAt)) {
        case FillType::WALL:
            mapData.fillWith(xAt,yAt,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        switch (mapData.getType(xAt+1,yAt)) {
        case FillType::WALL:
            mapData.fillWith(xAt+1,yAt,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        return result;
    case Direction::LEFT:
        xAt=(x-Settings::bulletRadius)/Settings::blockLength;
        yAt=(y-Settings::bulletRadius)/Settings::blockLength;
        switch (mapData.getType(xAt,yAt)) {
        case FillType::WALL:
            mapData.fillWith(xAt,yAt,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        switch (mapData.getType(xAt,yAt+1)) {
        case FillType::WALL:
            mapData.fillWith(xAt,yAt+1,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        return result;
    case Direction::RIGHT:
        xAt=(x+Settings::bulletRadius)/Settings::blockLength;
        yAt=(y-Settings::bulletRadius)/Settings::blockLength;
        switch (mapData.getType(xAt,yAt)) {
        case FillType::WALL:
            mapData.fillWith(xAt,yAt,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        switch (mapData.getType(xAt,yAt+1)) {
        case FillType::WALL:
            mapData.fillWith(xAt,yAt+1,FillType::NOTHING);
            result=true;
            break;
        case FillType::STEEL:
            result=true;
            break;
        default:
            break;
        }
        return result;
    default:
        return result;
    }
}
bool Bullet::isCollideTank(Tank &tank) const{
    int x=tank.getX();
    int y=tank.getY();
    return this->x>x*Settings::blockLength-Settings::bulletRadius
            &&this->y>y*Settings::blockLength-Settings::bulletRadius
            &&this->x<(x+2)*Settings::blockLength+Settings::bulletRadius
            &&this->y<(y+2)*Settings::blockLength+Settings::bulletRadius;
}
bool Bullet::isCollideBullet(Bullet &bullet) const{
    int diffX=bullet.getX()-x;
    int diffY=bullet.getY()-y;
    return sqrt(diffX*diffX+diffY*diffY)<Settings::bulletRadius;
}
