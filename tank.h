#ifndef TANK_H
#define TANK_H
#include"direction.h"
#include"mapdata.h"
#include"tanktype.h"
#include"bullet.h"
#include<QPainter>
class Bullet;
class Tank{
public:
    Tank(TankType type, int x, int y, Direction direction);
    ~Tank();
    bool moveOn(const MapData& mapData,Direction direction);
    //
    void draw(QPainter& pen);
    void shoot();
    void destroyBullet();
    void action(const MapData &mapData);
    //Getter
    Bullet* &getBullet();
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
