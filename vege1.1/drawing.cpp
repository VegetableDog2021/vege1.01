#include "drawing.h"
#include "ui_drawing.h"


drawing::drawing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::drawing)
{
    ui->setupUi(this);
    //如果初始值为正值，会在界面绘制一个点
    lastPoint=endPoint=QPoint(-20,-20);
    pix.fill(Qt::white);//填充图片的背景

    pix = QPixmap(this->width(),this->height());

    pen.setColor(Qt::black);
    pen.setWidth(5);

    font.setWeight(5);
    font.setPixelSize(2);
}

drawing::~drawing()
{
    delete ui;
}

QImage drawing::getImage()
{
    return pix.toImage();
}

bool drawing::saveImage(QString filePath)
{
    return pix.save(filePath);
}
//清空界面图片
void drawing::clearImage()
{
    lastPoint=endPoint=QPoint(-20,-20);
    pix.fill(Qt::white);
    update();
    printf("clean");
}
//绘图
void drawing::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    //先绘制在图片上
    QPainter pp(&pix);
    pp.setPen(pen);
    pp.setFont(font);
    pp.drawLine(lastPoint,endPoint);
    pp.setRenderHint(QPainter::HighQualityAntialiasing,true);

    lastPoint = endPoint;
    //再绘制再界面上
    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}
//鼠标按下
void drawing::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastPoint = event->pos();
    }
    endPoint = lastPoint;
}
//鼠标松开
void drawing::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        endPoint = event->pos();
        update();
    }
}
//鼠标移动
void drawing::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        endPoint = event->pos();
        update();
    }
}
//如果界面的尺寸发生了调整
void drawing::resizeEvent(QResizeEvent *event)
{
    pix = QPixmap(event->size());
    pix.fill(Qt::white);
    update();
}
