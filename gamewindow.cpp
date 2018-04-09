#include "gamewindow.h"
#include "ui_gamewindow.h"

#include"gamewidget.h"
#include<thread>
#include<QVBoxLayout>
#include<unistd.h>
#include<QDebug>
#include<QFileDialog>
std::string GameWindow::defaultMap="map.dat";
GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),game(new Game(defaultMap)),
    threadCreated(false){
    ui->setupUi(this);
    setCentralWidget(ui->centralWidget);
    GameWidget *gameWidget=new GameWidget(game);
    QVBoxLayout *mLayout=new QVBoxLayout();
    mLayout->addWidget(gameWidget);
    ui->centralWidget->setLayout(mLayout);
}
GameWindow::~GameWindow(){delete ui;}
void GameWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_P){
        if(threadCreated){
            game->stop();
            threadCreated=false;
        }else{
            std::thread t(Game::start,game,this);
            t.detach();
            threadCreated=true;
        }
    }else if(threadCreated)game->input(event->key());
}
void GameWindow::on_actionNew_triggered(){
    game->stop();
    sleep(1);
    delete game;
    threadCreated=false;
    game=new Game(defaultMap);
    update();
}
void GameWindow::on_actionMap_triggered(){
    QFileDialog *chooseMap=new QFileDialog(this);
    chooseMap->setDirectory(".");
    chooseMap->setFileMode(QFileDialog::ExistingFile);
    chooseMap->setNameFilter("Map File (*.dat *.txt)");
    chooseMap->exec();
    QStringList map=chooseMap->selectedFiles();
    QString m=map.at(0);
    defaultMap=m.toStdString();
    game->stop();
    sleep(1);
    delete game;
    threadCreated=false;
    game=new Game(defaultMap);
    update();
}
