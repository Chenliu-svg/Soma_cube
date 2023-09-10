#include "mypushbuttom.h"

MyPushButtom::MyPushButtom(QWidget *parent) :QPushButton(parent)
{

}


MyPushButtom::MyPushButtom(QString normalImage,QString pressImage){
    normalImagePath=normalImage;
    pressedImagePath=pressImage;
    QPixmap pixmap;
    bool ret=pixmap.load(normalImagePath);
    if(!ret){
        qDebug()<<normalImage<<"加载失败！";
    }
    this->setFixedSize(pixmap.width()*0.8,pixmap.height()*0.8);

    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pixmap);

    this->setIconSize(QSize(pixmap.width()*0.8,pixmap.height()*0.8));

    if(pressedImagePath!=""){
        connect(this,&MyPushButtom::clicked,[=](){
              QPixmap pixmap1;
            bool ret=pixmap1.load(pressedImagePath);
            if(!ret){
                qDebug()<<normalImage<<"加载失败！";
            }
            this->setFixedSize(pixmap1.width()*0.8,pixmap1.height()*0.8);

            this->setStyleSheet("QPushButton{border:0px;}");

            this->setIcon(pixmap1);

            this->setIconSize(QSize(pixmap1.width()*0.8,pixmap1.height()*0.8));

        });
    }
}


void MyPushButtom::zoom1(){
    QPropertyAnimation * ani=new QPropertyAnimation(this,"geometry");
    QMediaPlayer *player = new QMediaPlayer(this);//设置背景音乐
    player->setMedia(QUrl("qrc:/pic/弹跳.wav"));

    player->setVolume(50);//音量

    player->play();

    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

}

void MyPushButtom::zoom2(){
    QPropertyAnimation * ani=new QPropertyAnimation(this,"geometry");

    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();
}
