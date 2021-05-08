#ifndef BOARDW_H
#define BOARDW_H

#include <QGroupBox>

namespace Ui {
class boardw;
}

class boardw : public QGroupBox
{
    Q_OBJECT

public:
    explicit boardw(QWidget *parent = 0);
    ~boardw();

private:
    Ui::boardw *ui;
};

#endif // BOARDW_H
