#include "gamewidget.h"
#include "ui_gamewidget.h"
#include<QPixmap>
#include<QPainter>
#include<filltype.h>
#include"settings.h"
GameWidget::GameWidget(Game* game,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget),game(game){
    ui->setupUi(this);
}
GameWidget::~GameWidget(){delete ui;}
void GameWidget::paintEvent(QPaintEvent *){
    drawMap();
    drawTank(game->getPlayer());
    for(Tank& e:game->getEnemy()){
        drawTank(e);
    }
    drawGrass();
}
void GameWidget::drawMap(){
    QPainter pen(this);
    QPixmap pic;
    auto mapVV=game->getMapData().getVec();
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
void GameWidget::drawGrass(){
    QPainter pen(this);
    QPixmap pic(":/image/res/grass.gif");
    auto mapVV=game->getMapData().getVec();
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
void GameWidget::drawTank(Tank& tank){
    QPainter pen(this);
    QPixmap pic;
    switch (tank.getType()) {
    case TankType::PLAYER:
        pic.load(":/image/res/player.gif");
        break;
    case TankType::ENERMY:
        pic.load(":/image/res/enemy.gif");
        break;
    default:
        break;
    }
    QMatrix r;
    switch (tank.getDirection()) {
    case Direction::RIGHT:
        r.rotate(90);
        break;
    case Direction::DOWN:
        r.rotate(180);
        break;
    case Direction::LEFT:
        r.rotate(270);
        break;
    default:
        break;
    }
    pen.drawPixmap(tank.getX()*Settings::blockLength,
                   tank.getY()*Settings::blockLength,
                   2*Settings::blockLength,
                   2*Settings::blockLength,
                   pic.transformed(r));
    Bullet* bullet=tank.getBullet();
    if(bullet!=nullptr){
        pic.load(":/image/res/bullet.gif");
        pen.drawPixmap(bullet->getX()-Settings::bulletSize/2,
                       bullet->getY()-Settings::bulletSize/2,
                       Settings::bulletSize,Settings::bulletSize,
                       pic);
    }
}
