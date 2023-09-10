#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <QMainWindow>
#include"bigcube.h"
#include<QPainter>
class ToolWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ToolWindow(QWidget *parent = nullptr);

    bool rational();
    void randomDisplay();
    void show_big();

    void paintEvent(QPaintEvent* ) override;


  QVector<QVector<QVector<int>>> show3DArray;
 QLabel* tip;
 BigCube* big;
 User_define* shitu;
signals:
void clickBack();
};


#endif // TOOLWINDOW_H
