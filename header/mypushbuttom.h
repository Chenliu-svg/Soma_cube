#ifndef MYPUSHBUTTOM_H
#define MYPUSHBUTTOM_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QMediaPlayer>
#include <QPropertyAnimation>
class MyPushButtom : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButtom(QWidget *parent = nullptr);
    MyPushButtom(QString normalImage,QString pressImage="");
    void zoom1();//向下跳跃
    void zoom2();//向上跳跃
    QString normalImagePath;
    QString pressedImagePath;

signals:




};

#endif // MYPUSHBUTTOM_H
