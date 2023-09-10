#ifndef RANKLIST_H
#define RANKLIST_H

#include <QMainWindow>
#include"global.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>
#include<QVector>
#include"mypushbuttom.h"
class ranklist : public QMainWindow
{
    Q_OBJECT
public:
     ranklist(QVector<Player*> PlayerList,QWidget *parent = nullptr);

signals:
void clickBack();
};

#endif // RANKLIST_H
