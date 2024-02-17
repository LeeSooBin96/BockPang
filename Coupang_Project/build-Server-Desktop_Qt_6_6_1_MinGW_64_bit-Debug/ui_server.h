/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QLabel *lb_Marcket_name;
    QLabel *lb_Logo;
    QTextEdit *textEdit;

    void setupUi(QWidget *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName("Server");
        Server->resize(345, 295);
        Server->setMinimumSize(QSize(345, 295));
        Server->setMaximumSize(QSize(345, 295));
        lb_Marcket_name = new QLabel(Server);
        lb_Marcket_name->setObjectName("lb_Marcket_name");
        lb_Marcket_name->setGeometry(QRect(180, 19, 160, 41));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        lb_Marcket_name->setFont(font);
        lb_Marcket_name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lb_Logo = new QLabel(Server);
        lb_Logo->setObjectName("lb_Logo");
        lb_Logo->setGeometry(QRect(-25, 0, 190, 60));
        lb_Logo->setStyleSheet(QString::fromUtf8("border-image:url(\"/Users/IOT/Desktop/Important/Coupang_Project/Image/Join.png\")"));
        textEdit = new QTextEdit(Server);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(5, 60, 335, 230));

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QWidget *Server)
    {
        Server->setWindowTitle(QCoreApplication::translate("Server", "Server", nullptr));
        lb_Marcket_name->setText(QString());
        lb_Logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
