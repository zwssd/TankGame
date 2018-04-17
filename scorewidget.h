#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>
#include"game.h"

namespace Ui {
class ScoreWidget;
}

class ScoreWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreWidget(Game* game,QWidget *parent = 0);
    ~ScoreWidget();
    void paintEvent(QPaintEvent *event)override;
private:

    Ui::ScoreWidget *ui;
    Game* game;
};

#endif // SCOREWIDGET_H
