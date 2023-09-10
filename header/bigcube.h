#ifndef BIGCUBE_H
#define BIGCUBE_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>
#include<QSet>
#include<QMessageBox>
#include"board.h"
#include<QDir>


//改局游戏获得积分的计算：难度*剩余时间

class Init_3D{
    //按各种条件生成3维01数组my01Array，即异形立方体
         //（比如自动出题根据阶数和小正方体的数量生成异形立方体,根据三视图生成异形立方体等等）
    //check_array()函数判断立方体是否满足没有孤岛的要求（异形立方体中的小立方体之间必须是有面连接的）

    //generate_2D() 生成异形立方体的三视图
    //center_zuobiao数组保存着每一个小正方体的中心坐标，便于Cude3D可视化

public:

     Init_3D(int n);//随机生成符合条件的n阶0-1矩阵
     Init_3D(int n,int small_num);//随机生成符合条件的n阶0-1矩阵,并且size等于指定的small_num
     Init_3D(const QVector<QVector<QVector<int>>>);//根据传入的三维数组来初始化
     //根据三个视图，生成最大的异形立方体
     Init_3D( const QVector<QVector<int>> & left,const QVector<QVector<int>>  & front, const QVector<QVector<int>> & top);
    //用于打印测试
     void print_01()  const;
    //
     bool check(int i,int j,int k);


     //check_array()函数判断立方体是否满足没有孤岛的要求（异形立方体中的小立方体之间必须是有面连接的）
    int check_array();
    //生成异形立方体的三个视图
    void generate_2D();
  int getsize(){
      return size;}

     QVector<QVector3D> center_zuobiao;
     QVector<QVector<int>> left_view;
     QVector<QVector<int>> front_view;
     QVector<QVector<int>> top_view;
     //void dfs(QVector<QVector<QVector<int>>>);
      QVector<QVector<QVector<int>>> my01Array;





      int jieshu=0;


private:


  int size=0;
  int last_x=0;
  int last_y=0;
  int last_z=0;

};


class BigCube : public QMainWindow
{
    //对每一个小正方体进行可视化，从而实现大的异形立方体的可视化
    //构造函数 传入Init_3D异形立方体的三维数组，获得其center_zuobiao中心坐标数组
    //重写父类虚函数 paintEvent（）绘制每个正方体
    //重写mousePressEvent（），mouseMoveEvent（），mouseReleaseEvent（）实现绕原点旋转功能
    //重写wheelEvent（）实现放大，缩小功能
    Q_OBJECT
public:
   // explicit BigCube(QWidget *parent = nullptr);
      BigCube( Init_3D z,NANDU a,int Turn,QWidget *parent = nullptr);
    BigCube(const Init_3D,QWidget *parent = nullptr);

     void findall(Init_3D & a);
     void dfs(Init_3D & a,int i,int j,int k);
     void dispalyall();
     void writeall();
     void encoder(Init_3D & a);





    QVector<QVector3D> temp_encoder;
   // QVector<QVector3D> zhongxin;
    QVector<QVector<QVector<int>>>  marktable;
     MyTimer* timer=0;
     Board* board=0;
     NANDU degree=EASY;
     int turn=0;
     QVector<Init_3D*> init_array;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    QPointF getPoint(const QVector3D &vt, int w) const;

private:

    QList<QVector<QVector3D>>  vertexArr;//中心点坐标列表  每一个元素是每一个小正方体的8个顶点

    //立方体六个面
    QVector<QVector<int>> elementArr;
    //观察矩阵旋转
    QVector3D rotationAxis;
    QQuaternion rotationQuat;
    //透视投影的fovy参数，视野范围
    float projectionFovy{30.0f};

    //鼠标位置
    QPoint mousePos;
    //鼠标按下标志位
    bool mousePressed{false};


signals:
   void nextCube();
   void returnback();
};

#endif // BIGCUBE_H
