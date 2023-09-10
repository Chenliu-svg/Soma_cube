#ifndef CHOOSELEVEL_H
#define CHOOSELEVEL_H
#include<QPainter>
#include<QLineEdit>
#include<QTextCodec>
#include<string>
#include"choosenandu.h"
#include <QMainWindow>
#include"global.h"
#include"ranklist.h"
#include<QComboBox>
#include<QDir>
class ChooseLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevel(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* ) override;
    void addNewPlayer(QString s_name);

    void display_rank();
    void update_line();
    QVector<Player*> PlayerList;
    QLineEdit* inputLine;
    ranklist* rank;
     QComboBox* choose_player;
    //Player* cur_player=0;
private:
    Choosenandu * choosenandu=0;


signals:
//自定义信号，告诉主场景，点击了返回
//自定义信号只要声明，不需要实现
//在需要的地方，使用emit发送
    void clickBack();
};







#endif // CHOOSELEVEL_H
