#ifndef GLOBAL_H
#define GLOBAL_H
#include<QString>
#include<QSet>
#include<string>
extern  std::string file1;
extern  QString file0;
class Player{
public:

    int id;
    int getScore(){
        return score;
    }
    void setScore(int s){
        score=s;
    }
    QString getName(){
        return name;
    }

    void setName(QString  s){
        name=s;
    }
private:
    QString name;
    int score;


};
extern Player* cur_player;
extern int turn;
extern int view;
//void dfs(QVector<QVector<QVector<int>>>);
//extern QSet<QVector<QVector<QVector<int>>>> init_array1;
//bool check(QVector<QVector<QVector<int>>> a,int i,int j,int k);
//void generate_2D(QVector<QVector<QVector<int>>> my01Array,QVector<QVector<int>>*front_view, QVector<QVector<int>>*left_view);


#endif // GLOBAL_H
