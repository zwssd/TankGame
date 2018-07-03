#include "gamewindow.h"
#include "ui_gamewindow.h"

#include"gamewidget.h"
#include"scorewidget.h"
#include<thread>
#include<QVBoxLayout>
#include<unistd.h>
#include<QDebug>
#include<QFileDialog>
std::string GameWindow::defaultMap="map.dat";
GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),game(new Game(defaultMap)){
    ui->setupUi(this);
    setCentralWidget(ui->centralWidget);
    GameWidget *gameWidget=new GameWidget(game);

    ScoreWidget *scoreWidget=new ScoreWidget(game);

    scoreWidget->setMaximumSize(100,500);
    QHBoxLayout *mLayout=new QHBoxLayout();
    mLayout->addWidget(gameWidget);
    mLayout->addWidget(scoreWidget);
    ui->centralWidget->setLayout(mLayout);
}
GameWindow::~GameWindow(){delete ui;}
void GameWindow::keyPressEvent(QKeyEvent *event){
    if(game==nullptr)return;
    if(event->key()==Qt::Key_P){
        if(game->getIsStarted()){
            game->stop();
        }else{
            std::thread t(Game::start,game,this);
            t.detach();
        }
    }else if(game->getIsStarted()){
        qDebug()<<"in";
        game->input(event->key());
    }
}
void GameWindow::on_actionNew_triggered(){
    game->stop();
    sleep(1);
    delete game;
    qDebug()<<"=====>>>>>";
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
    game=new Game(defaultMap);
    update();
}
