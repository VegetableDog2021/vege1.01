#ifndef DIALOGW_H
#define DIALOGW_H
#include "header.h"
#include <QDialog>
#include <QButtonGroup>
#include <QList>
#include <QLineEdit>
using namespace std;
namespace Ui {
class Dialogw;
}

class Dialogw :public QDialog
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
    void ReadModel();
    QString getcharacter(cv::Mat image);

signals :
    void commit(QString str);
private slots :
    void slot_charBtClicked(QAbstractButton *bt);
    void on_del_clicked();
    void on_close_clicked();
    void on_clean_clicked();
    void on_okButton_clicked();
    void focusChanged(QWidget *, QWidget *nowWidget);

private:
    Ui::Dialogw *ui;
    torch::jit::script::Module module ;
    QList<QAbstractButton *> zhList;
    QLineEdit *lineEdit;
};

#endif // DIALOGW_H
