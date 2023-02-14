#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include<playsence.h>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    //创建游戏场景 对象指针
    PlaySence *play = NULL;

signals:
    //自定义信号，告诉主场景， 点击了返回
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
