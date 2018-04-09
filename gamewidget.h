#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include"game.h"
namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(Game* game,QWidget *parent = 0);
    ~GameWidget();
    void paintEvent(QPaintEvent *event)override;
private:
    Ui::GameWidget *ui;
    Game *game;
    void drawMap();
    void drawTank(Tank& tank);
    void drawGrass();
};

#endif // GAMEWIDGET_H
