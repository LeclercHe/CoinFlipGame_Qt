#include "mycoin.h"
#include<QDebug>
#include<QTimer>
//MyCoin::MyCoin(QWidget *parent)
//    : QPushButton{parent}
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret= pix.load(btnImg);
    if(!ret)
    {
        qDebug() << "图片加载失败";
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面信号， 并翻转金币
    connect(timer1, &QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/image/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //如果翻完了 重置min=1
        if(this->min > this->max)
        {
            min = 1;
            isAnimation = false;//金币停止了动画
            timer1->stop();
        }
    });
    //监听反面翻正面信号， 并翻转金币
    connect(timer2, &QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/image/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //如果翻完了 重置min=1
        if(this->max < this->min)
        {
            max = 8;
            isAnimation = false;//金币停止了动画
            timer2->stop();
        }
    });
}

//改变正反面标志方法
void MyCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        isAnimation = true;//开始做翻转动画
        this->flag=false;

    }
    else
    {
        timer2->start(30);
        isAnimation = true;//开始做翻转动画
        this->flag=true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation | this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}
