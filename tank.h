#ifndef TANK_H
#define TANK_H
#include"direction.h"
#include"mapdata.h"
#include"tanktype.h"
#include"bullet.h"
#include<QWidget>
class Bullet;
class Tank{
public:
    Tank(TankType type, int x, int y, Direction direction);
    ~Tank();
    bool moveOn(const MapData& mapData,Direction direction);
    //
    void shoot();
    void destroyBullet();
    void action(const MapData &mapData);
    //Getter
    Bullet* &getBullet();
    TankType getType()const;
    Direction getDirection()const;
    int getX()const;
    int getY()const;
private:

    TankType type;
    int x;
    int y;
    Direction direction;
    Bullet* bullet;

    bool lastState;
    int lastChoice;
};
#endif // TANK_H
