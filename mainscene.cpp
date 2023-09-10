#include "mainscene.h"
#include "ui_mainscene.h"
#include"mypushbuttom.h"
#include<QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

//基本设置
    setFixedSize(1200,800);

    setWindowIcon(QIcon(":/pic/icon.png"));

    setWindowTitle("索玛秘图");


    chooselevel=new ChooseLevel();


    //监听选择关卡的返回按钮信号
    connect(chooselevel,&ChooseLevel::clickBack,[=](){
         QTimer::singleShot(500,this,[=](){
        chooselevel->hide();//隐藏选择关卡场景
        this->show();
     });
    });





//游戏模式按钮
    MyPushButtom * startbtn=new MyPushButtom(":/pic/game.png");



    startbtn->setParent(this);

    startbtn->move(this->width()*0.8-startbtn->width()*0.5,this->height()*0.35);

    connect(startbtn,&MyPushButtom::clicked,[=](){
        //实现弹跳效果
    startbtn->zoom1();
    startbtn->zoom2();

    //实现延时退出效果
    QTimer::singleShot(500,this,[=](){
        this->hide();
        chooselevel->show();
        });

    });


//工具模式按钮

    MyPushButtom * toolbtn=new MyPushButtom(":/pic/toolmode.png");

    toolbtn->setParent(this);

    toolbtn->move(this->width()*0.8-toolbtn->width()*0.5,this->height()*0.45);

    connect(toolbtn,&MyPushButtom::clicked,[=](){
    toolbtn->zoom1();
    toolbtn->zoom2();
    QTimer::singleShot(500,this,[=](){
        this->hide();
         toolwindow=new ToolWindow();

         connect(toolwindow,&ToolWindow::clickBack,[=](){
              QTimer::singleShot(500,this,[=](){
             toolwindow->hide();//隐藏选择关卡场景
             this->show();
          });
         });
        toolwindow->show();
    });

    });



//设置模式按钮
    shezhiwindow=new ShezhiWindow();

    connect(shezhiwindow,&ShezhiWindow::clickBack,[=](){
         QTimer::singleShot(500,this,[=](){
        shezhiwindow->hide();//隐藏选择关卡场景
        this->show();
     });
    });
    MyPushButtom * sehzhibtn=new MyPushButtom(":/pic/shezhi.png");

    sehzhibtn->setParent(this);

    sehzhibtn->move(this->width()*0.8-sehzhibtn->width()*0.5,this->height()*0.55);

    connect(sehzhibtn,&MyPushButtom::clicked,[=](){
    sehzhibtn->zoom1();
    sehzhibtn->zoom2();


    QTimer::singleShot(500,this,[=](){

       shezhiwindow->show();
    });
    });

//退出按钮
    MyPushButtom * tuichubtn=new MyPushButtom(":/pic/tuichu.png");

    tuichubtn->setParent(this);

    tuichubtn->move(this->width()*0.92-tuichubtn->width()*0.5,this->height()*0.88);

    connect(tuichubtn,&MyPushButtom::clicked,[=](){
    tuichubtn->zoom1();
    tuichubtn->zoom2();


    QTimer::singleShot(500,this,[=](){
        this->close();

    });
    });
}


void MainScene::paintEvent(QPaintEvent* ev) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/mainscene.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/pic/标题.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(800,100,pix.width(),pix.height(),pix);



}

MainScene::~MainScene()
{
    delete ui;
}

