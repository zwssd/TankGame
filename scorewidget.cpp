#include "scorewidget.h"
#include "ui_scorewidget.h"
#include<string>
ScoreWidget::ScoreWidget(Game *game, QWidget *parent) :

    QWidget(parent),
    ui(new Ui::ScoreWidget),
    game(game){
    ui->setupUi(this);

}

ScoreWidget::~ScoreWidget()
{
    delete ui;
}

void ScoreWidget::paintEvent(QPaintEvent *){
    int i=game->getAllEnemy();
    QString remain(QString::fromStdString(
                       "剩余敌人数目:<b>"+std::to_string(i)+"</b>"));
    ui->remain->setText(remain);
    ui->remain->setWordWrap(true);
    ui->score->setText(
                QString::fromStdString(
                    "defen<b>:"+std::to_string(100)+"</b>"
                    )
                );
}
