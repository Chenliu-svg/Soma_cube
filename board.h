#ifndef BOARD_H
#define BOARD_H
#include <QBasicTimer>
#include <QFrame>
#include <QMouseEvent>
#include <QPointer>
#include<QDebug>
#include<QWidget>
#include<QPoint>
#include<QMainWindow>
#include"mypushbuttom.h"
#include"global.h"
#include<QPair>
#include<QQueue>
#include<QTimer>
#include<QLabel>
typedef enum {EASY=1,MEDIUM=2,HARD=3} NANDU;

const int EASY_TIME=8;
const int MEDIUM_TIME=8;
const int HARD_TIME=8;

const int EASY_SCORE=1;
const int MEDIUM_SCORE=10;
const int HARD_SCORE=60;


const int FRONT=0;
const int LEFT=1;
const int TOP=2;
const int BACK=3;
const int RIGHT=4;
const int BOTTOM=5;


typedef QPair<int,int> P;
QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE





class MyTimer:public QTimer
{
     Q_OBJECT
public:
    explicit MyTimer(QWidget *parent = nullptr);
    MyTimer(NANDU);
    int get_time() const{
        return now;
    }
    void set_now(int s){
        now=s;
    }

    int get_init() const{
        return init_time;
    }
    void set_init(int s){
        init_time=s;
    }
    void reset_time(){
        now=init_time;
    }

    QLabel * lab=0;

private:
    int init_time=0;
    int now=0;

signals:
    void timepass();


};

//每创建一个timer都要指定它的cur_player
class Mylabel:public QLabel{
    Q_OBJECT
public:
   explicit Mylabel(QWidget *parent = nullptr);
    void show_info(){

        this->setText( "玩家： "+cur_player->getName()+'\n'+"积分： "+QString::number(cur_player->getScore()));
        this->show();
    }


    Player* cur_player;



};

class proj_2D: public QFrame{

    //对传入的2d矩阵进行包装
    //使其具有旋转rotate() 功能，并将生成的旋转的矩阵放在rotate_brothers列表中
    //drawSquare（）绘制小正方形
    //重写paintEvent(),根据show_view矩阵,调用drawSquare（）对proj_2D进行可视化
    //重写mousePressEvent(),mouseReleaseEvent() 实现鼠标按下显示2d视图,释放隐藏视图的功能

    //piece左上角的一个块作为标记块,鼠标点击时获得坐标,如果位于标记快内则为选中 ischosen=1;

public:
    explicit proj_2D( const QVector<QVector<int>> & view);
    // proj_2D(proj_2D& m);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    //宽为SquareWidht，高为SquareHeight的正方型
    int squareWidth() {return contentsRect().width() / pieceWidth; }
    int squareHeight() { return contentsRect().height() / pieceHeight; }
    void drawSquare(QPainter &painter, int x, int y,int yanse);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event)  override;
    void mouseReleaseEvent(QMouseEvent *event) override;


    void rotate() ;
    void print_2d();
    QVector<QVector<int>> show_view ;

    QVector<QVector<int>> get_view(){
        return m_view;
    }
    bool ischoosen{false};

    QList<QVector<QVector<int>>> rotate_brothers;
    enum {pieceWidth=6,pieceHeight=6};
    MyPushButtom* choose=0;
private:
    int jieshu;


    int yanse=rand()%8;

    QVector<QVector<int>> m_view ;

    //鼠标位置
    //QPoint mousePos;
    //鼠标按下标志位
    bool mousePressed{false};



    int num_click=0;

};

class User_define:public proj_2D{
    //生成空白的，带方格的画布，用户点击一个方格，就给方格上色，最后用户画完以后点击提交，将生成的两个视图传入init_3d里面,从而生成所有的，再导入文件中
    //0-1二维矩阵，如果是0，就画成白色，1就画成彩色，这样就实现了无论怎样都根据01矩阵画，一开始矩阵全是0
    //鼠标点击事件，获取鼠标点击的位置，计算鼠标在哪一个块，然后把矩阵对应的元素改为1，然后重画这个矩阵
    //后点击提交，将生成的两个视图传入init_3d里面从而生成所有的
public:
    User_define();
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event)  override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    QVector<QVector<int>> getshowview(){
        return this->show_view;
    }

    //鼠标位置
    QPoint mousePos;
    //鼠标按下标志位
    bool mousePressed{false};
    //按键次数矩阵
    QVector<QVector<int>> count;
    int color[2]={7,8};
};

class zhankai:public User_define{
public:
    zhankai(const QVector<QVector<int>> & arr);
    //关闭对鼠标事件的响应
    void mousePressEvent(QMouseEvent *event)  override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};


class Zhankaitu: public QMainWindow {
    Q_OBJECT
public:
    Zhankaitu(const QVector<QVector<QVector<int>>> & arr,QWidget *parent = 0);
    //生成标准的三视图
    void stand_3view(const QVector<QVector<QVector<int>>> & arr);
    //生成6个视图
    virtual void generate_all_view()=0;//虚函数，完全由子类展开图的不同而实现
    //生成不同视图的方法
    QVector<QVector<int>> lr_asysmetry(const QVector<QVector<int>> & a);
    QVector<QVector<int>> td_asysmetry(const QVector<QVector<int>> & a);
    QVector<QVector<int>> ni_asysmetry(const QVector<QVector<int>> & a);//逆时针旋转90度后左右对称
    QVector<QVector<int>> shun_asysmetry(const QVector<QVector<int>> & a);//顺时针旋转90度后左右对称

    //将每个视图生成的zhankai移动到合适的展开图的位置
    void move_all();

    //布局：给每个视图一个块号，虚函数，因展开图而不同
    virtual void bujv()=0;


    //可视化二维矩阵
    void keshihua();



    //QVector<QVector<QVector<int>>>  cube;
    QVector<QVector<int>> views [6];//六个视图的二维矩阵
    int loc[6];//记录所在位置
    zhankai *  zhankai_arr[6];//六个视图可视化
};


class Gun :public Zhankaitu{
public:
    Gun(const QVector<QVector<QVector<int>>> & arr);
    void generate_all_view();
    void bujv();

};

class Step:public Zhankaitu{
public:
    Step(const QVector<QVector<QVector<int>>> & arr);
    void generate_all_view();
    void bujv();

};

class Dog:public Zhankaitu{
public:
    Dog(const QVector<QVector<QVector<int>>> & arr);
    void generate_all_view();
    void bujv();

};


class Board : public QMainWindow
{

    //board类根据传入的三个视图生成所需要的干扰视图，并可视化
    //rand_2dArray随机生成二维干扰数组列表(不包括传入的三个视图数组和他们的rotate_brothers，并检验无孤岛check_2dArray(),数组的大小由难度等级决定
    //如果符合条件则生成proj_2d加入到展示total_2d列表中
    //设置计时器,玩家情况展示(包含一个玩家对象,用于更新玩家的积分和等级),关卡情况
    //暂停,退出,再来一次,下一关,返回按钮

    Q_OBJECT
public:

    explicit  Board( proj_2D& view1, proj_2D& view2, proj_2D& view3,NANDU degree, int guanqia,QWidget *parent = 0);

    int check_2d_array(QVector<QVector<int>> & array);






    QList<QVector<QVector<int>>>total_brothers;
    QList<QVector<QVector<int>>> all_view;
    MyTimer* timer;
    QList<proj_2D*> all_proj;
    QList<int> correct_index;
    Mylabel* player_info;


signals:
    void clickback();
    void nextturn();

};

#endif // BOARD_H
