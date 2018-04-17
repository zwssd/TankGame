#ifndef BULLET_H
#define BULLET_H

#include"direction.h"
#include"tank.h"
#include"mapdata.h"
#include<QPainter>
class Tank;
class Bullet
{
public:
    Bullet(int x, int y, Direction direction,int speed);
    void move(int distance);

    void draw(QPainter& pen);

    bool isOutside()const;
    bool isCollideTank(Tank& tank)const;
    bool isCollideBullet(Bullet& bullet)const;
    bool isCollideWall(MapData& mapData)const;
private:
    int x,y;
    const Direction direction;
    double speed;
};

#endif // BULLET_H
