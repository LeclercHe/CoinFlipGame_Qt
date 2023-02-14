#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<mainscene.h>
#include<QTimer>
#include<QLabel>
#include<playsence.h>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //选择关卡场景配置
    //设置大小
    this->setFixedSize(340,588);
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置图标
    this->setWindowIcon(QPixmap(":/res/image/Coin0001"));

    //设置菜单栏
    QMenuBar * menBar = menuBar();
    setMenuBar(menBar);
    //创建开始菜单
    QMenu *  startMenu = menBar->addMenu("开始");
    //创建退出项
    QAction * quitAction = startMenu->addAction("退出");
    //
    connect(quitAction, &QAction::triggered , [=](){
        this->close();
    });


    //设置返回按钮
    MyPushButton * returnBtn = new MyPushButton(":/res/image/BackButton.png",":/res/image/BackButtonSelected.png");
    returnBtn->setParent(this);
    returnBtn->move(this->width() - returnBtn->width(),this->height()-returnBtn->height());
    connect(returnBtn, &QPushButton::clicked , [=](){
        //延时返回
        QTimer::singleShot(500,[=](){
            //告诉主场景我返回了，主场景监听ChooseLevelScene的返回按钮
            emit this->chooseSceneBack();
        });
    });


    //设置选择关卡的按钮
    for (int i =0 ; i<20 ; i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/image/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(22+i%4 * 80 , 120+i/4 *80);//*****good****

        //监听关卡按钮
        connect(menuBtn, &MyPushButton::clicked , [=](){
            //进入游戏场景
            this->hide();
            play = new PlaySence(i+1);
            //设置游戏场景初始位置
            play->setGeometry(this->geometry());
            play->show();


            connect(play, &PlaySence::playSceneBack, [=](){
                this->setGeometry(play->geometry());
                play->hide();
                delete play;
                play = NULL;
                this->show();
            });
        });


        //加文字
        QLabel *label = new QLabel(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(22+i%4 * 80 , 120+i/4 *80);

        //设置 label上的文字对齐方式  水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标可以进行穿透label  51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/image/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //背景图标
    pixmap.load(":/res/image/Title");
    painter.drawPixmap(20,30,pixmap);

}
