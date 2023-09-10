#include "choosenandu.h"
#include<QPainter>
#include"mypushbuttom.h"
#include"QMessageBox"
#include"QDir"
int turn=1;

Dengji::Dengji(QString Image,NANDU denji,QMainWindow &m, BigCube* bigcube,Mylabel* player_info):MyPushButtom(Image){
    int jieshu=0;
    int geshu=0;
    switch (denji) {
    case EASY: jieshu=3;
          geshu=6;
          break;
    case MEDIUM:jieshu=4;
          geshu=7;
          break;
    case HARD:jieshu=5;
          geshu=8;
          break;
    }
    connect(this,&MyPushButtom::clicked,[&]()mutable{
        zoom1();
        zoom2();
        bigcube=new BigCube(Init_3D(jieshu,geshu),denji,1);
        m.hide();
       bigcube->show();

        connect(bigcube,&BigCube::returnback,[&](){
            qDebug()<<"get returnback";
            m.hide();
            bigcube->hide();
            //m.show();
            player_info->show_info();});
        connect(bigcube,&BigCube::nextCube,[&]()mutable{
            bigcube=new BigCube(Init_3D(jieshu+1,geshu+1),denji,2);
         bigcube->show();

            connect(bigcube,&BigCube::nextCube,[&](){
                //两局以后本模式结束
                QMessageBox* success=new QMessageBox(this);

                m.show();
                player_info->show_info();


                success->information(this,"tip","恭喜你，完成了本模式的所有关卡！\n点击 ok 重新选选择难度等级吧！");
                bigcube->board->timer->stop();

            });

       });


    });
}
Choosenandu::Choosenandu(QWidget *parent) : QMainWindow(parent)
{
    //基本设置
        setFixedSize(1200,800);

        setWindowIcon(QIcon(":/pic/icon.png"));

        setWindowTitle("索玛秘图");
    //玩家信息
        player_info=new Mylabel(this);
        //player_info->setParent(this);
        // player_info->move(this->width()*0.8-player_info->width(),0);
        player_info->cur_player=cur_player;
        player_info->show_info();


        //设置返回按钮
        MyPushButtom * tuichubtn=new MyPushButtom(":/pic/tuichu.png");

        tuichubtn->setParent(this);

        tuichubtn->move(this->width()*0.92-tuichubtn->width()*0.5,this->height()*0.88);

        connect(tuichubtn,&MyPushButtom::clicked,[=](){
        tuichubtn->zoom1();
        tuichubtn->zoom2();

        emit this->clickBack();

        });

       //三个等级按钮
//       //  cubeArray.resize(5);
//         easy=new Dengji(":/pic/jiandan.png",EASY,*this,this->bigcube,this->player_info);
// easy->setParent(this);
// easy->move(this->width()*0.5-easy->width()*0.5,this->height()*0.3);

  //     medium=new Dengji(":/pic/zzhongdeng.png",MEDIUM,*this,this->bigcube,this->player_info);

//        medium->setParent(this);
//        medium->move(this->width()*0.5-medium->width()*0.5,this->height()*0.45);

//        hard=new Dengji(":/pic/kunnan.png",HARD,*this,this->bigcube,this->player_info);

//        hard->setParent(this);
//        hard->move(this->width()*0.5-hard->width()*0.5,this->height()*0.6);

        //        MyPushButtom* easy=new MyPushButtom(":/pic/jiandan.png");
//        easy->setParent(this);
//        easy->move(this->width()*0.5-easy->width()*0.5,this->height()*0.3);
//        connect(easy,&MyPushButtom::clicked,[=](){
//            easy->zoom1();
//            easy->zoom2();
//            bigcube=new BigCube(Init_3D(3,6),EASY,1);
//            bigcube->show();
//            this->hide();
//            connect(this->bigcube,&BigCube::returnback,[=](){
//                qDebug()<<"get returnback";
//                this->show();
//                this->player_info->show_info();});
//            connect(bigcube,&BigCube::nextCube,[=](){
//                bigcube=new BigCube(Init_3D(3,7),EASY,2);
//                bigcube->show();

//                connect(bigcube,&BigCube::nextCube,[=](){
//                    //两局以后简单模式结束
//                    QMessageBox* success=new QMessageBox(this);

//                    this->show();
//                    player_info->show_info();


//                    success->information(this,"tip","恭喜你，完成了简单模式的所有关卡！\n点击 ok 重新选选择难度等级吧！");


//                });

//            });


//        });


        MyPushButtom* medium=new MyPushButtom(":/pic/zzhongdeng.png");
        medium->setParent(this);
        medium->move(this->width()*0.5-medium->width()*0.5,this->height()*0.45);

        connect(medium,&MyPushButtom::clicked,[=](){
        medium->zoom1();
        medium->zoom2();
        bigcube=new BigCube(Init_3D(4),MEDIUM,1);
        bigcube->show();
        this->hide();
        connect(this->bigcube,&BigCube::returnback,[=](){
            qDebug()<<"get returnback";
            this->show();
            this->player_info->show_info();});
        connect(bigcube,&BigCube::nextCube,[=](){
            bigcube=new BigCube(Init_3D(4),MEDIUM,2);
            bigcube->show();

            connect(bigcube,&BigCube::nextCube,[=](){
                //两局以后模式结束
                QMessageBox* success=new QMessageBox(this);

                this->show();
                player_info->show_info();


                success->information(this,"tip","恭喜你，完成了本模式的所有关卡！\n点击 ok 重新选选择难度等级吧！");
            bigcube->board->timer->stop();

            });

        });

        });

        MyPushButtom* easy=new MyPushButtom(":/pic/jiandan.png");
               easy->setParent(this);
               easy->move(this->width()*0.5-easy->width()*0.5,this->height()*0.3);
               connect(easy,&MyPushButtom::clicked,[=](){
                   easy->zoom1();
                   easy->zoom2();
                   bigcube=new BigCube(Init_3D(3,6),EASY,1);
                   bigcube->show();
                   this->hide();
                   connect(this->bigcube,&BigCube::returnback,[=](){
                       qDebug()<<"get returnback";
                       this->show();
                       this->player_info->show_info();});
                   connect(bigcube,&BigCube::nextCube,[=](){
                       bigcube=new BigCube(Init_3D(3,7),EASY,2);
                       bigcube->show();

                       connect(bigcube,&BigCube::nextCube,[=](){
                           //两局以后简单模式结束
                           QMessageBox* success=new QMessageBox(this);

                           this->show();
                           player_info->show_info();


                           success->information(this,"tip","恭喜你，完成了简单模式的所有关卡！\n点击 ok 重新选选择难度等级吧！");
                       bigcube->board->timer->stop();

                       });

                   });


               });





        MyPushButtom* hard=new MyPushButtom(":/pic/kunnan.png");
        hard->setParent(this);
        hard->move(this->width()*0.5-hard->width()*0.5,this->height()*0.6);
        connect(hard,&MyPushButtom::clicked,[=](){
        hard->zoom1();
        hard->zoom2();
        bigcube=new BigCube(Init_3D(4),HARD,1);
        bigcube->show();
        this->hide();
        connect(this->bigcube,&BigCube::returnback,[=](){
            qDebug()<<"get returnback";
            this->show();
            this->player_info->show_info();});
        connect(bigcube,&BigCube::nextCube,[=](){
            bigcube=new BigCube(Init_3D(4),HARD,2);
            bigcube->show();

            connect(bigcube,&BigCube::nextCube,[=](){
                //两局以后简单模式结束
                QMessageBox* success=new QMessageBox(this);

                this->show();
                player_info->show_info();


                success->information(this,"tip","恭喜你，完成了困难模式的所有关卡！\n点击 ok 重新选选择难度等级吧！");
                    bigcube->board->timer->stop();

            });

        });

        });






}


//void Choosenandu::myslots(){
//    if(turn<4){
//          cubeArray[turn]=new BigCube(Init_3D(3,5+turn),EASY,turn);
//       // bigcube=new BigCube(Init_3D(3,6+turn),EASY,turn+1);
//        //connect(bigcube,&BigCube::nextCube,[=](){this->myslots();});
//        this->hide();
//        cubeArray[turn]->show();


//    }
//    else{
//        QMessageBox* success=new QMessageBox(this);
//        success->information(this,"tip","恭喜你，完成了简单模式的所有关卡！\n点击 ok 进入下一个等级叭！");

//    }
//}
void Choosenandu::paintEvent(QPaintEvent* ) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/nandu.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/pic/kuang.png");
    //pix=pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(this->width()*0.38,this->height()*0.2,pix.width(),pix.height(),pix);
   qDebug()<<" painter";


}
