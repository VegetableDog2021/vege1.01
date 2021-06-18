/********************************************************************************
** Form generated from reading UI file 'dialogw.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGW_H
#define UI_DIALOGW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include "drawing.h"

QT_BEGIN_NAMESPACE

class Ui_Dialogw
{
public:
    QPushButton *clean;
    drawing *dwidget;
    QToolButton *toolButton;
    QPushButton *zh_1;
    QPushButton *zh_2;
    QPushButton *zh_3;
    QPushButton *zh_4;
    QPushButton *zh_5;
    QPushButton *zh_6;
    QPushButton *zh_7;
    QPushButton *zh_8;
    QPushButton *zh_9;
    QPushButton *zh_10;
    QPushButton *del;
    QPushButton *close;
    QPushButton *okButton;

    void setupUi(QDialog *Dialogw)
    {
        if (Dialogw->objectName().isEmpty())
            Dialogw->setObjectName(QStringLiteral("Dialogw"));
        Dialogw->resize(329, 345);
        Dialogw->setStyleSheet(QLatin1String("<style name=\"dialog\" parent=\"@android:style/Theme.Dialog\">\n"
"        <item name=\"android:windowFrame\">@null</item>\n"
"        <item name=\"android:windowIsFloating\">true</item>\n"
"        <item name=\"android:windowIsTranslucent\">true</item>\n"
"        <item name=\"android:windowNoTitle\">true</item>\n"
"        <item name=\"android:background\">@android:color/transparent</item>\n"
"        <item name=\"android:windowBackground\">@android:color/transparent</item>\n"
"        <item name=\"android:backgroundDimEnabled\">false</item>\n"
"        <item name=\"android:backgroundDimAmount\">0.6</item>\n"
"    </style>"));
        clean = new QPushButton(Dialogw);
        clean->setObjectName(QStringLiteral("clean"));
        clean->setGeometry(QRect(220, 320, 81, 20));
        dwidget = new drawing(Dialogw);
        dwidget->setObjectName(QStringLiteral("dwidget"));
        dwidget->setGeometry(QRect(20, 10, 261, 241));
        toolButton = new QToolButton(Dialogw);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(290, 40, 31, 31));
        zh_1 = new QPushButton(Dialogw);
        zh_1->setObjectName(QStringLiteral("zh_1"));
        zh_1->setGeometry(QRect(20, 260, 31, 31));
        zh_2 = new QPushButton(Dialogw);
        zh_2->setObjectName(QStringLiteral("zh_2"));
        zh_2->setGeometry(QRect(20, 300, 31, 31));
        zh_3 = new QPushButton(Dialogw);
        zh_3->setObjectName(QStringLiteral("zh_3"));
        zh_3->setGeometry(QRect(60, 260, 31, 31));
        zh_4 = new QPushButton(Dialogw);
        zh_4->setObjectName(QStringLiteral("zh_4"));
        zh_4->setGeometry(QRect(60, 300, 31, 31));
        zh_5 = new QPushButton(Dialogw);
        zh_5->setObjectName(QStringLiteral("zh_5"));
        zh_5->setGeometry(QRect(100, 260, 31, 31));
        zh_6 = new QPushButton(Dialogw);
        zh_6->setObjectName(QStringLiteral("zh_6"));
        zh_6->setGeometry(QRect(100, 300, 31, 31));
        zh_7 = new QPushButton(Dialogw);
        zh_7->setObjectName(QStringLiteral("zh_7"));
        zh_7->setGeometry(QRect(140, 260, 31, 31));
        zh_8 = new QPushButton(Dialogw);
        zh_8->setObjectName(QStringLiteral("zh_8"));
        zh_8->setGeometry(QRect(140, 300, 31, 31));
        zh_9 = new QPushButton(Dialogw);
        zh_9->setObjectName(QStringLiteral("zh_9"));
        zh_9->setGeometry(QRect(180, 260, 31, 31));
        zh_10 = new QPushButton(Dialogw);
        zh_10->setObjectName(QStringLiteral("zh_10"));
        zh_10->setGeometry(QRect(180, 300, 31, 31));
        del = new QPushButton(Dialogw);
        del->setObjectName(QStringLiteral("del"));
        del->setGeometry(QRect(220, 290, 81, 21));
        close = new QPushButton(Dialogw);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(290, 10, 31, 28));
        okButton = new QPushButton(Dialogw);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(220, 260, 81, 21));

        retranslateUi(Dialogw);

        QMetaObject::connectSlotsByName(Dialogw);
    } // setupUi

    void retranslateUi(QDialog *Dialogw)
    {
        Dialogw->setWindowTitle(QApplication::translate("Dialogw", "Dialog", Q_NULLPTR));
        clean->setText(QApplication::translate("Dialogw", "\346\270\205\351\231\244", Q_NULLPTR));
        toolButton->setText(QApplication::translate("Dialogw", "...", Q_NULLPTR));
        zh_1->setText(QString());
        zh_2->setText(QString());
        zh_3->setText(QString());
        zh_4->setText(QString());
        zh_5->setText(QString());
        zh_6->setText(QString());
        zh_7->setText(QString());
        zh_8->setText(QString());
        zh_9->setText(QString());
        zh_10->setText(QString());
        del->setText(QApplication::translate("Dialogw", "backspace", Q_NULLPTR));
        close->setText(QString());
        okButton->setText(QApplication::translate("Dialogw", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialogw: public Ui_Dialogw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGW_H
