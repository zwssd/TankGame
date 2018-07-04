#include "mapdata.h"
#include<QPixmap>
#include<QDebug>
#include<QPainter>
#include<fstream>
#include"settings.h"
#include"math.h"
MapData::MapData(int width,int height,std::string filename)
    :width(width),height(height){
    loadMap(filename);
}

void MapData::draw(QPainter &pen){

    QPixmap pic;
    for(unsigned y=0;y<mapVV.size();++y){
        for(unsigned x=0;x<mapVV[0].size();++x){
            switch (mapVV[y][x]) {
            case FillType::NOTHING:
                pic.load(":/image/res/blank.gif");
                break;
            case FillType::WALL:
                pic.load(":/image/res/normal.gif");
                break;
            case FillType::GRASS:
                pic.load(":/image/res/blank.gif");  //cao yeshi blank!
                break;
            case FillType::STEEL:
                pic.load(":/image/res/steel.gif");
                break;
            case FillType::WATER:
                pic.load(":/image/res/water.gif");
                break;
            default :
                pic.load(":/image/res/blank.gif");
                break;
            }
            pen.drawPixmap(x*Settings::blockLength,
                           y*Settings::blockLength,
                           Settings::blockLength,
                           Settings::blockLength,
                           pic);
        }

    }
}
void MapData::drawGrass(QPainter &pen){
    QPixmap pic;
    pic.load(":/image/res/grass.gif");

    for(unsigned y=0;y<mapVV.size();++y){
        for(unsigned x=0;x<mapVV[0].size();++x){
            if(mapVV[y][x]==FillType::GRASS) {
                pen.drawPixmap(x*Settings::blockLength,
                               y*Settings::blockLength,
                               Settings::blockLength,
                               Settings::blockLength,
                               pic);
            }
        }
    }
}

bool MapData::isSolid(int x,int y)const{
    double dx = x,dy = y;
    double dbL = Settings::blockLength;
    int xx,yy;
    xx = ceil(dx/dbL);
    yy = ceil(dy/dbL);
    if(xx>19)xx=19;
    if(yy>19)yy=19;
        qDebug()<<"x="<<x;
        qDebug()<<"y="<<y;
        qDebug()<<"x/Settings::blockLength="<<x/Settings::blockLength;
        qDebug()<<"y/Settings::blockLength="<<y/Settings::blockLength;
        qDebug()<<"ceil(x/Settings::blockLength)="<<ceil(dx/dbL);
        qDebug()<<"ceil(y/Settings::blockLength)="<<ceil(dy/dbL);
    if(x<0||x>=width*Settings::blockLength||y<0||y>=height*Settings::blockLength)return true;
    switch (mapVV[yy][xx]) {
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
void MapData::loadMap(std::string filename){
    std::ifstream map(filename);
    loadMap(map);
    map.close();
}
void MapData::loadMap(std::ifstream &in){
    int dat;
    for(int i=0;i<height;++i){
        std::vector<FillType> row;
        for(int j=0;j<width;++j){
            in>>dat;
            row.push_back(intToFill(dat));
        }
        mapVV.push_back(row);
    }
}

FillType MapData::getType(int x, int y) const{
    if(x<0||y<0||x>=width||y>=height){
        return FillType::NOTHING;
    }
    return mapVV[y][x];
}
