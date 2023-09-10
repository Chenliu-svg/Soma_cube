#include "ranklist.h"
#include<algorithm>
#include<QHorizontalBarSeries>
QT_CHARTS_USE_NAMESPACE
using std::sort;
ranklist::ranklist(QVector<Player*> PlayerList,QWidget*parent )
{
    int num=PlayerList.count();
    QHorizontalBarSeries *series = new QHorizontalBarSeries();
    //将玩家按照分数排序
    sort(PlayerList.begin(),PlayerList.end(),[](Player* a,Player* b){
        return a->getScore()<b->getScore();
    });

    //每个人一个bar
   QBarSet* set;
    QStringList categories;
    setWindowIcon(QIcon(":/pic/icon.png"));

    set=new QBarSet("PlayerList");
    for(int i=0;i<num;i++){

        *set<<PlayerList[i]->getScore();
        categories<<PlayerList[i]->getName();

    }
    series->append(set);
    series->setBarWidth(this->width()*0.0005);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsCenter);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("RankList");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->setAxisY(axisY,series);

    chart->legend()->setVisible(false);
    chart->setTheme(QChart::ChartThemeDark);

    QFont font;
    font.setBold(true);
         font.setPixelSize(30);
         chart->setTitleFont(font);
         chart->setTitleBrush(QBrush(Qt::white));

    QFont labelsFont;
    labelsFont.setFamily("HGB4X_CNKI");
    labelsFont.setBold(true);

         labelsFont.setPixelSize(20);
         axisY->setLabelsFont(labelsFont);
         QBrush axisBrush(Qt::white);

              axisY->setLabelsBrush(axisBrush);
              QPen pen;
              pen.setColor(Qt::black);
 axisY->setLinePen(pen);


        // axisX->setGridLineVisible(false);
              axisY->setGridLineVisible(false);



    QChartView *chartView = new QChartView(chart);


    setCentralWidget(chartView);

    resize(1000,700);
    //设置返回按钮
    MyPushButtom * tuichubtn=new MyPushButtom(":/pic/tuichu.png");

    tuichubtn->setParent(this);

    tuichubtn->move(this->width()*0.92-tuichubtn->width()*0.5,this->height()*0.88);

    connect(tuichubtn,&MyPushButtom::clicked,[=](){
    tuichubtn->zoom1();
    tuichubtn->zoom2();
    emit this->clickBack();

    });



}
