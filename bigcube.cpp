#include "bigcube.h"
#include"global.h"
#include <QtGlobal>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QDebug>
#include <QTime>
#include<QQueue>
#include<QTimer>
#include<QLabel>
#include <QPicture>
#include<iostream>
#include<fstream>
using namespace std;
string file1=(QString(QDir::currentPath()+"/"+"cube.dat")).toStdString();
//string file1="D:/qtlearning/MainScene/cube.dat";
int view=0;
//给阶数生成异形立方体
Init_3D::Init_3D(int n):jieshu(n)
{
     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    my01Array.resize(jieshu);
    for(int i=0;i<jieshu;i++){
        my01Array[i].resize(jieshu);
         for(int j=0;j<jieshu;j++){
              my01Array[i][j].resize(jieshu);

         }
    }
    do{
    //随机生成01数组
    size=0;
    center_zuobiao.clear();
    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            for(int k=0;k<jieshu;k++){
                my01Array[i][j][k]=0;


                int suiji=qrand()%10;
                if(suiji>6){
                my01Array[i][j][k]=1;
                last_x=i;
                last_y=j;
                last_z=k;

                size++;
                //center_zuobiao数组保存着每一个小正方体的中心坐标，便于异形立方体的可视化
                center_zuobiao.push_back(QVector3D(i-jieshu/2,j-jieshu/2,k-jieshu/2));
                }


            }
        }
    }


}while((size>jieshu*jieshu||size<=jieshu)||(!this->check_array()));

        generate_2D();
}

//直接根据01矩阵生成立方体
Init_3D::Init_3D(const QVector<QVector<QVector<int>>> array){
    this->my01Array=array;
    this->jieshu=array.count();
    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            for(int k=0;k<jieshu;k++){
                if(my01Array[i][j][k]==1){

                last_x=i;
                last_y=j;
                last_z=k;

                size++;

                center_zuobiao.push_back(QVector3D(i-jieshu/2,j-jieshu/2,k-jieshu/2));
            }}}}


     generate_2D();
}


//给阶数和个数生成异形立方体
Init_3D::Init_3D(int n,int small_num):jieshu(n){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
   my01Array.resize(jieshu);
   for(int i=0;i<jieshu;i++){
       my01Array[i].resize(jieshu);
        for(int j=0;j<jieshu;j++){
             my01Array[i][j].resize(jieshu);

        }
   }
    do{
    size=0;
    center_zuobiao.clear();
    for(int i=0;i<jieshu;i++){
        for(int j=0;j<jieshu;j++){
            for(int k=0;k<jieshu;k++){
                my01Array[i][j][k]=0;
                int suiji=qrand()%10;
                if(suiji>4){
                my01Array[i][j][k]=1;
                last_x=i;
                last_y=j;
                last_z=k;

                size++;
                center_zuobiao.push_back(QVector3D(i-jieshu/2,j-jieshu/2,k-jieshu/2));
                }


            }
        }
    }


}while((size!=small_num)||(!this->check_array()));
    generate_2D();
    //qDebug()<<size;
}


//给三视图生成最大的符合要求的异形立方体
Init_3D::Init_3D( const QVector<QVector<int>> & left,const QVector<QVector<int>>  & front, const QVector<QVector<int>> & top){
    jieshu=left.size();


    my01Array.resize(jieshu);
    for(int i=0;i<jieshu;i++){
        my01Array[i].resize(jieshu);
         for(int j=0;j<jieshu;j++){
              my01Array[i][j].resize(jieshu);

         }
    }



    //把视图拓展成三维矩阵
    QVector<QVector<QVector<int>>> left_temp(jieshu,QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0)));
    QVector<QVector<QVector<int>>> front_temp(jieshu,QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0)));
    QVector<QVector<QVector<int>>> top_temp(jieshu,QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0)));




   QVector<QVector<int>> zero_cmp(jieshu,QVector<int>(jieshu,0));

    if(top==zero_cmp){
        view=2;
    for(int x=0;x<jieshu;x++){
         for(int y=0;y<jieshu;y++){
             for(int z=0;z<jieshu;z++ ){
                 top_temp[x][y][z]=1;
                    if(left[z][x]){
                    left_temp[x][y][z]=1;

                }
                    if(front[z][y]){

                     front_temp[x][y][z]=1;
                        }

            }
        }
    }}
    if(front==zero_cmp){
        view=0;
        for(int x=0;x<jieshu;x++){
             for(int y=0;y<jieshu;y++){
                 for(int z=0;z<jieshu;z++ ){
                      front_temp[x][y][z]=1;
                        if(left[z][x]){
                        left_temp[x][y][z]=1;

                    }
                        if(top[x][y]){

                         top_temp[x][y][z]=1;
                            }

                }
            }
        }
    }
   if(left==zero_cmp){
       view=1;
            for(int x=0;x<jieshu;x++){
                 for(int y=0;y<jieshu;y++){
                     for(int z=0;z<jieshu;z++ ){
                          left_temp[x][y][z]=1;

                          if(front[z][y]){

                           front_temp[x][y][z]=1;
                              }
                            if(top[x][y]){

                             top_temp[x][y][z]=1;
                                }

                    }
                }
            }


    }

    //三个三维矩阵对应位置做与运算

    for(int x=0;x<jieshu;x++){
        for(int y=0;y<jieshu;y++){
            for(int z=0;z<jieshu;z++){
                my01Array[x][y][z]=left_temp[x][y][z]*top_temp[x][y][z]*front_temp[x][y][z];
                if(my01Array[x][y][z])
               { last_x=x;
                last_y=y;
                last_z=z;

                size++;
                center_zuobiao.push_back(QVector3D(x-jieshu/2,y-jieshu/2,z-jieshu/2));
                }

            }
        }
    }

    if(!check_array()){
        qDebug()<<"异形立方体存在孤岛，构造失败程序退出";
      exit(1);

    }

    generate_2D();
}


void Init_3D::generate_2D(){
    front_view=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));
    left_view=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));
    top_view=QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0));


    //按位或

//    for(int z=0;z<jieshu;z++){
//        for(int x=0;x<jieshu;x++){
//            for(int y=0;y<jieshu;y++){
//                front_view[z][y]|=my01Array[x][y][z];
//                left_view[z][x]|=my01Array[x][y][z];
//                top_view[x][y]|=my01Array[x][y][z];
//            }
//        }
//    }
    for(int x=0;x<jieshu;x++){
            for(int y=0;y<jieshu;y++){
                for(int z=0;z<jieshu;z++){
                    front_view[z][y]|=my01Array[x][y][z];
                    left_view[z][x]|=my01Array[x][y][z];
                    top_view[x][y]|=my01Array[x][y][z];
                }
            }
        }


}
int Init_3D::check_array()
{
    //利用图的遍历算法，计数，如果最后小于size说明有孤岛
    //广度优先遍历，出队就
    QQueue<QVector3D> que;

    //temp作为标记数组，每次没有标记的邻居入队
  QVector<QVector<QVector<int>>> temp(jieshu,QVector<QVector<int>>(jieshu,QVector<int>(jieshu,0)));
    int count=0;


    //遍历6个邻居
    vector<vector<int>> delt={{-1,0,0},{1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}

    };

    que.enqueue(QVector3D(last_x,last_y,last_z));

     while(!que.empty()){
          QVector3D front= que.dequeue();//队列不为空，出队

          if(temp[front.x()][front.y()][front.z()]!=1){
          for(int m=0;m<6;m++){
           if(((front.x()+delt[m][0])>=0&&((front.x()+delt[m][0])<jieshu))
               &&((front.y()+delt[m][1])>=0&&((front.y()+delt[m][1])<jieshu))
                &&((front.z()+delt[m][2])>=0&&((front.z()+delt[m][2])<jieshu))
               &&(my01Array[front.x()+delt[m][0]][front.y()+delt[m][1]][front.z()+delt[m][2]]==1)){
               if(temp[front.x()+delt[m][0]][front.y()+delt[m][1]][front.z()+delt[m][2]]!=1){
                  que.enqueue(QVector3D(front.x()+delt[m][0],front.y()+delt[m][1],front.z()+delt[m][2]));

               }
                   else{continue;}

           }

            }
         temp[front.x()][front.y()][front.z()]=1;//标记已经被访问过的节点
         count++;
     }

}


    //如果count最后小于size说明有孤岛
    if(count<size){
        return 0;
    }
    return 1;

}
bool Init_3D::check(int i,int j,int k){
   QVector<QVector<QVector<int>>> temp=this->my01Array;
    temp[i][j][k]=0;
   Init_3D temp3d=Init_3D(temp);
  bool t=true;

   if(view==2){
   t=(temp3d.check_array()&&temp3d.left_view==this->left_view&&temp3d.front_view==this->front_view);}
   if(view==0){
      t=(temp3d.check_array()&&temp3d.left_view==this->left_view&&temp3d.top_view==this->top_view);
   }
   if(view==1){
       t=(temp3d.check_array()&&temp3d.front_view==this->front_view&&temp3d.top_view==this->top_view);
   }
   return t;
}


void Init_3D::print_01() const{
    for(int x=0;x<jieshu ;x++){
        for(int j=0;j<jieshu;j++){
            for(int k=0;k<jieshu;k++){
                cout<<my01Array[x][j][k];
            }
            cout<<endl;
        }
         cout<<endl;
    }

}

BigCube::BigCube(Init_3D z,QWidget *parent) : QMainWindow(parent){
    //基本设置
        setFixedSize(800,600);

        setWindowIcon(QIcon(":/pic/icon.png"));

        setWindowTitle("索玛秘图");
        rotationQuat=QQuaternion(1,0,0,0);
        QVector<QVector<QVector<int>>> t2(z.jieshu,QVector<QVector<int>>(z.jieshu,QVector<int>(z.jieshu,0)));

      marktable=t2;

      QVector<QVector3D>   zhongxin=z.center_zuobiao;
        for(int i=0;i<zhongxin.count();i++){
            float x0=zhongxin[i].x();
            float y0=zhongxin[i].y();
            float z0=zhongxin[i].z();
            QVector<QVector3D> vertexArr0 = QVector<QVector3D>{
                    QVector3D{x0+0.5f, y0+0.5f, z0-0.5f},
                    QVector3D{x0+0.5f, y0+0.5f, z0+0.5f},
                    QVector3D{x0+0.5f, y0-0.5f, z0+0.5f},
                    QVector3D{x0+0.5f, y0-0.5f, z0-0.5f},

                    QVector3D{x0-0.5f, y0+0.5f, z0-0.5f},
                    QVector3D{x0-0.5f, y0+0.5f, z0+0.5f},
                    QVector3D{x0-0.5f, y0-0.5f, z0+0.5f},
                    QVector3D{x0-0.5f, y0-0.5f, z0-0.5f}

                     };
            for(int k=0;k<vertexArr0.size();k++){
                QVector3D vertex=vertexArr0[k];
            QVector3D temp=vertex;
           vertexArr0[k].setX(temp.y());
            vertexArr0[k].setY(temp.z());
           vertexArr0[k].setZ(temp.x());}

        vertexArr.push_back(vertexArr0);
         }
            //六个面，一个面包含四个顶点
            elementArr = QVector<QVector<int>>{
                {0, 1, 2, 3},//前面
                {4, 5, 6, 7},//后面
                {0, 4, 5, 1},//右侧
                {1, 5, 6, 2},
                {2, 6, 7, 3},
                {3, 7, 4, 0}};

            //Widget默认没有焦点，此处设置为点击时获取焦点
            //setFocusPolicy(Qt::ClickFocus);



}
BigCube::BigCube(const Init_3D z,NANDU nandu,int Turn,QWidget *parent) : QMainWindow(parent)
{
       //z.print_01();
       this->turn=Turn;
        degree=nandu;
    //基本设置
        setFixedSize(800,600);

        setWindowIcon(QIcon(":/pic/icon.png"));

        setWindowTitle("索玛秘图");

        //计时器显示
        timer=new MyTimer(degree);
        timer->lab->setParent(this);

        timer->lab->resize(this->width()*0.2,this->height()*0.1);
        timer->lab->move(5,5);


    //          7------------------4
    //        /                 /  |
    //     3------------------0    |
    //     |                  |    |
    //     |                  |    |
    //     |                  |    |
    //     |                  |    |
    //     |    6             |    5
    //     |                  |  /
    //     2------------------1
    //立方体前后四个顶点，从右上角开始顺时针


        //六个面，一个面包含四个顶点
        elementArr = QVector<QVector<int>>{
        {0, 1, 2, 3},//前面
        {4, 5, 6, 7},//后面
        {0, 4, 5, 1},//右侧
        {1, 5, 6, 2},
        {2, 6, 7, 3},
        {3, 7, 4, 0}};

        QVector<QVector3D> zhongxin=z.center_zuobiao;
        for(int i=0;i<zhongxin.count();i++){
            float x0=zhongxin[i].x();
            float y0=zhongxin[i].y();
            float z0=zhongxin[i].z();

            //由中心点得到每个顶点的坐标
            QVector<QVector3D> vertexArr0 = QVector<QVector3D>{
                    QVector3D{x0+0.5f, y0+0.5f, z0-0.5f},
                    QVector3D{x0+0.5f, y0+0.5f, z0+0.5f},
                    QVector3D{x0+0.5f, y0-0.5f, z0+0.5f},
                    QVector3D{x0+0.5f, y0-0.5f, z0-0.5f},

                    QVector3D{x0-0.5f, y0+0.5f, z0-0.5f},
                    QVector3D{x0-0.5f, y0+0.5f, z0+0.5f},
                    QVector3D{x0-0.5f, y0-0.5f, z0+0.5f},
                    QVector3D{x0-0.5f, y0-0.5f, z0-0.5f}

        };



            //转化到qt的绘图坐标系中
            for(int k=0;k<vertexArr0.size();k++){
                QVector3D vertex=vertexArr0[k];
                QVector3D temp=vertex;
                vertexArr0[k].setX(temp.y());
                vertexArr0[k].setY(temp.z());
                vertexArr0[k].setZ(temp.x());}

            vertexArr.push_back(vertexArr0);
        }





        //绘制board
        proj_2D* piece=new proj_2D (z.left_view);

        proj_2D* piece1=new proj_2D (z.front_view);

        proj_2D* piece2=new proj_2D (z.top_view);


        this->board= new Board (*piece,*piece1,*piece2,degree,turn);
        //board->cur_player=cur_player;

        connect(this->board,&Board::nextturn,[=](){
            this->board->close();
            emit nextCube();
        });
        connect(this->timer,&MyTimer::timepass,[=](){


            this->hide();
            this->board->show();
        });
        connect(this->board,&Board::clickback,[=](){
            this->board->close();
            emit returnback();
        });
}
void BigCube::findall(Init_3D & a){


     init_array.push_back(&a);//保存当前的状态

    for(int i=0;i<a.jieshu;i++){
        for (int j=0;j<a.jieshu;j++) {
            for(int k=0;k<a.jieshu;k++){

                    if(a.my01Array[i][j][k]==1&&a.check(i,j,k)){


                    dfs(a,i,j,k);


                }
            }

        }
    }

}
//值为1，且未被标记过，然后还可以删除，这样才可以被dfs
void BigCube::dfs(Init_3D & a,int m,int n,int  r){


     a.my01Array[m][n][r]=0;//删掉这个块
       Init_3D* b=new Init_3D(a.my01Array);//删掉以后的新的异形立方体
        init_array.push_back(b);//保存当前的状态
       //对于相邻的（在这里就是符合要求的）dfs
        int j=n;int k=r;
     for(int i=m;i<a.jieshu;i++){
         for (;j<a.jieshu;j++) {
             for(;k<a.jieshu;k++){

                     if(b->my01Array[i][j][k]==1&&b->check(i,j,k)){
                     dfs(*b,i,j,k);
                 }
             }
              k=0;
         }
         j=0;
     }
     a.my01Array[m][n][r]=1;//做完以后要恢复，不然这个块就被删没了
}

void BigCube::dispalyall(){
    int num=this->init_array.size();
    qDebug()<<num;
    //int jieshu=init_array[0]->jieshu;
    for(int i=0;i<num;i++){

        init_array[i]->print_01();
        cout<<"\n";
    }

}
void BigCube:: writeall(){

   //以二进制的方式写入
    int num=this->init_array.size();
    ofstream out(file1,ios::trunc|ios::binary);
    if(!out){cout<<"open failed!";}
    else{

    for(int i=0;i<num;i++){
     temp_encoder.clear();//清空上一回
     encoder(*init_array[i]);
    QVector3D p;
     //对每一个进行写入
     for(int i=0;i<temp_encoder.size();i++){
         p=temp_encoder[i];
        out.write((char*)&p,sizeof p);
     }

    }

    }
    out.close();

}
void BigCube::encoder(Init_3D&a){
    //把a的01矩阵的1的坐标存入temp_encoder
    for(int x=0;x<a.jieshu;x++){
        for(int y=0;y<a.jieshu;y++){
            for(int z=0;z<a.jieshu;z++){
                if(a.my01Array[x][y][z]==1){
                    temp_encoder.push_back(QVector3D(x,y,z));
                }
            }
        }
    }


}
void BigCube::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)
    QPainter painter(this);
    //先画一个白底黑框
    painter.fillRect(this->rect(), Qt::white);
    QPen pen(Qt::black);
    painter.setPen(pen);
    painter.drawRect(this->rect().adjusted(0, 0, -1, -1)); //右下角会超出范围


    //投影矩阵
    QMatrix4x4 perspective_mat;//单位矩阵
    perspective_mat.perspective(projectionFovy, 1.0f, 0.1f, 100.0f);
    //qDebug()<<"透视投影矩阵"<<perspective_mat;
    //观察矩阵
    QMatrix4x4 view_mat;
    view_mat.translate(0.0f, 0.0f, -10.0f);
    // qDebug()<<"观察矩阵"<<view_mat;

    view_mat.rotate(rotationQuat);
    QList<QVector3D> vertex_list; //和矩阵运算后的顶点


    //矩形边框参考大小
    const int cube_width = (width() > height() ? height() : width()) / 5;

    for(int m=0;m<vertexArr.count();m++){
        for (int i = 0; i < vertexArr[m].count(); i++)
        {
            //以异形立方体中心为原点旋转

            QVector3D vertex = perspective_mat * view_mat * vertexArr[m].at(i);
            vertex_list.push_back(vertex);
        }
            //把原点移到中间来，方便绘制
            painter.save();
            painter.translate(width() / 2, height() / 2);
            //绘制front和back六个面，先计算路径再绘制
            QList<QPainterPath> element_path_list; //每个面路径

            QList<int> element_front_list;         //elementArr中表面的index
            //计算每个表面
            for (int i = 0; i < 6; i++)
            {
                //每个面四个顶点
                const QVector3D &vt0 = vertex_list.at(elementArr.at(i).at(0));
                const QVector3D &vt1 = vertex_list.at(elementArr.at(i).at(1));
                const QVector3D &vt2 = vertex_list.at(elementArr.at(i).at(2));
                const QVector3D &vt3 = vertex_list.at(elementArr.at(i).at(3));


                //单个面的路径，面根据大小等比放大
                QPainterPath element_path;
                element_path.moveTo(getPoint(vt0, cube_width));
                element_path.lineTo(getPoint(vt1, cube_width));
                element_path.lineTo(getPoint(vt2, cube_width));
                element_path.lineTo(getPoint(vt3, cube_width));
                element_path.closeSubpath();

                element_front_list.push_back(i);
                element_path_list.push_back(element_path);
            }



            //根据计算好的路径绘制
            painter.setRenderHint(QPainter::Antialiasing, true);
            //画表面
            //qDebug()<<element_front_list.count();
            for (auto index : element_front_list)
            {

                painter.fillPath(element_path_list.at(index), Qt::cyan);
            }

            painter.restore();
            element_front_list.clear();
            vertex_list.clear();


        }
        painter.drawText(20, 30, "Drag Moving");
}

QPointF BigCube::getPoint(const QVector3D &vt, int w) const
{
    //可以用z来手动计算远小近大，也可以矩阵运算
    //const float z_offset=vt.z()*0.1;

    //cout<<vt.x()* w<<" "<<vt.y()* w<<endl;
    //return QPointF{ vt.x()*w*(1+z_offset), vt.y()*w*(1+z_offset) };
    return QPointF{vt.x() * w, vt.y() * w};
}

void BigCube::mousePressEvent(QMouseEvent *event)
{
    mousePressed = true;
    mousePos = event->pos();
    QWidget::mousePressEvent(event);
}


void BigCube::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed)
    {
        QVector2D diff =   QVector2D(event->pos())-QVector2D(mousePos);
        mousePos = event->pos();
        QVector3D n = QVector3D( -diff.y(),diff.x(), 0.0).normalized();
        rotationAxis = (rotationAxis + n).normalized();
        //不能对换乘的顺序
        rotationQuat = QQuaternion::fromAxisAndAngle(rotationAxis, 2.0f) * rotationQuat;
         update();
    }
    QWidget::mouseMoveEvent(event);
}

void BigCube::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
    QWidget::mouseReleaseEvent(event);
}

void BigCube::wheelEvent(QWheelEvent *event)
{

    event->accept();
    //fovy越小，模型看起来越大
    if (event->delta() < 0)
    {
        //鼠标向下滑动为-，这里作为zoom out
        projectionFovy += 0.5f;
        if (projectionFovy > 90)
            projectionFovy = 90;
    }
    else
    {
        //鼠标向上滑动为+，这里作为zoom in
        projectionFovy -= 0.5f;
        if (projectionFovy < 1)
            projectionFovy = 1;
    }
    update();
}



