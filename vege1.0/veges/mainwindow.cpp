#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->lineEdit->installEventFilter(this);
    board = new Dialogw(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(board);
    }

    return QWidget::eventFilter(watched, event);
}

void MainWindow::callKeyBoard(Dialogw *board )
{
       board->show();

}
void MainWindow::killKeyBoard(Dialogw *board )
{
       board->hide();

}
*/

//确定按键
void MainWindow::on_pushButton_clicked()
{
    /*QPixmap pixmap = QPixmap::grabWidget(this);     //把Widget窗口内容转为QPixmap
    QSize picSize(28,28);                           //设置修改的大小为28*28
    QPixmap ret = pixmap.scaled(picSize);           //重新修改QPixmap的大小

    ret.save("num.png"); //保存QPixmap为png图片*/
}

//清除按键
void MainWindow::on_pushButton_2_clicked()
{//ui->dwidget->clearImage();
}

