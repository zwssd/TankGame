#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include"game.h"
#include<string>
#include<QKeyEvent>
namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event)override;

private:
    static std::string defaultMap;
    Ui::GameWindow *ui;
    Game *game;

    bool threadCreated;
private slots:
    void on_actionNew_triggered();
    void on_actionMap_triggered();
};

#endif // GAMEWINDOW_H
