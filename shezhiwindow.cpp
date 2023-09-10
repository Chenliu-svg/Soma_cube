#include "shezhiwindow.h"

ShezhiWindow::ShezhiWindow(QWidget *parent) : QMainWindow(parent)
{
    //基本设置
        setFixedSize(300,500);

        setWindowIcon(QIcon(":/pic/icon.png"));

        setWindowTitle("索玛秘图");


        //背景音乐设置
        playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl("qrc:/pic/background.mp3"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        music = new QMediaPlayer();
        music->setPlaylist(playlist);
        music->play();


        //暂停按钮
        MyPushButtom* zantin=new MyPushButtom(":/pic/zantin.png");
        zantin->setParent(this);
        zantin->move(this->width()*0.5-zantin->width()*0.5,this->height()*0.4);
        connect(zantin,&MyPushButtom::clicked,[=](){
        zantin->zoom1();
        zantin->zoom2();
        this->music->stop();});

        //播放按钮
        MyPushButtom* bofang=new MyPushButtom(":/pic/bofang.png");
        bofang->setParent(this);
        bofang->move(this->width()*0.5-bofang->width()*0.5,this->height()*0.6);
        connect(bofang,&MyPushButtom::clicked,[=](){
        bofang->zoom1();
        bofang->zoom2();
        this->music->play();});

        //音量调节
        int nMin = 0;
        int nMax = 100;
        int nSingleStep = 5;

        // 微调框
        QSpinBox *pSpinBox = new QSpinBox(this);
        pSpinBox->setMinimum(nMin);  // 最小值
        pSpinBox->setMaximum(nMax);  // 最大值
        pSpinBox->setSingleStep(nSingleStep);  // 步长
        pSpinBox->move(this->width()*0.2,this->height()*0.28);
        pSpinBox->resize(this->width()*0.2,this->height()*0.05);

        // 滑动条
        QSlider *pSlider = new QSlider(this);
        pSlider->setOrientation(Qt::Horizontal);  // 水平方向
        pSlider->setMinimum(nMin);  // 最小值
        pSlider->setMaximum(nMax);  // 最大值
        pSlider->setSingleStep(nSingleStep);
        // 步长
       pSlider->resize(this->width()*0.5,this->height()*0.05);
        pSlider->move(this->width()*0.4,this->height()*0.28);


       //更改样式
       QString qss;
       QFile qssFile(":/pic/myqss.qss");
          qssFile.open(QFile::ReadOnly);

          if(qssFile.isOpen())
          {
              qss = QLatin1String(qssFile.readAll());
              pSlider->setStyleSheet(qss);
              qssFile.close();
          }


        // 连接信号槽（相互改变）


        connect(pSpinBox, SIGNAL(valueChanged(int)), pSlider, SLOT(setValue(int)));
        connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));
        connect(pSlider,&QSlider::valueChanged,[=](){
            this->music->setVolume(pSpinBox->value());}
        );
        pSpinBox->setValue(50);


}
void ShezhiWindow::paintEvent(QPaintEvent* ) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/nandu.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/pic/yinliang.png");
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(this->width()*0.35,this->height()*0.1,pix.width(),pix.height(),pix);



}
