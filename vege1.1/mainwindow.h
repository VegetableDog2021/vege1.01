
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialogw.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QSize>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Dialogw *board ;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H








