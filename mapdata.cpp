#include "mapdata.h"
#include<QPixmap>
#include<QPainter>
#include<fstream>
MapData::MapData(int width,int height,std::string filename)
    :width(width),height(height){
    loadMap(filename);
}
bool MapData::isSolid(int x,int y)const{
    if(x<0||x>=width||y<0||y>=height)return true;
    switch (mapVV[y][x]) {
    case FillType::NOTHING:
    case FillType::GRASS:
        return false;
    case FillType::WALL:
    case FillType::STEEL:
    case FillType::WATER:
        return true;
    default:
        return true;
    }
}
void MapData::fillWith(int x, int y, FillType fillType){
    if(x>=0&&x<width&&y>=0&&y<height)
        mapVV[y][x]=fillType;
}
std::string MapData::toString(){
    std::string s;
    for(int i=0;i<height;++i){
        for(int j=0;j<width;++j){
            s.push_back(getFillSym((int)mapVV[i][j]));
        }
        s.push_back('\n');
    }
    return s;
}
const std::vector<std::vector<FillType>>& MapData::getVec() const{
    return mapVV;
}

void MapData::loadMap(std::string filename){
    std::ifstream map(filename);
    int dat;
    for(int i=0;i<height;++i){
        std::vector<FillType> row;
        for(int j=0;j<width;++j){
            map>>dat;
            row.push_back(intToFill(dat));
        }
        mapVV.push_back(row);
    }
    map.close();
}


FillType MapData::getType(int x, int y) const{
    if(x<0||y<0||x>=width||y>=height){
        return FillType::NOTHING;
    }
    return mapVV[y][x];
}
