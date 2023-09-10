#include "board.h"
#include<QPainter>
#include<iostream>
#include<QMessageBox>
using namespace std;

proj_2D::proj_2D( const QVector<QVector<int>> & view){
    //基本设置
    setFixedSize(210,210);
    setFrameShape(WinPanel);
    setFrameShadow(Plain);

    jieshu=view.count();


    m_view.resize(jieshu);
    for(int i=0;i<jieshu;i++){
        m_view[i].resize(jieshu);
    }
    m_view=view;

    show_view.resize(pieceWidth);
    for(int i=0;i<pieceWidth;i++){
        show_view[i].resize(pieceHeight);
    }

//    for(int i=0;i<jieshu;i++){
//        for(int j=0;j<jieshu;j++){
//            show_view[i+1][j+1]=m_view[i][j];
//        }
//    }

    choose=new MyPushButtom(":/pic/choose1.png",":/pic/choose2.png");
    choose->setParent(this);
    choose->move(this->width()*0.025,this->height()*0.025);

    connect(choose,&MyPushButtom::clicked,[=](){
        num_click++;

        //奇数下代表选中
        if(num_click%2)
        {
            this->ischoosen=true;


                QPixmap pixmap1;
                bool ret=pixmap1.load(choose->pressedImagePath);
                if(!ret){
                    qDebug()<<choose->pressedImagePath<<"加载失败！";
                }
                choose->setFixedSize(pixmap1.width()*0.8,pixmap1.height()*0.8);

                choose->setStyleSheet("QPushButton{border:0px;}");

                choose->setIcon(pixmap1);

                choose->setIconSize(QSize(pixmap1.width()*0.8,pixmap1.height()*0.8));
            }




        else{
            this->ischoosen=false;

                QPixmap pixmap1;
                bool ret=pixmap1.load(choose->normalImagePath);
                if(!ret){
                    qDebug()<<choose->normalImagePath<<"加载失败！";
                }
                choose->setFixedSize(pixmap1.width()*0.8,pixmap1.height()*0.8);

                choose->setStyleSheet("QPushButton{border:0px;}");

                choose->setIcon(pixmap1);

                choose->setIconSize(QSize(pixmap1.width()*0.8,pixmap1.height()*0.8));
            }


        });
}

void proj_2D::rotate(){
    QVector<QVector<int>>  temp0(jieshu,QVector<int>(jieshu,0));
    QVector<QVector<int>>  temp1(jieshu,QVector<int>(jieshu,0));
    QVector<QVector<int>>  temp2(jieshu,QVector<int>(jieshu,0));

    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            temp0[j][jieshu-i-1]=m_view[i][j];
            temp1[jieshu-i-1][jieshu-j-1]=m_view[i][j];
            temp2[jieshu-j-1][i]=m_view[i][j];
        }
    }
    rotate_brothers.push_back(temp0);
     rotate_brothers.push_back(temp1);
      rotate_brothers.push_back(temp2);

}





void proj_2D::print_2d(){
    for(int k=0;k<rotate_brothers.count();k++){
        for(int i=0;i<jieshu;i++){
            for(int j=0;j<jieshu;j++){
                cout<<rotate_brothers[k][i][j]<<" ";
            }
            cout<<endl;
    }
        cout<<endl<<endl;
}
}

QSize proj_2D::sizeHint() const
{
    //qDebug()<<frameWidth();//1
    return QSize(pieceHeight*20 + frameWidth() * 2,
                 pieceHeight*24 + frameWidth() * 2);
}

QSize proj_2D::minimumSizeHint() const

{
    return QSize(pieceHeight*5  + frameWidth() * 2,
                 pieceHeight*6  + frameWidth() * 2);
}

void proj_2D::drawSquare(QPainter &painter, int x, int y,int yanse)
{
    static const QRgb colorTable[9] = {
        0xFFC0CB, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00,0xffffff
    };

    QColor color = colorTable[yanse];

    //内部填充，两边各留1px的线条
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);


    //上面和左边是浅色，右边和下面是深色的，以达到更好的视觉效果
    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}

void proj_2D::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();

    int pieceTop = rect.bottom() - pieceHeight*squareHeight();

    for (int i = 0; i < pieceHeight; ++i) {
        for (int j = 0; j < pieceWidth; ++j) {
           int shape = show_view[i][j];
            if (shape)
                drawSquare(painter, rect.left() + j * squareWidth(),
                           pieceTop + i * squareHeight(),yanse);
        }



}

}


void proj_2D::mousePressEvent(QMouseEvent *event)
{
    mousePressed = true;
   // mousePos = event->pos();

    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            show_view[i+1][j+1]=m_view[i][j];
        }
    }
    update();
    QWidget::mousePressEvent(event);

}

void proj_2D::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
    show_view=QVector<QVector<int>>(pieceWidth,QVector<int>(pieceHeight,0));
    update();
    QWidget::mouseReleaseEvent(event);
}

User_define::User_define():proj_2D(QVector<QVector<int>>(pieceWidth,QVector<int>(pieceHeight,0))){
    this->choose->hide();
    this->show_view=this->get_view();//初始化为全0的矩阵
    this->count=this->get_view();//初始化为全0的矩阵
}
void User_define::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();



    int pieceTop = rect.bottom() - pieceHeight*squareHeight();

    for (int i = 0; i < pieceHeight; ++i) {
        for (int j = 0; j < pieceWidth; ++j) {
           int shape = show_view[i][j];
            if (shape)//是1就画成黄色
                drawSquare(painter, rect.left() + j * squareWidth(),
                           pieceTop + i * squareHeight(),color[0]);
            else{//是0就画成白色
                drawSquare(painter, rect.left() + j * squareWidth(),
                           pieceTop + i * squareHeight(),color[1]);
            }
        }



}

}

void User_define::mousePressEvent(QMouseEvent *event){
    mousePressed = true;
    mousePos = event->pos();

    //根据坐标判断矩阵哪一个元素变成1

    //为了实现奇数下画，偶数下不画的效果
   //为每一个元素维护一个按键次数c矩阵，show_view[i][j]=c%2
    int j=mousePos.x()/squareWidth();
    int i=mousePos.y()/squareHeight();
    count[i][j]++;
    show_view[i][j]=count[i][j]%2;
    update();
    QWidget::mousePressEvent(event);

}

void User_define::mouseReleaseEvent(QMouseEvent *event)
{
 QWidget::mouseReleaseEvent(event);
}

zhankai::zhankai(const QVector<QVector<int>> & arr){
    this->show_view=arr;
}

void zhankai::mousePressEvent(QMouseEvent *event){
     QWidget::mousePressEvent(event);
}

void zhankai::mouseReleaseEvent(QMouseEvent *event)
{
 QWidget::mouseReleaseEvent(event);
}

Zhankaitu::Zhankaitu(const QVector<QVector<QVector<int>>> & arr,QWidget *parent):QMainWindow(parent){
    //基本设置
    setFixedSize(1200,800);

    setWindowIcon(QIcon(":/pic/icon.png"));

    setWindowTitle("索玛秘图");


   stand_3view(arr);

}

Gun::Gun(const QVector<QVector<QVector<int>>> & arr):Zhankaitu(arr){

    this->generate_all_view();
    this->bujv();

}

void Gun::generate_all_view(){
    //后视图=前视图左右对称
    this->views[BACK]=this->lr_asysmetry(views[FRONT]);

    //右视图=左视图左右对称
    this->views[RIGHT]=this->lr_asysmetry(views[LEFT]);


    //仰视图=俯视图逆时针旋转90度后左右对称
    this->views[BOTTOM]=this->ni_asysmetry(views[TOP]);


}
void Gun::bujv(){
    loc[TOP]=1;
    loc[LEFT]=4;
    loc[FRONT]=5;
    loc[RIGHT]=6;
    loc[BACK]=7;
    loc[BOTTOM]=10;

    //布局好后移动到相关位置

    this->move_all();

}

Step::Step(const QVector<QVector<QVector<int>>> & arr):Zhankaitu(arr){

    this->generate_all_view();
    this->bujv();

}

void Step::generate_all_view(){
    //后视图=前视图左右对称
    this->views[BACK]=this->shun_asysmetry(views[FRONT]);

    //右视图=左视图左右对称
    this->views[RIGHT]=this->shun_asysmetry(views[LEFT]);


    //仰视图=俯视图逆时针旋转90度后左右对称
    this->views[BOTTOM]=this->shun_asysmetry(views[TOP]);


}
void Step::bujv(){
    loc[TOP]=2;
    loc[LEFT]=5;
    loc[FRONT]=6;
    loc[RIGHT]=3;
    loc[BACK]=8;
    loc[BOTTOM]=9;


    //布局好后移动到相关位置

    this->move_all();

}


Dog::Dog(const QVector<QVector<QVector<int>>> & arr):Zhankaitu(arr){

    this->generate_all_view();
    this->bujv();

}

void Dog::generate_all_view(){
    //后视图=前视图左右对称
    this->views[BACK]=this->lr_asysmetry(views[FRONT]);

    //右视图=左视图左右对称
    this->views[RIGHT]=this->shun_asysmetry(views[LEFT]);


    //仰视图=俯视图逆时针旋转90度后左右对称
    this->views[BOTTOM]=this->td_asysmetry(views[TOP]);


}
void Dog::bujv(){
    loc[TOP]=2;
    loc[LEFT]=5;
    loc[FRONT]=6;
    loc[RIGHT]=3;
    loc[BACK]=4;
    loc[BOTTOM]=10;


    //布局好后移动到相关位置

    this->move_all();

}




void Zhankaitu::stand_3view(const QVector<QVector<QVector<int>>> & arr){
    int jieshu=arr.count();
    this->views[FRONT]=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));
    this->views[LEFT]=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));
    this->views[TOP]=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));


    //按位或

    for(int x=0;x<jieshu;x++){
        for(int y=0;y<jieshu;y++){
            for(int z=0;z<jieshu;z++){
                 this->views[FRONT][z][y]|=arr[x][y][z];
                 this->views[LEFT][z][x]|=arr[x][y][z];
                 this->views[TOP][x][y]|=arr[x][y][z];
            }
        }
    }
}


QVector<QVector<int>> Zhankaitu::lr_asysmetry(const QVector<QVector<int>> & a){
    int n=a.count();
    QVector<QVector<int>> b=a;

    for(int i=0;i<n;i++){
        for(int j=0;j<n/2;j++){
//           int temp=b[i][j];
//           b[i][j]=
            swap(b[i][j],b[i][n-1-j]);
        }
    }
    return b;
}


QVector<QVector<int>> Zhankaitu::td_asysmetry(const QVector<QVector<int>> & a){
    int n=a.count();
    QVector<QVector<int>> b=a;

    for(int i=0;i<n/2;i++){
        for(int j=0;j<n;j++){
//           int temp=b[i][j];
//           b[i][j]=
            swap(b[i][j],b[n-1-i][j]);
        }
    }
    return b;
}


QVector<QVector<int>>  Zhankaitu::ni_asysmetry(const QVector<QVector<int>> & a)//逆时针旋转90度后左右对称
{
    int jieshu=a.count();
    QVector<QVector<int>>  temp0(jieshu,QVector<int>(jieshu,0));
    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            temp0[jieshu-j-1][i]=a[i][j];

        }



    }
    return lr_asysmetry(temp0);
}
QVector<QVector<int>>  Zhankaitu::shun_asysmetry(const QVector<QVector<int>> & a)//顺时针旋转90度后左右对称
{
    int jieshu=a.count();
    QVector<QVector<int>>  temp0(jieshu,QVector<int>(jieshu,0));
    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            temp0[j][jieshu-i-1]=a[i][j];

        }


    }
    return lr_asysmetry(temp0);
}


void  Zhankaitu::keshihua(){
    for(int i=0;i<6;i++){
        zhankai_arr[i]=new zhankai(views[i]);
    }

}
//将每个视图生成的zhankai移动到合适的展开图的位置
void Zhankaitu::move_all(){
    keshihua();//为每个二维视图可视化
    for(int i=0;i<6;i++){
        this->zhankai_arr[i]->setParent(this);
        this->zhankai_arr[i]->move(this->width()*0.15+loc[i]%4*zhankai_arr[i]->width(),
                                   this->height()*0.1+loc[i]/4*zhankai_arr[i]->height());
    }



}


MyTimer::MyTimer(NANDU  degree){
    switch (degree) {
    case EASY:
        set_init(EASY_TIME);
        set_now(EASY_TIME);
        break;
    case MEDIUM:
        set_init(MEDIUM_TIME);
        set_now(MEDIUM_TIME);
        break;
    case HARD:
        set_init(HARD_TIME);
        set_now(HARD_TIME);
        break;

    }
    this->start(1000);
    lab=new QLabel();
    lab->setStyleSheet(
                "  font-family:STXingkai;"
                "font-size: 20px;"
                "color: #292421;"
                "font-style: normal;"
                "font-weight: normal;"

                " border-style: solid;"
                "border-width: 2px;"
                " border-color: #ffd700;"
                " border-radius: 20px;"

                " padding-left: 20px;"
                " padding-top: 0px;"

                "  background-color: #87ceeb;"

                "  background-repeat: no-repeat;"
                " background-position: left center;"
                );

    lab->setText("     ");
    connect(this,&QTimer::timeout, this, [=](){
        lab->setText("剩余时间: \n   "+QString::number(now--));
        if(now==0){
            emit timepass();


        }
    });

}

Mylabel::Mylabel(QWidget *parent){
   setParent(parent);

    resize(parent->width()*0.15,parent->height()*0.1);
    move(parent->width()*0.8,0);

    setStyleSheet(
                "  font-family:STXingkai;"
                               "font-size: 20px;"
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


}


Board:: Board( proj_2D& view1, proj_2D& view2, proj_2D& view3,NANDU degree, int guanqia,QWidget *parent )
 : QMainWindow(parent)
{

    //基本设置
    setFixedSize(1200,800);

    setWindowIcon(QIcon(":/pic/icon.png"));

    setWindowTitle("索玛秘图");


    //显示玩家信息lab
    player_info=new Mylabel(this);

    player_info->cur_player=cur_player;
    player_info->show_info();

    //设置倒计时，要可以记录秒数，用于积分计算，超时出发挑战失败窗口
    timer=new MyTimer (degree);
    timer->set_init((4-int(degree))*30);
    timer->reset_time();
    timer->lab->setParent(this);

    timer->lab->resize(this->width()*0.2,this->height()*0.1);
    timer->lab->move(5,5);
    connect(timer,&MyTimer::timepass,[=](){
        //
        QMessageBox* over=new QMessageBox(this);

        over->information(this,"fail","很遗憾没能在规定时间提交，挑战失败\n点击 ok 再来一次叭！");
        if(cur_player->getScore()-10>0){
            cur_player->setScore(cur_player->getScore()-10);
        }
        player_info->show_info();
        timer->reset_time();




    });
    //显示关卡lab
    QLabel* guanshu=new QLabel(this);
    guanshu->move(this->width()*0.5-guanshu->width(),0);
    QString nandu;
    switch (degree) {
    case EASY:
        nandu="简单";
        break;
    case MEDIUM:
        nandu="中等";
        break;
    case HARD:
        nandu="困难";
        break;

    }
    guanshu->resize(this->width()*0.1,this->height()*0.05);
    guanshu->setStyleSheet(
                "  font-family:STXingkai;"
                "font-size: 20px;"
                "color: #000000;"
                "font-style: normal;"
                "font-weight: normal;"

                " border-style: solid;"
                "border-width: 2px;"
                " border-color: #dda0dd;"
                " border-radius: 20px;"

                " padding-left: 20px;"
                " padding-top: 0px;"

                "  background-color: #FFFF00;"

                "  background-repeat: no-repeat;"
                " background-position: left center;"
                );
    guanshu->setText(nandu+":    "+QString::number(guanqia));

    //翻转区域,判断是否挑战成功，弹出挑战成功对话框
    //对每一个视图，生成3个干扰图


    QList<proj_2D*> temp_proj;
    temp_proj.push_back(&view1);
    temp_proj.push_back(&view2);
    temp_proj.push_back(&view3);

    view1.rotate();
    view2.rotate();
    view3.rotate();

    int jieshu=view1.get_view().count();
    QVector<QVector<int>> temp_view=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));
    for(int k=0;k<3;k++){

        all_view.push_back(temp_proj[k]->get_view());}

    //生成total_brothers
    for(int k=0;k<3;k++){
        for(int i=0;i<3;i++){
            total_brothers.push_back(temp_proj[k]->rotate_brothers[i]);
        }}
    //生成三个符合要求的干扰图
    for(int m=0;m<9;m++){
        // qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        temp_view=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));
        do{
            for(int i=0;i<jieshu;i++){
                for(int j=0;j<jieshu;j++){
                    if(qrand()%10<4){
                        temp_view[i][j]=1;
                    }
                }
            }}while(!check_2d_array(temp_view)||all_view.contains(temp_view)||total_brothers.contains(temp_view));

        //不能和前面的相同
        all_view.push_back(temp_view);

    }

    //qDebug()<<all_view.count();
    //    for(int i=0;i<all_view[0].count();i++){
    //        qDebug()<<all_view[0][i]<<" ";
    //    }



    //利用shuffle算法生成一个随机的全排列
    int t=all_view.count();
    QList<QVector<QVector<int>>> temp_list;
    for(int i=1;i<=all_view.count();i++){

        int x=rand()%t;//随机挑一个，放入temp_list中
        //如果挑到正确的，记录位置，也就是i-1
        if(all_view[x]==view1.get_view()||
                all_view[x]==view2.get_view()||all_view[x]==view3.get_view()){
            correct_index.push_back(i-1);
        }
        temp_list.push_back(all_view[x]);

        swap(all_view[x],all_view[t-1]);
        t--;
    }


    for(int i=0;i<3;i++){
        qDebug()<<correct_index[i];
    }


    for(int i=0;i<temp_list.count();i++){

        proj_2D* temp=new proj_2D(temp_list.at(i));
        all_proj.push_back(temp);}


    for(int i=0;i<all_proj.count();i++){
        proj_2D* temp_2d= all_proj[i];
        temp_2d->setParent(this);

        temp_2d->move(this->width()*0.15+temp_2d->width()*(i%4),this->height()*0.1+temp_2d->height()*(i/4));


    }

    //设置返回按钮  封装成一个类  提前强制退出：扣分
    MyPushButtom * tuichubtn=new MyPushButtom(":/pic/tuichu.png");

    tuichubtn->setParent(this);

    tuichubtn->move(this->width()*0.92-tuichubtn->width()*0.5,this->height()*0.9);

    connect(tuichubtn,&MyPushButtom::clicked,[=](){
        tuichubtn->zoom1();
        tuichubtn->zoom2();
        //扣分
        if(cur_player->getScore()-10>0){
            cur_player->setScore(cur_player->getScore()-10);
        }
        player_info->show_info();
        timer->stop();
        emit this->clickback();

    });



    //用户点击提交以后，获得选中的编号     //后期：不可以多选
    //提交以后：获得选中的编号 ，获得检查是否正确，弹出提示框，再来一次，下一关


    //提交按钮：
    MyPushButtom * tijiaobtn=new MyPushButtom(":/pic/tijiao.png");

    tijiaobtn->setParent(this);

    tijiaobtn->move(this->width()*0.8-tijiaobtn->width()*0.5,this->height()*0.9);

    connect(tijiaobtn,&MyPushButtom::clicked,[=](){
        QList<int> player_choose;
        tuichubtn->zoom1();
        tuichubtn->zoom2();
        //弹出对话框提示
        int count=0;
        for(int i=0;i<all_proj.count();i++){
            if(all_proj[i]->ischoosen){
                count++;
                player_choose.push_back(i);
            }
        }
        if(count<3){
            QMessageBox* warning=new QMessageBox(this);

            warning->information(this,"tip","还没选满3个哦！\n点击 ok 继续游戏！");

            //继续游戏,计时器继续走
            QMediaPlayer *player = new QMediaPlayer(this);//设置背景音乐
            player->setMedia(QUrl("qrc:/pic/失败.wav"));

            player->setVolume(50);//音量

            player->play();


        }
        else{
            bool ret=(correct_index.contains(player_choose[0]))&&(correct_index.contains(player_choose[1]))&&(correct_index.contains(player_choose[2]));
            if(ret){
                //停止计时
                timer->stop();
                //画出三个proj_2d
                for(int k=0;k<3;k++){
                    for(int i=0;i<jieshu;i++){
                        for(int j=0;j<jieshu;j++){
                            all_proj[correct_index[k]]->show_view[i+1][j+1]=all_proj[correct_index[k]]->get_view()[i][j];
                            update();
                        }
                    }


                }
                QMessageBox* success=new QMessageBox(this);

                success->information(this,"tip","恭喜你，选择正确！\n点击 ok 进入下一关叭！");
                QMediaPlayer *player = new QMediaPlayer(this);//设置背景音乐
                player->setMedia(QUrl("qrc:/pic/成功.wav"));

                player->setVolume(50);//音量

                player->play();
                cur_player->setScore(cur_player->getScore()+timer->get_time()*int(degree)+turn);
                //player_info->show_info();
                disconnect(timer, &MyTimer::timepass, 0, 0);
                turn++;
                emit nextturn();
                //进入下一关


            }else{
                QMessageBox* fail=new QMessageBox(this);

                fail->information(this,"tip","真遗憾，挑战失败！\n点击 ok 继续选择叭！");
                QMediaPlayer *player = new QMediaPlayer(this);//设置背景音乐
                player->setMedia(QUrl("qrc:/pic/失败.wav"));

                player->setVolume(50);//音量

                player->play();
                if(cur_player->getScore()-10>0){
                    cur_player->setScore(cur_player->getScore()-10);
                }
                player_info->show_info();

                //计时器继续走

            }
        }
    });


    //暂停按钮


    //退出按钮







}


int Board::check_2d_array( QVector<QVector<int>> & array){
    //计算所有1的个数
    int jieshu=array.count();
    int size=0;
    int last_x=0;
    int last_y=0;
    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            if(array[i][j]){
                size++;
                last_x=i;
                last_y=j;
            }
        }
    }
    if(size==0) return 0;//不可以为空
    //bfs判断是否有孤岛

    //利用图的遍历算法，计数，如果最后小于size说明有孤岛
    //广度优先遍历，出队就
    QQueue<P> que;
    QVector<QVector<int>> temp(QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0)));
    int count=0;

    vector<vector<int>> delt={{-1,0},{1,0},{0,1},{0,-1}};

    que.enqueue(P(last_x,last_y));
    //hash[QVector3D(last_x,last_y,last_z)]=1;
    //temp[last_x][last_y][last_z]=1;

    while(!que.empty()){
        P front= que.dequeue();//队列不为空，出队

        if(temp[front.first][front.second]!=1){
            for(int m=0;m<4;m++){
                if(((front.first+delt[m][0])>=0&&((front.first+delt[m][0])<jieshu))
                        &&(front.second+delt[m][1])>=0&&((front.second+delt[m][1])<jieshu)
                        &&(array[front.first+delt[m][0]][front.second+delt[m][1]]==1)){
                    if(temp[front.first+delt[m][0]][front.second+delt[m][1]]!=1){
                        que.enqueue(P(front.first+delt[m][0],front.second+delt[m][1]));

                    }
                    else{continue;}

                }

            }
            temp[front.first][front.second]=1;
            count++;
        }

    }

    int flag=1;

    if(count<size){
        flag= 0;
    }


    return flag;

}



