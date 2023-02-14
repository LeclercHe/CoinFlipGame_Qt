#include "mypushbutton.h"
#include <QDebug>
#include<QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent)
//    : QPushButton{parent}
//{

//}


MyPushButton:: MyPushButton(QString normalImg , QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pixmap;
    bool ret = pixmap.load(normalImg);
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }

    //设置按钮固定大小
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

}


void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+20,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}


//重写按钮按下 和 释放事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath != " ")// 如果传入的图片不为空，则切换图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(this->pressImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        //设置按钮固定大小
        this->setFixedSize(pixmap.width(),pixmap.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pixmap);
        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != " ")// 如果传入的图片不为空，则切换初始图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(this->normalImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        //设置按钮固定大小
        this->setFixedSize(pixmap.width(),pixmap.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pixmap);
        //设置图标大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }


    return QPushButton::mouseReleaseEvent(e);
}
