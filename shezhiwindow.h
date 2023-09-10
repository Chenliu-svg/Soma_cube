#ifndef SHEZHIWINDOW_H
#define SHEZHIWINDOW_H
#include <QMediaPlayer>
#include<QPainter>
#include <QMainWindow>
#include <QSound>
#include<QMediaPlaylist>
#include"mypushbuttom.h"
#include<QSpinBox>
#include<QSlider>
#include<QFile>
class ShezhiWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ShezhiWindow(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent* ) override;
    QMediaPlaylist *playlist;
QMediaPlayer *music;
signals:
void clickBack();
};

#endif // SHEZHIWINDOW_H
