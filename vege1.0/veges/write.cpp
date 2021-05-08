#include "write.h"
#include "mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QSize>
#include <QWidget>
write::write()
{  setMouseTracking(true);
    this->press = false;

}
write::write(QWidget *p) : QLabel(p)
{  setMouseTracking(true);
    this->press = false;

}
//绘画，每次update的时候执行
void write::paintEvent(QPaintEvent *event)
{   QLabel::paintEvent(event);
    QPainter painter(this);
    QPen pen;                     //创建画笔
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(5);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);          //画板设置画笔

    int i = 0;                      //把每一次鼠标移动的地方进行画点
    while(point_list.size()!=0 && i != point_list.size())
    {
        painter.drawPoint(point_list.at(i));
        i++;
    }

}

//鼠标左键按下，开始记录坐标
void write::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        this->press = true;
    }
}

//鼠标移动事件
void write::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(this->press)     //只有鼠标被按下的时候才记录坐标
        {
            point = event->pos();       //记录坐标
            point_list.append(point);   //记录每一次移动的坐标
            update();                   //更新，让画笔画画
        }

    }
}

//鼠标松开，停止记录
void write::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->press = false;
    }
}

void write::clean( )
{   point_list.clear();     //清空鼠标坐标记录
    update();               //更新，让画笔画画*/
}
