#ifndef MAPDATA_H
#define MAPDATA_H

#include"filltype.h"
#include<vector>
#include<fstream>
#include<QPainter>
class MapData
{
public:
    MapData(int width, int height, std::string filename);

    bool isSolid(int x,int y)const;
    FillType getType(int x,int y)const;
    void fillWith(int x,int y,FillType fillType);

    void loadMap(std::string filename="map.dat");
    void loadMap(std::ifstream &in);
    void draw(QPainter& pen);
    void drawGrass(QPainter& pen);
private:
    int width,height;
    std::vector<std::vector<FillType>> mapVV;

};

#endif // MAPDATA_H
