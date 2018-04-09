#ifndef BULLET_H
#define BULLET_H

#include"direction.h"
#include"tank.h"
#include"mapdata.h"
class Tank;
class Bullet
{
public:
    Bullet(int x, int y, Direction direction,int speed);
    void move();
    //
    int getX()const;
    int getY()const;
    Direction getDirection()const;
    //
    bool isOutside()const;
    bool isCollideTank(Tank& tank)const;
    bool isCollideBullet(Bullet& bullet)const;
    bool isCollideWall(MapData& mapData);
private:
    timeval moveTime;
    int x,y;
    const Direction direction;
    double speed;
};

#endif // BULLET_H
