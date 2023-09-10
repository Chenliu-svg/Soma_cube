#ifndef CHOOSENANDU_H
#define CHOOSENANDU_H

#include <QMainWindow>
#include<QLabel>
#include"bigcube.h"
#include"global.h"


class Dengji:public MyPushButtom
{
    Q_OBJECT
public:
    Dengji(QString Image,NANDU denji,QMainWindow &m,BigCube* bigcube,Mylabel* player_info);
};

class Choosenandu : public QMainWindow
{
    Q_OBJECT
public:
    explicit Choosenandu(QWidget *parent = nullptr);
    Mylabel* player_info=0;
    void paintEvent(QPaintEvent* ) override;
    BigCube* bigcube=0;
//     Dengji* easy;
//     Dengji* medium;
//     Dengji* hard;
    //QVector<BigCube> cubeArray;
    //Player* cur_player=0;
//public slots:
//    void myslots();


signals:
void clickBack();

//public slots:
//void nextgame();
};

#endif // CHOOSENANDU_H
