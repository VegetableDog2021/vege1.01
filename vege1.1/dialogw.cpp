#include "dialogw.h"
#include "ui_dialogw.h"

Dialogw::Dialogw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogw)
{   ReadModel();

    ui->setupUi(this);
    this->setWindowTitle( tr("board") );
    outputStr = "";
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
    update();
}
void Dialogw::showKeyboard(QPoint pt, QRect focusWidget)
{   ui->dwidget->clearImage();
    update();
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
void Dialogw::ReadModel()//读取模型
{
      try
      { module = torch::jit::load("./model/model.pt");

      }
       catch (const c10::Error& e) {
       std::cerr << "error loading the model\n";
     }
     std::cout << "Load model ok\n";
}

QString Dialogw::getcharacter(cv::Mat image)//获取文字
{
    cv::Mat image_transfomed;
    cv::resize(image, image_transfomed, cv::Size(64, 64));
    torch::Tensor tensor_image = torch::from_blob(image_transfomed.data,
                                {image_transfomed.rows, image_transfomed.cols,1},torch::kByte);
        tensor_image = tensor_image.permute({2,0,1});
        tensor_image = tensor_image.toType(torch::kFloat);
        tensor_image = tensor_image.div(255);
        tensor_image = tensor_image.unsqueeze(0);
        at::Tensor output = module.forward({tensor_image}).toTensor();

        auto prediction = output.argmax(1);
        std::cout << "prediction:" << prediction << std::endl;

        int maxk = 10;
        auto top10 = std::get<1>(output.topk(maxk, 1, true, true));
        std::vector<int> res;
        for (auto i = 0; i < maxk; i++) {
            res.push_back(top10[0][i].item().toInt());
        }
        for (auto i : res) {
            std::cout << i << " ";
        }
        std::cout << "\n";

        std::cout<<"print"<<std::endl;
        Json::Reader reader;
        Json::Value labels;
        std::ifstream read_file("model/char_utf.json", std::ios::binary);
        reader.parse(read_file, labels);
        string geten;
        for(int i=0; i<10;i++){
            int idx = res[i];
            char b[4];int a=idx;
            ostringstream  ostr;
            ostr << a ;
            string str(ostr.str());
            std::cout << labels[str].asString() << " ";
            
            geten=geten+labels[str].asString() ;
            if(i!=9)
            geten=geten+",";
       }
       
        std::cout<<geten<<endl;
        return QString::fromStdString(geten);
}
QString Dialogw::findchar()
{ QString returnChinese;
    QImage image = ui->dwidget->getImage();
    Mat mat =toMat(image);
    mat=getGrayImg(mat);
    returnChinese = getcharacter(mat);
    return returnChinese;
}

void Dialogw::focusChanged(QWidget *, QWidget *nowWidget)//
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


//汉字按钮的设置
void Dialogw::setcharBt()
{


    for (int i = 0; i < 10; i++)
    {
        zhList.at(i)->setText("");
    }

    QString ChineseStr = findchar();
    if (ChineseStr != "")
    {QStringList listcharacter = ChineseStr.split(",");
    for(int i = 0; i< listcharacter.size();++i)
    {
        QString tmp = listcharacter.at(i);
        qDebug()<<"tmp ="<< tmp;
        ((QPushButton *)zhList.at(i))->setText(tmp);

    }
	}
    
    return;

}


//十个按钮点击
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
    ui->dwidget->clearImage();
    update();

}

// 退格键
void Dialogw::on_del_clicked()
{
        QString str = lineEdit->text();
        lineEdit->setText(str.left(str.length() - 1));

}
void  Dialogw::on_okButton_clicked()
{
    setcharBt();

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
