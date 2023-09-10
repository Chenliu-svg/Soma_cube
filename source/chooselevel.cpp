#include "chooselevel.h"
#include"mypushbuttom.h"
#include<QFile>
#include<QLineEdit>
#include<QComboBox>
#include<QMessageBox>
#include<QTextStream>
#include<QStandardItemModel>
#include<QTimer>
#include<algorithm>
using  std::string;
QString file0=QDir::currentPath()+"/"+"Player.txt";

Player* cur_player=0;

ChooseLevel::ChooseLevel(QWidget *parent) : QMainWindow(parent)
{
    //基本配置
    setFixedSize(1200,800);

    setWindowIcon(QIcon(":/pic/icon.png"));

    setWindowTitle("选择关卡");


    //设置返回按钮
    MyPushButtom * tuichubtn=new MyPushButtom(":/pic/tuichu.png");

    tuichubtn->setParent(this);

    tuichubtn->move(this->width()*0.92-tuichubtn->width()*0.5,this->height()*0.88);

    connect(tuichubtn,&MyPushButtom::clicked,[=](){
    tuichubtn->zoom1();
    tuichubtn->zoom2();
    emit this->clickBack();

    });
    //先在文本框中输入用户名，点击以后添加

    QLineEdit* line=new QLineEdit(this);

    line->setFixedSize(QSize(this->width()*0.2,this->height()*0.05));
    line->move(this->width()*0.5-line->width()*0.5,this->height()*0.4);
        //点击下拉框的按钮获得用户名
        choose_player=new QComboBox(this);
        choose_player->resize(QSize(this->width()*0.2,this->height()*0.05));
        choose_player->move(this->width()*0.5-line->width()*0.5,this->height()*0.5);



    //初始化玩家列表
    //读取玩家文件
    QFile *file = new QFile (file0);
    qDebug()<<QDir::currentPath()+"/"+"Player.txt";
    file->open(QIODevice::ReadOnly);
    if(!file->isOpen()){
        qDebug()<<"Player file open fail.";
    }
    // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    QByteArray array;
    int index_id;
    int the_id;
    int index_name;
    QString the_name;
    int the_score;
    while(!file->atEnd()){
        array=file->readLine();
        index_id=array.indexOf(';');
        index_name=array.lastIndexOf(';');
        the_id=array.left(index_id).toInt();
        the_name=QString::fromLocal8Bit(array.mid(index_id+1,index_name-index_id-1));
       the_score=array.mid(index_name+1,array.length()-index_name-2).toInt();

        Player * newPlayer=new Player();
        newPlayer->id=the_id;
        newPlayer->setName(the_name);
        newPlayer->setScore(the_score);
        //加入列表中
        PlayerList.push_back(newPlayer);

    }
    file->close();
   update_line();
   display_rank();
//    //先在文本框中输入用户名，点击以后添加

//    QLineEdit* line=new QLineEdit(this);

//    line->setFixedSize(QSize(this->width()*0.2,this->height()*0.05));
//    line->move(this->width()*0.5-line->width()*0.5,this->height()*0.4);

    MyPushButtom * addbtn=new MyPushButtom(":/pic/addplayer.png");

    addbtn->setParent(this);

    addbtn->move(this->width()*0.61,this->height()*0.41);

    connect(addbtn,&MyPushButtom::clicked,[=](){
    addbtn->zoom1();
    addbtn->zoom2();
    //不可添加重名的玩家
    QString curname=line->text();
    int flag=0;
    for(int i=0;i<PlayerList.count();i++){
        if(curname==PlayerList[i]->getName()){
            QMessageBox* warning=new QMessageBox(this);

            warning->information(this,"tip","该玩家已经存在:D\n可以在玩家列表中直接选择该玩家");
            flag=1;
            break;
        }
    }
    if(flag==0){this->addNewPlayer(curname);
         choose_player->addItem(curname);
              QStandardItemModel * model = qobject_cast<QStandardItemModel*>(choose_player->model());
              for (int i = 0; i < model->rowCount(); ++i)
              {
                  QStandardItem * item = model->item(i);
                  item->setSizeHint({ 0, 45 });

              }
    QMessageBox* inform=new QMessageBox(this);
    inform->information(this,"tip","成功创建玩家:P\n可以在玩家列表中直接选择该玩家",QMessageBox::Close);
    }
    display_rank();
 //update_line();

    });

    //查看排行榜
        MyPushButtom * rankbtn=new MyPushButtom(":/pic/ranklist.png");

        rankbtn->setParent(this);

        rankbtn->move(this->width()*0.5-rankbtn->width()*0.5,this->height()*0.6);

        connect(rankbtn,&MyPushButtom::clicked,[=](){
        rankbtn->zoom1();
        rankbtn->zoom2();
      this->hide();

      rank=new ranklist(this->PlayerList);
      rank->show();
      connect(rank,&ranklist::clickBack,[=](){
          QTimer::singleShot(500,this,[=](){
         rank->hide();//隐藏选择关卡场景
         this->show();
      });

      });

        });


//    //点击下拉框的按钮获得用户名
//    choose_player=new QComboBox(this);
//    choose_player->resize(QSize(this->width()*0.2,this->height()*0.05));
//    choose_player->move(this->width()*0.5-line->width()*0.5,this->height()*0.5);
//     for(int i=0;i<PlayerList.count();i++){
//         choose_player->addItem(PlayerList[i]->getName());
//     }

//     QStandardItemModel * model = qobject_cast<QStandardItemModel*>(choose_player->model());
//     for (int i = 0; i < model->rowCount(); ++i)
//     {
//         QStandardItem * item = model->item(i);
//         item->setSizeHint({ 0, 45 });

//     }


     //根据选择的用户名初始化玩家


     connect(choose_player, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
           [=](int index){
         for(int i=0;i<PlayerList.size();i++){
             if(index==PlayerList[i]->id){

                 cur_player=PlayerList[i];
                  choosenandu=new Choosenandu();
                  connect(choosenandu,&Choosenandu::clickBack,[=](){
                      //实现延时退出效果
                      qDebug()<<"get it";
                      QTimer::singleShot(400,this,[=](){


                          //将当前玩家分数写回

                          for(int i=0;i<PlayerList.size();i++){
                              if(PlayerList[i]->id==cur_player->id){

                                  PlayerList[i]->setScore(cur_player->getScore());}
                          }
                           QFile file(file0);

                          file.open(QIODevice::ReadWrite | QIODevice::Truncate);
                          QTextStream fileOut(&file);
                          for(int i=0;i<PlayerList.count();i++){
                              fileOut<<PlayerList[i]->id<<';'<<PlayerList[i]->getName()<<';'<<PlayerList[i]->getScore()<<endl;
                          }

                          file.close();
                          choosenandu->hide();
                          this->show();
                          display_rank();
                          });

                  }



                  );
                 //choosenandu->cur_player=cur_player;
                // qDebug()<<cur_player->id<<'\t'<<cur_player->getName()<<'\t'<<cur_player->getScore();
                 break;
             }

         }



    //进入选择难度窗口
          this->hide();
          choosenandu->show();




     });






}

void ChooseLevel::update_line(){
    for(int i=0;i<PlayerList.count();i++){
        choose_player->addItem(PlayerList[i]->getName());
    }

    QStandardItemModel * model = qobject_cast<QStandardItemModel*>(choose_player->model());
    for (int i = 0; i < model->rowCount(); ++i)
    {
        QStandardItem * item = model->item(i);
        item->setSizeHint({ 0, 45 });

    }
}
void ChooseLevel::display_rank(){
    for(int i=0;i<PlayerList.count();i++){
        qDebug()<<PlayerList[i]->id<<'\t'<<PlayerList[i]->getName()<<'\t'<<PlayerList[i]->getScore();
    }

}


void ChooseLevel::addNewPlayer(QString s_name){
    Player * newPlayer=new Player();
    newPlayer->id=this->PlayerList.count();
    newPlayer->setScore(0);
    newPlayer->setName(s_name);
    //加入列表中
    PlayerList.push_back(newPlayer);

    //否则直接追加到文件尾部
    QFile file(file0);
    file.open(QIODevice::Append);

    QTextStream txtOutput(&file);

    txtOutput <<newPlayer->id<<';'<<newPlayer->getName()<<';'<<newPlayer->getScore()<<endl;

    file.close();
}

void ChooseLevel::paintEvent(QPaintEvent* ) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/chooselevel.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/pic/player.png");
    pix=pix.scaled(pix.width(),pix.height());
    painter.drawPixmap(this->width()*0.38,this->height()*0.2,pix.width(),pix.height(),pix);


}

