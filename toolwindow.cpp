#include "toolwindow.h"

#include"QMessageBox"
#include<fstream>

using namespace std;

ToolWindow::ToolWindow(QWidget *parent) : QMainWindow(parent)
{
    //基本设置
        setFixedSize(1200,800);

        setWindowIcon(QIcon(":/pic/icon.png"));

        setWindowTitle("索玛秘图");


        //设置返回按钮
        MyPushButtom * tuichubtn=new MyPushButtom(":/pic/tuichu.png");

        tuichubtn->setParent(this);

        tuichubtn->move(this->width()*0.92-tuichubtn->width()*0.5,this->height()*0.88);

        connect(tuichubtn,&MyPushButtom::clicked,[=](){
        tuichubtn->zoom1();
        tuichubtn->zoom2();
        emit this->clickBack();

        });
     //生成三个user_define，让用户画任意两个视图画，点击提交以后生成所有的可能，存入文件中
    //标签提示：请画出任意两个视图
       tip=new QLabel("请画出任意两个视图");
       tip->setParent(this);
       tip->resize(this->width()*0.25,this->height()*0.1);
       tip->move(this->width()*0.5-tip->width()*0.5,this->height()*0.08);
       tip->setStyleSheet(
                   "  font-family:STXingkai;"
                                  "font-size: 24px;"
                                  "color: #BDC8E2;"
                                  "font-style: normal;"
                                  "font-weight: normal;"

                                 " border-style: solid;"
                                  "border-width: 2px;"
                                 " border-color: aqua;"
                                 " border-radius: 20px;"

                                 " padding-left: 20px;"
                                 " padding-top: 0px;"

                                "  background-color: #2E3648;"

                                "  background-repeat: no-repeat;"
                                 " background-position: left center;"
                              );

//放三个user_define

       shitu=new User_define[3];
      for(int i=0;i<3;i++){
           shitu[i].setParent(this);}
          //qDebug()<<i%4<<" "<<i/3;
           shitu[0].move(this->width()*0.33-shitu[0].width()*0.5,this->height()*0.2);
           shitu[1].move(this->width()*0.66-shitu[0].width()*0.5,this->height()*0.2);
           shitu[2].move(this->width()*0.33-shitu[0].width()*0.5,this->height()*0.27+shitu[0].height());

       //点击提交按钮就将每个视图的show_view传入big 去 findall 然后在写入文件中
           MyPushButtom * tijiaobtn=new MyPushButtom(":/pic/tijiao.png");

           tijiaobtn->setParent(this);

           tijiaobtn->move(this->width()*0.66-tijiaobtn->width()*0.5,this->height()*0.6);
           connect(tijiaobtn,&MyPushButtom::clicked,[=](){
               tijiaobtn->zoom1();
               tijiaobtn->zoom2();
               //先判断是否合理
               if(rational()){
               Init_3D* a= new Init_3D(shitu[1].getshowview(),shitu[0].getshowview(),shitu[2].getshowview());
               big=new BigCube(*a);
              big->findall(*a);
               big->dispalyall();
               //存储生成的稀疏矩阵到cube 文件中
               big->writeall();
               randomDisplay();
               QTimer::singleShot(500,this,[=](){

                   QMessageBox* tips=new QMessageBox(this);
                   int num=big->init_array.size();
                   tips->information(this,"tip","生成的 "+QString::number(num)+" 个异形立方体已经全部保存到cube文件！\n 点击ok将随机展示其中的的一种 ");
                   //点击ok将随机展示其中的一种，
                   show_big();


                   //并随机画出11种展开图中的任何一种

                   Zhankaitu * test;
                   //test=new Step(show3DArray);
                    int r=qrand()%3;
                    switch (r) {
                    case 0: test=new Dog(show3DArray);
                        break;
                    case 1: test=new Step(show3DArray);
                        break;
                    case 2: test=new Gun(show3DArray);
                        break;


                    }
                    QTimer::singleShot(10000,this,[=](){
                     big->close();
                    test->show();});
              });
              }
               else{
                   QMessageBox* tip1=new QMessageBox(this);

                   tip1->information(this,"tip","视图绘制不合理，请重试！");

               }

           });




//    QVector<QVector<int>> l={{0,0,0},{0,1,0},{1,1,1}};
//    QVector<QVector<int>> f={{0,0,0},{1,0,0},{1,0,0}};
//    QVector<QVector<int>> top={{0,1,0},{0,1,0},{0,1,0}};

//  Init_3D* a= new Init_3D(l,f,top);
//   big=new BigCube(*a);
//  big->findall(*a);
//   big->dispalyall();
}
void ToolWindow::randomDisplay(){
    //以二进制的方式读出到 show3DArray
    int jieshu=this->big->init_array[0]->jieshu;
    show3DArray= QVector<QVector<QVector<int>>> (jieshu,QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0)));

    int num=this->big->init_array.size();

    int rand=qrand()%num;
    int start=0;

    for(int i=0;i<rand;i++){

        start+=this->big->init_array[i]->getsize();

    }
    int size=this->big->init_array[rand]->getsize();
    ifstream fin;
    fin.open(file1,ios::in|ios::binary);
    streampos place=start* sizeof(QVector3D);
    fin.seekg(place);//随机访问
    QVector3D p;
    while(size>0){
        fin.read((char*)&p,sizeof p);
       show3DArray[p.x()][p.y()][p.z()]=1;
       size--;

    }

    fin.close();




}
void ToolWindow::show_big(){
    big=new BigCube(this->show3DArray);
    //temp->setParent(this);
    big->show();
}
bool ToolWindow::rational(){

    int jieshu=this->shitu[0].getshowview().count();
    QVector<QVector<int>> zero_cmp(jieshu,QVector<int>(jieshu,0));
     QVector<QVector<int>> front=this->shitu[0].getshowview();

     QVector<QVector<int>> left=this->shitu[1].getshowview();

     QVector<QVector<int>> top=this->shitu[2].getshowview();

    //主视图为0
    if(zero_cmp==front){
        //俯视图和左视图宽相等
        for(int x=0;x<jieshu;x++){
            int s0=0; int t0=0;
            for(int y=0;y<jieshu;y++){
                s0|=top[x][y];
                t0|=left[y][x];

            }
            if(s0!=t0){return false;}
        }
    }


    //左视图为0
    if(zero_cmp==left){
        //俯视图和主视图长对正
        for(int x=0;x<jieshu;x++){
            int s0=0; int t0=0;
            for(int y=0;y<jieshu;y++){
                s0|=top[y][x];
                t0|=front[y][x];

            }
            if(s0!=t0){return false;}
        }
    }



    //俯视图为0
    if(zero_cmp==top){
        //主视图和左视图高平齐
        for(int x=0;x<jieshu;x++){
            int s0=0; int t0=0;
            for(int y=0;y<jieshu;y++){
                s0|=front[x][y];
                t0|=left[x][y];

            }
            if(s0!=t0){return false;}
        }
    }

    return true;
}
void ToolWindow::paintEvent(QPaintEvent* ) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pic/nandu.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
