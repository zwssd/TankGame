#ifndef MAPDATA_H
#define MAPDATA_H

#include<string>
#include"filltype.h"
#include<vector>
class MapData
{
public:
    MapData(int width, int height, std::string filename);
    bool isSolid(int x,int y)const;
    FillType getType(int x,int y)const;
    void fillWith(int x,int y,FillType fillType);
    std::string toString();
    const std::vector<std::vector<FillType>>& getVec()const;
    void loadMap(std::string filename="map.dat");
private:
    int width,height;
    std::vector<std::vector<FillType>> mapVV;

};

#endif // MAPDATA_H
