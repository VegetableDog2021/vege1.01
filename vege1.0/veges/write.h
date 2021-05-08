#ifndef WRITE_H
#define WRITE_H
#include <QLabel>
#include <QPoint>
#include <QColor>
#include <QPaintEvent>
#include <QImage>
#include <QPixmap>
#include <QWidget>

class write : public QLabel
{
public:
    write();
    write(QWidget *p=0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event) override;
    void clean();
private:
    bool press;
    QPoint point;
    QList<QPoint> point_list;
};

#endif // WRITE_H
