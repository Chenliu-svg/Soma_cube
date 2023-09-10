#ifndef MAINSCENE_H
#define MAINSCENE_H
#include<QPainter>
#include <QMainWindow>
#include"chooselevel.h"
#include"toolwindow.h"
#include"shezhiwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent*) override;

private:
    Ui::MainScene *ui;

    ChooseLevel* chooselevel=0;

    ToolWindow* toolwindow=0;

    ShezhiWindow* shezhiwindow=0;
};
#endif // MAINSCENE_H
