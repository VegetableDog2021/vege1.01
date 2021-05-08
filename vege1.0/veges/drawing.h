#ifndef DRAWING_H
#define DRAWING_H
#include "header.h"
#include <QWidget>

namespace Ui {
class drawing;
}

class drawing : public QWidget
{
    Q_OBJECT

public:
    explicit drawing(QWidget *parent = 0);
    ~drawing();
    QImage getImage();//获取当前画板的图片
    bool saveImage(QString filePath);//将画板中的图片保存下来
    void clearImage();//清空画板
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    Ui::drawing *ui;
    QPixmap pix;//画板中的图片变量

    QPoint lastPoint;//鼠标上一次的位置
    QPoint endPoint;//鼠标当前的位置

    QPen pen;
    QFont font;
};

#endif // DRAWING_H
