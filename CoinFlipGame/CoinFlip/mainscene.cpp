#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<mypushbutton.h>
#include<QTimer>
#include<QSoundEffect>
#include<QtMultimedia>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置主场景
    //设置界面宽度
    setFixedSize(340,588);
    //设置图标
    setWindowIcon(QIcon(":/res/image/Coin0001.png"));
    //设置标题
    setWindowTitle(QString("小贺带你翻金币"));

    //退出按钮实现
    connect(ui->actionquit , &QAction::triggered, [=](){
        this->close();
    });

}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景图标
    pix.load(":/res/image/Title.png");
    //图片缩放
    pix = pix.scaled(pix.width()*0.5 , pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

//    //设置开始音效
//    QSoundEffect * sound = new QSoundEffect(this);
//    sound->setSource(QUrl::fromLocalFile(":/res/music/CoinFlip_res_TapButtonSound"));

    //设置开始按钮
    MyPushButton * startbtn = new MyPushButton(":/res/image/MenuSceneStartButton");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5 - startbtn->width()*0.5, this->height()*0.7);
    startbtn->show();

    //实例化选择关卡场景对象
    chooseScene= new ChooseLevelScene;

    //监听选择关卡的返回按钮信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack , [=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();//选择场景隐藏
        this->show();//主场景重现
    });


    connect(startbtn , &QPushButton::clicked , [=](){
        //播放音乐
        //sound->play();
        //做弹起特效
        startbtn->zoom1();
        startbtn->zoom2();

        //延时进入关卡场景
        QTimer::singleShot(500,this,[=](){
            //设置chooseScene场景位置
            chooseScene->setGeometry(this->geometry());
            //进入选择关卡场景中
            //主场景隐藏
            this->hide();
            //显示关卡场景
            chooseScene->show();

        });

    });

}



MainScene::~MainScene()
{
    delete ui;
}
