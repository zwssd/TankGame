#include "gamewidget.h"
#include "ui_gamewidget.h"
#include<QPixmap>
#include<QPainter>
#include<filltype.h>
#include<QDebug>
#include<stdexcept>
#include"settings.h"
GameWidget::GameWidget(Game* game,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget),game(game){
    ui->setupUi(this);
}
GameWidget::~GameWidget(){delete ui;}
void GameWidget::paintEvent(QPaintEvent *){
    QPainter pen(this);
    game->draw(pen);
}
