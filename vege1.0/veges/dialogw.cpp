#include "dialogw.h"
#include "ui_dialogw.h"

Dialogw::Dialogw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogw)
{
    ui->setupUi(this);
    this->setWindowTitle( tr("board") );
    outputStr = "";
    pageAll = 0;
    curPage = 0;
    /*setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);//设置子窗口属性
    this->setParent(parent);//设置依附的窗口*/
    //lineEdit = LineEdit;
    QButtonGroup *hanziGroup = new QButtonGroup();//汉字选项
    hanziGroup->addButton(ui->zh_1, 1);
    hanziGroup->addButton(ui->zh_2, 2);
    hanziGroup->addButton(ui->zh_3, 3);
    hanziGroup->addButton(ui->zh_4, 4);
    hanziGroup->addButton(ui->zh_5, 5);
    hanziGroup->addButton(ui->zh_6, 6);
    hanziGroup->addButton(ui->zh_7, 7);
    hanziGroup->addButton(ui->zh_8, 8);
    hanziGroup->addButton(ui->zh_9, 9);
    hanziGroup->addButton(ui->zh_10, 10);
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));
    connect( hanziGroup, SIGNAL(buttonClicked(QAbstractButton*)),
             this, SLOT(slot_charBtClicked(QAbstractButton*)));
    zhList = hanziGroup->buttons();
}
void Dialogw::showKeyboard(QPoint pt, QRect focusWidget)
{
    QWidget::show();
}

void Dialogw::hideKeyboard()
{
    QWidget::hide();
}

bool Dialogw::isVisible() const
{
    return QWidget::isVisible();
}
QString Dialogw::findchar()
{ QString returnChinese;
  return returnChinese;
}
void Dialogw::focusChanged(QWidget *, QWidget *nowWidget)
{
#if 1
    if (nowWidget != 0 && !this->isAncestorOf(nowWidget))
    {
        if (nowWidget->inherits("QLineEdit"))
        {
            lineEdit = (QLineEdit *)nowWidget;

            QPoint movePoint;

            // 鼠标点击位置坐标

                movePoint = QPoint(QCursor::pos().x(), QCursor::pos().y());
                update();

            this->move(movePoint);
            this->repaint();
            this->setVisible(true);
        }
        else
        {
            lineEdit = 0;
            this->setVisible(false);

        }
    }
#endif
}


/* 汉字按钮的设置 */
void Dialogw::setcharBt()
{

    for (int i = 0; i < 10; i++)
    {
        zhList.at(i)->setText("");
    }

    QString ChineseStr = findchar();

    ui->up->setEnabled(false);
    ui->down->setEnabled(false);

    if (ChineseStr != "")
    {
        int ChineseStrCount = ChineseStr.length();
        // 10字以内汉字个数
        if (ChineseStrCount <= 10)
        {
            for (int i = 0; i < ChineseStrCount; i++)
            {
                ((QPushButton *)zhList.at(i))->setText(ChineseStr.at(i));
            }
            return;
        }

        // 大于10字
        for (int i = 0; i < 10; i++)
        {
            ((QPushButton *)zhList.at(i))->setText(ChineseStr.at(i));
        }

        ui->up->setEnabled(true);
        ui->down->setEnabled(true);

    }//if
}
void Dialogw::on_up_clicked()
{
    curPage++;

    if (curPage > pageAll)
    {
        curPage = 1;
    }

    for (int i = 0; i < 10; i++)
    {
        zhList.at(i)->setText("");
    }

    QString str = pageList.at(curPage-1);
    qDebug() << str;
    for (int i = 0; i < str.length(); i++)
    {
        zhList.at(i)->setText(str.at(i));
    }
}

void Dialogw::on_down_clicked()
{
    curPage--;
    if (curPage == 0)
    {
        curPage = pageAll;
    }

    for (int i = 0; i < 10; i++)
    {
        zhList.at(i)->setText("");
    }

    QString str = pageList.at(curPage-1);
    for (int i = 0; i < str.length(); i++)
    {
        zhList.at(i)->setText(str.at(i));
    }
}

/* 十个按钮点击 */
void Dialogw::slot_charBtClicked(QAbstractButton *bt)
{
    QPushButton *tmp = (QPushButton *)bt;
    QString str = lineEdit->text();
    str.append(tmp->text());
    lineEdit->setText(str);
    for (int i = 0; i < 10; i++)
    {
        zhList.at(i)->setText("");
    }

    ui->down->setEnabled(false);
    ui->up->setEnabled(false);
}

/* 退格键 */
void Dialogw::on_del_clicked()
{
        QString str = lineEdit->text();
        lineEdit->setText(str.left(str.length() - 1));

}

void Dialogw::on_clean_clicked()
{
       ui->dwidget->clearImage();
       update();
}
void Dialogw::on_close_clicked()
{
        this->hide();
}
Dialogw::~Dialogw()
{
    delete ui;
}
