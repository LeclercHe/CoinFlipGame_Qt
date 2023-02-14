#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    //参数：金币路径还是银币路径
    MyCoin(QString btnImg);

    //金币属性
    int posX;
    int posY;
    bool flag;

    //改变标志方法
    void changeFlag();
    QTimer *timer1;//正面翻反面定时器
    QTimer *timer2;//反面翻正面定时器
    int min =1;
    int max =8;

    //执行动画标志
    bool isAnimation = false;

    //重新鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //胜利标志
    bool isWin= false;
signals:

};

#endif // MYCOIN_H
