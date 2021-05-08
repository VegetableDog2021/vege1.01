#ifndef DIALOGW_H
#define DIALOGW_H

#include <QDialog>
#include <QButtonGroup>
#include <QList>
#include <QLineEdit>
namespace Ui {
class Dialogw;
}

class Dialogw : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogw(QWidget *parent = 0);
    ~Dialogw();
    void showKeyboard(QPoint pt, QRect focusWidget);
    void hideKeyboard();
    bool isVisible() const;
    QString outputStr;
    QString findchar();
    void  setcharBt();

signals:
    void commit(QString str);
private slots:
    void slot_charBtClicked(QAbstractButton *bt);
    void on_del_clicked();
    void on_down_clicked();
    void on_up_clicked();
    void on_close_clicked();
    void on_clean_clicked();
    void focusChanged(QWidget *, QWidget *nowWidget);
private:
    Ui::Dialogw *ui;
    QList<QAbstractButton *> zhList;
    int pageAll; // 总页数
    int curPage; // 当前页
    QLineEdit *lineEdit;
    QStringList pageList; // 查找出的字符串10个10个分割
};

#endif // DIALOGW_H
