#ifndef PLAYSENCE_H
#define PLAYSENCE_H

#include <QMainWindow>
#include<mycoin.h>

class PlaySence : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlaySence(QWidget *parent = nullptr);
    PlaySence(int levelNum );

    int levelIndex; //内部成员属性 记录所选关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *event);

    //使用一个二维数组维护每个关卡的具体数据
    int gameArray[4][4];

    //维护金币
    MyCoin *coinBtn[4][4];

    //胜利标志
    bool isWin=true;
signals:
    //自定义返回信号
    void playSceneBack();
};

#endif // PLAYSENCE_H
