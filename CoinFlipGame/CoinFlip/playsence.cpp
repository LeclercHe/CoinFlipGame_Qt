#include "playsence.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<QFont>
#include<QPixmap>
#include<mycoin.h>
#include<dataconfig.h>
#include<QPushButton>
#include<QPropertyAnimation>
#include<QSoundEffect>
//PlaySence::PlaySence(QWidget *parent)
//    : QMainWindow{parent}
//{

//}

PlaySence::PlaySence(int levelNum )
{
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/image/Coin0001"));
    //设置标题
//    QString str = QString("关卡%1").arg(levelNum);
    this->setWindowTitle("翻金币");

    //设置菜单栏
    QMenuBar * menBar = menuBar();
    setMenuBar(menBar);
    //创建开始菜单
    QMenu *  startMenu = menBar->addMenu("开始");
    //创建退出项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出
    connect(quitAction, &QAction::triggered , [=](){
        this->close();
    });


    //返回按钮
    MyPushButton * returnBtn = new MyPushButton(":/res/image/BackButton.png",":/res/image/BackButtonSelected.png");
    returnBtn->setParent(this);
    returnBtn->move(this->width() - returnBtn->width(),this->height()-returnBtn->height());
    connect(returnBtn, &QPushButton::clicked , [=](){
        //延时返回
        QTimer::singleShot(500,[=](){
            emit this->playSceneBack();

        });
    });
//    //胜利音效
//    QSoundEffect * sound = new QSoundEffect(this);
//    sound->setSource(QUrl::fromLocalFile(":/res/music/CoinFlip_res_LevelWinSound.mav"));
    //显示关卡数
    QLabel *label = new QLabel;
    label->setParent(this);
    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str = QString("Level: %1").arg(levelNum);
    //将字体设置到标签label中
    label->setFont(font);
    label->setText(str);
    label->setGeometry(30,this->height() - 50, 120,50);


    dataConfig config;

    //初始化每个关卡的二维数组
    for(int i=0; i<4 ; i++ )
    {
        for(int j=0 ; j<4; j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }


    //显示胜利图片
    QLabel *winLabel = new QLabel;
    QPixmap winPix;
    winPix.load(":/res/image/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,winPix.width(),winPix.height());
    winLabel->setParent(this);
    winLabel->setPixmap(winPix);
    winLabel->move((this->width() - winPix.width())*0.5 , -winPix.height());

    //显示金币背景图案
    for (int i=0 ; i<4 ; i++)
    {
        for(int j=0 ; j< 4; j++)
        {
            //绘制图片背景
            QLabel *label2 = new QLabel;
            QPixmap pix= QPixmap(":/res/image/BoardNode.png");
            label2->setGeometry(0,0,pix.width(),pix.height());
            label2->setPixmap(pix);
            label2->setParent(this);
            label2->move(57+i*50 , 200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str=":/res/image/Coin0001.png";
            }
            else
            {
                str=":/res/image/Coin0008.png";
            }

            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50 , 204+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];//1正面 0反面

            //将金币放入到 金币二维数组 以维护
            coinBtn[i][j]=coin;

            //点击金币 进行翻转
            connect(coin, &QPushButton::clicked , [=](){

                //点击按钮 将所有按钮先都禁用
                for(int i =0 ; i<4 ;i++)
                {
                    for(int j =0 ; j<4 ;j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] = gameArray[i][j] ==0 ? 1 : 0;

                //延时翻转
                QTimer::singleShot(300,[=](){
                    //翻转周围
                    if(coin->posX+1 <= 3)//翻转右侧
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY] ==0 ? 1 : 0;
                    }
                    if(coin->posX-1 >= 0)//翻转左侧
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY] ==0 ? 1 : 0;
                    }
                    if(coin->posY-1 >= 0)//翻转上侧
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX][coin->posY-1] ==0 ? 1 : 0;
                    }
                    if(coin->posY+1 <= 3)//翻转下侧
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX][coin->posY+1] ==0 ? 1 : 0;
                    }


                    //翻转完周围金币后，将所有金币解开禁用
                    for(int i =0 ; i<4 ;i++)
                    {
                        for(int j =0 ; j<4 ;j++)
                        {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0 ; i<4; i++)
                    {
                        for(int j = 0 ; j<4; j++)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        for(int i = 0 ; i<4; i++)
                        {
                            for(int j = 0 ; j<4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }


                        //将胜利图片出现
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+124,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                        //sound->play();
                    }
                });

            });
        }
    }

}


 void PlaySence::paintEvent(QPaintEvent *event)
 {
     QPainter painter(this);
     QPixmap pixmap;
     pixmap.load(":/res/image/PlayLevelSceneBg.png");
     painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

     //背景图标
     pixmap.load(":/res/image/Title");
     pixmap = pixmap.scaled(pixmap.width()*0.5 , pixmap.height()*0.5);
     painter.drawPixmap(20,30,pixmap);

 }
