/********************************************************************************
** Form generated from reading UI file 'loginpage.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lb_Logo;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *Btn_FindPW;
    QLabel *lb_Pw;
    QLabel *lb_ID;
    QLineEdit *PW_Edit;
    QPushButton *Btn_Join;
    QLineEdit *ID_Edit;
    QPushButton *Btn_FindID;
    QPushButton *Btn_Login;
    QWidget *page_2;
    QLineEdit *PW_JoinEdit;
    QLabel *lb_Join_NAME;
    QLabel *lb_Join_PHONE;
    QLineEdit *NAME_JoinEdit;
    QPushButton *Btn_confirmNICKNAME;
    QLabel *lb_Join_NICKNAME;
    QLineEdit *ID_JoinEdit;
    QLabel *lb_Join_ID;
    QPushButton *Btn_confirmJoin;
    QLineEdit *PHONE_JoinEdit;
    QLineEdit *NICKNAME_JoinEdit;
    QLabel *lb_Join_PW;
    QPushButton *Btn_JoinBack;
    QPushButton *Btn_confirmID;
    QPushButton *Btn_confirmPHONE;
    QLabel *lbl_ckID;
    QLabel *lbl_ckPW;
    QWidget *page_3;
    QPushButton *Btn_confirmFindID;
    QLabel *lb_FindID_PHONE;
    QLabel *lb_FindID_NAME;
    QLineEdit *NAME_FindIDEdit;
    QLineEdit *PHONE_FindIDEdit;
    QPushButton *Btn_FindIDBack;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_noticID;
    QLabel *lbl_SID;
    QWidget *page_4;
    QLineEdit *NAME_FindPWEdit;
    QLabel *lb_FindPW_NICKNAME;
    QLineEdit *ID_FindPWEdit;
    QLabel *lb_FindPW_ID;
    QLineEdit *PHONE_FindPWEdit;
    QLabel *lb_FindPW_PHONE;
    QPushButton *Btn_FindPWBack;
    QPushButton *Btn_confirmFindPW;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *lbl_noticPW;
    QLabel *lbl_SPW;

    void setupUi(QWidget *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName("LoginPage");
        LoginPage->resize(375, 665);
        LoginPage->setMinimumSize(QSize(375, 665));
        LoginPage->setMaximumSize(QSize(375, 665));
        verticalLayout = new QVBoxLayout(LoginPage);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 50, 0, 0);
        lb_Logo = new QLabel(LoginPage);
        lb_Logo->setObjectName("lb_Logo");
        lb_Logo->setStyleSheet(QString::fromUtf8("\n"
"border-image: url(:/Image/Join.png);"));
        lb_Logo->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lb_Logo);

        stackedWidget = new QStackedWidget(LoginPage);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        Btn_FindPW = new QPushButton(page);
        Btn_FindPW->setObjectName("Btn_FindPW");
        Btn_FindPW->setGeometry(QRect(200, 320, 125, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Image/Find_PW.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_FindPW->setIcon(icon);
        Btn_FindPW->setIconSize(QSize(150, 50));
        Btn_FindPW->setFlat(true);
        lb_Pw = new QLabel(page);
        lb_Pw->setObjectName("lb_Pw");
        lb_Pw->setGeometry(QRect(65, 100, 70, 40));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        lb_Pw->setFont(font);
        lb_ID = new QLabel(page);
        lb_ID->setObjectName("lb_ID");
        lb_ID->setGeometry(QRect(65, 40, 70, 40));
        lb_ID->setFont(font);
        PW_Edit = new QLineEdit(page);
        PW_Edit->setObjectName("PW_Edit");
        PW_Edit->setGeometry(QRect(135, 100, 190, 40));
        PW_Edit->setEchoMode(QLineEdit::Password);
        Btn_Join = new QPushButton(page);
        Btn_Join->setObjectName("Btn_Join");
        Btn_Join->setGeometry(QRect(65, 260, 260, 40));
        QFont font1;
        font1.setBold(true);
        Btn_Join->setFont(font1);
        Btn_Join->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_Join->setIconSize(QSize(260, 50));
        Btn_Join->setFlat(true);
        ID_Edit = new QLineEdit(page);
        ID_Edit->setObjectName("ID_Edit");
        ID_Edit->setGeometry(QRect(135, 40, 190, 40));
        Btn_FindID = new QPushButton(page);
        Btn_FindID->setObjectName("Btn_FindID");
        Btn_FindID->setGeometry(QRect(65, 320, 125, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Image/Find_ID.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_FindID->setIcon(icon1);
        Btn_FindID->setIconSize(QSize(150, 50));
        Btn_FindID->setFlat(true);
        Btn_Login = new QPushButton(page);
        Btn_Login->setObjectName("Btn_Login");
        Btn_Login->setGeometry(QRect(65, 200, 260, 40));
        Btn_Login->setFont(font1);
        Btn_Login->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_Login->setIconSize(QSize(260, 50));
        Btn_Login->setFlat(true);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        PW_JoinEdit = new QLineEdit(page_2);
        PW_JoinEdit->setObjectName("PW_JoinEdit");
        PW_JoinEdit->setGeometry(QRect(100, 90, 190, 40));
        lb_Join_NAME = new QLabel(page_2);
        lb_Join_NAME->setObjectName("lb_Join_NAME");
        lb_Join_NAME->setGeometry(QRect(30, 150, 70, 40));
        lb_Join_NAME->setFont(font);
        lb_Join_PHONE = new QLabel(page_2);
        lb_Join_PHONE->setObjectName("lb_Join_PHONE");
        lb_Join_PHONE->setGeometry(QRect(30, 210, 70, 40));
        lb_Join_PHONE->setFont(font);
        NAME_JoinEdit = new QLineEdit(page_2);
        NAME_JoinEdit->setObjectName("NAME_JoinEdit");
        NAME_JoinEdit->setGeometry(QRect(100, 150, 190, 40));
        Btn_confirmNICKNAME = new QPushButton(page_2);
        Btn_confirmNICKNAME->setObjectName("Btn_confirmNICKNAME");
        Btn_confirmNICKNAME->setGeometry(QRect(300, 270, 60, 40));
        Btn_confirmNICKNAME->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        lb_Join_NICKNAME = new QLabel(page_2);
        lb_Join_NICKNAME->setObjectName("lb_Join_NICKNAME");
        lb_Join_NICKNAME->setGeometry(QRect(30, 270, 70, 40));
        lb_Join_NICKNAME->setFont(font);
        ID_JoinEdit = new QLineEdit(page_2);
        ID_JoinEdit->setObjectName("ID_JoinEdit");
        ID_JoinEdit->setGeometry(QRect(100, 30, 190, 40));
        lb_Join_ID = new QLabel(page_2);
        lb_Join_ID->setObjectName("lb_Join_ID");
        lb_Join_ID->setGeometry(QRect(30, 30, 70, 40));
        lb_Join_ID->setFont(font);
        Btn_confirmJoin = new QPushButton(page_2);
        Btn_confirmJoin->setObjectName("Btn_confirmJoin");
        Btn_confirmJoin->setGeometry(QRect(100, 380, 260, 40));
        Btn_confirmJoin->setFont(font1);
        Btn_confirmJoin->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_confirmJoin->setIconSize(QSize(260, 50));
        Btn_confirmJoin->setFlat(true);
        PHONE_JoinEdit = new QLineEdit(page_2);
        PHONE_JoinEdit->setObjectName("PHONE_JoinEdit");
        PHONE_JoinEdit->setGeometry(QRect(100, 210, 190, 40));
        NICKNAME_JoinEdit = new QLineEdit(page_2);
        NICKNAME_JoinEdit->setObjectName("NICKNAME_JoinEdit");
        NICKNAME_JoinEdit->setGeometry(QRect(100, 270, 190, 40));
        lb_Join_PW = new QLabel(page_2);
        lb_Join_PW->setObjectName("lb_Join_PW");
        lb_Join_PW->setGeometry(QRect(30, 90, 70, 40));
        lb_Join_PW->setFont(font);
        Btn_JoinBack = new QPushButton(page_2);
        Btn_JoinBack->setObjectName("Btn_JoinBack");
        Btn_JoinBack->setGeometry(QRect(20, 380, 60, 40));
        Btn_JoinBack->setFont(font1);
        Btn_JoinBack->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_JoinBack->setIconSize(QSize(200, 50));
        Btn_JoinBack->setFlat(true);
        Btn_confirmID = new QPushButton(page_2);
        Btn_confirmID->setObjectName("Btn_confirmID");
        Btn_confirmID->setGeometry(QRect(300, 30, 60, 40));
        Btn_confirmID->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_confirmPHONE = new QPushButton(page_2);
        Btn_confirmPHONE->setObjectName("Btn_confirmPHONE");
        Btn_confirmPHONE->setGeometry(QRect(300, 210, 60, 40));
        Btn_confirmPHONE->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        lbl_ckID = new QLabel(page_2);
        lbl_ckID->setObjectName("lbl_ckID");
        lbl_ckID->setGeometry(QRect(100, 70, 271, 20));
        QFont font2;
        font2.setPointSize(8);
        lbl_ckID->setFont(font2);
        lbl_ckID->setStyleSheet(QString::fromUtf8("color: rgb(115, 186, 184);"));
        lbl_ckPW = new QLabel(page_2);
        lbl_ckPW->setObjectName("lbl_ckPW");
        lbl_ckPW->setGeometry(QRect(100, 130, 271, 16));
        lbl_ckPW->setFont(font2);
        lbl_ckPW->setStyleSheet(QString::fromUtf8("color: rgb(115, 186, 184);"));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        Btn_confirmFindID = new QPushButton(page_3);
        Btn_confirmFindID->setObjectName("Btn_confirmFindID");
        Btn_confirmFindID->setGeometry(QRect(100, 350, 260, 40));
        Btn_confirmFindID->setFont(font1);
        Btn_confirmFindID->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_confirmFindID->setFlat(true);
        lb_FindID_PHONE = new QLabel(page_3);
        lb_FindID_PHONE->setObjectName("lb_FindID_PHONE");
        lb_FindID_PHONE->setGeometry(QRect(60, 130, 70, 40));
        lb_FindID_PHONE->setFont(font);
        lb_FindID_NAME = new QLabel(page_3);
        lb_FindID_NAME->setObjectName("lb_FindID_NAME");
        lb_FindID_NAME->setGeometry(QRect(60, 70, 70, 40));
        lb_FindID_NAME->setFont(font);
        NAME_FindIDEdit = new QLineEdit(page_3);
        NAME_FindIDEdit->setObjectName("NAME_FindIDEdit");
        NAME_FindIDEdit->setGeometry(QRect(130, 70, 190, 40));
        PHONE_FindIDEdit = new QLineEdit(page_3);
        PHONE_FindIDEdit->setObjectName("PHONE_FindIDEdit");
        PHONE_FindIDEdit->setGeometry(QRect(130, 130, 190, 40));
        Btn_FindIDBack = new QPushButton(page_3);
        Btn_FindIDBack->setObjectName("Btn_FindIDBack");
        Btn_FindIDBack->setGeometry(QRect(20, 350, 60, 40));
        Btn_FindIDBack->setFont(font1);
        Btn_FindIDBack->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_FindIDBack->setIconSize(QSize(200, 50));
        Btn_FindIDBack->setFlat(true);
        widget = new QWidget(page_3);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(60, 190, 261, 121));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lbl_noticID = new QLabel(widget);
        lbl_noticID->setObjectName("lbl_noticID");
        QFont font3;
        font3.setPointSize(15);
        font3.setBold(true);
        lbl_noticID->setFont(font3);
        lbl_noticID->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lbl_noticID);

        lbl_SID = new QLabel(widget);
        lbl_SID->setObjectName("lbl_SID");
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        lbl_SID->setFont(font4);
        lbl_SID->setStyleSheet(QString::fromUtf8("color: rgb(42, 193, 188);"));
        lbl_SID->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lbl_SID);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        NAME_FindPWEdit = new QLineEdit(page_4);
        NAME_FindPWEdit->setObjectName("NAME_FindPWEdit");
        NAME_FindPWEdit->setGeometry(QRect(130, 70, 190, 40));
        lb_FindPW_NICKNAME = new QLabel(page_4);
        lb_FindPW_NICKNAME->setObjectName("lb_FindPW_NICKNAME");
        lb_FindPW_NICKNAME->setGeometry(QRect(60, 70, 70, 40));
        lb_FindPW_NICKNAME->setFont(font);
        ID_FindPWEdit = new QLineEdit(page_4);
        ID_FindPWEdit->setObjectName("ID_FindPWEdit");
        ID_FindPWEdit->setGeometry(QRect(130, 10, 190, 40));
        lb_FindPW_ID = new QLabel(page_4);
        lb_FindPW_ID->setObjectName("lb_FindPW_ID");
        lb_FindPW_ID->setGeometry(QRect(60, 10, 70, 40));
        lb_FindPW_ID->setFont(font);
        PHONE_FindPWEdit = new QLineEdit(page_4);
        PHONE_FindPWEdit->setObjectName("PHONE_FindPWEdit");
        PHONE_FindPWEdit->setGeometry(QRect(130, 130, 190, 40));
        lb_FindPW_PHONE = new QLabel(page_4);
        lb_FindPW_PHONE->setObjectName("lb_FindPW_PHONE");
        lb_FindPW_PHONE->setGeometry(QRect(60, 130, 70, 40));
        lb_FindPW_PHONE->setFont(font);
        Btn_FindPWBack = new QPushButton(page_4);
        Btn_FindPWBack->setObjectName("Btn_FindPWBack");
        Btn_FindPWBack->setGeometry(QRect(20, 350, 60, 40));
        Btn_FindPWBack->setFont(font1);
        Btn_FindPWBack->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        Btn_confirmFindPW = new QPushButton(page_4);
        Btn_confirmFindPW->setObjectName("Btn_confirmFindPW");
        Btn_confirmFindPW->setGeometry(QRect(100, 350, 260, 40));
        Btn_confirmFindPW->setFont(font1);
        Btn_confirmFindPW->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(42, 193, 188);\n"
"border-radius:10px;\n"
""));
        layoutWidget_2 = new QWidget(page_4);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(60, 190, 261, 121));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        lbl_noticPW = new QLabel(layoutWidget_2);
        lbl_noticPW->setObjectName("lbl_noticPW");
        lbl_noticPW->setFont(font3);
        lbl_noticPW->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(lbl_noticPW);

        lbl_SPW = new QLabel(layoutWidget_2);
        lbl_SPW->setObjectName("lbl_SPW");
        lbl_SPW->setFont(font4);
        lbl_SPW->setStyleSheet(QString::fromUtf8("color: rgb(42, 193, 188);"));
        lbl_SPW->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(lbl_SPW);

        stackedWidget->addWidget(page_4);

        verticalLayout->addWidget(stackedWidget);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 7);
        stackedWidget->raise();
        lb_Logo->raise();
        QWidget::setTabOrder(ID_Edit, PW_Edit);
        QWidget::setTabOrder(PW_Edit, Btn_Login);
        QWidget::setTabOrder(Btn_Login, Btn_Join);
        QWidget::setTabOrder(Btn_Join, Btn_FindID);
        QWidget::setTabOrder(Btn_FindID, Btn_FindPW);
        QWidget::setTabOrder(Btn_FindPW, ID_JoinEdit);
        QWidget::setTabOrder(ID_JoinEdit, Btn_confirmID);
        QWidget::setTabOrder(Btn_confirmID, PW_JoinEdit);
        QWidget::setTabOrder(PW_JoinEdit, NAME_JoinEdit);
        QWidget::setTabOrder(NAME_JoinEdit, PHONE_JoinEdit);
        QWidget::setTabOrder(PHONE_JoinEdit, Btn_confirmPHONE);
        QWidget::setTabOrder(Btn_confirmPHONE, NICKNAME_JoinEdit);
        QWidget::setTabOrder(NICKNAME_JoinEdit, Btn_confirmNICKNAME);
        QWidget::setTabOrder(Btn_confirmNICKNAME, Btn_confirmJoin);
        QWidget::setTabOrder(Btn_confirmJoin, Btn_JoinBack);

        retranslateUi(LoginPage);
        QObject::connect(ID_Edit, &QLineEdit::returnPressed, PW_Edit, qOverload<>(&QLineEdit::setFocus));
        QObject::connect(PW_Edit, &QLineEdit::returnPressed, Btn_Login, qOverload<>(&QPushButton::click));
        QObject::connect(Btn_Login, SIGNAL(clicked()), LoginPage, SLOT(LoginProgress()));
        QObject::connect(Btn_JoinBack, SIGNAL(clicked()), LoginPage, SLOT(gotoLogin()));
        QObject::connect(Btn_Join, SIGNAL(clicked()), LoginPage, SLOT(gotoJoin()));
        QObject::connect(ID_JoinEdit, SIGNAL(textChanged(QString)), LoginPage, SLOT(CheckID(QString)));
        QObject::connect(Btn_confirmID, SIGNAL(clicked()), LoginPage, SLOT(SendJoinID()));
        QObject::connect(PW_JoinEdit, SIGNAL(textChanged(QString)), LoginPage, SLOT(CheckPW(QString)));
        QObject::connect(Btn_confirmPHONE, SIGNAL(clicked()), LoginPage, SLOT(CheckPHONE()));
        QObject::connect(Btn_confirmNICKNAME, SIGNAL(clicked()), LoginPage, SLOT(SendNICK()));
        QObject::connect(ID_JoinEdit, &QLineEdit::returnPressed, Btn_confirmID, qOverload<>(&QPushButton::click));
        QObject::connect(PW_JoinEdit, &QLineEdit::returnPressed, NAME_JoinEdit, qOverload<>(&QLineEdit::setFocus));
        QObject::connect(NAME_JoinEdit, &QLineEdit::returnPressed, PHONE_JoinEdit, qOverload<>(&QLineEdit::setFocus));
        QObject::connect(PHONE_JoinEdit, &QLineEdit::returnPressed, Btn_confirmPHONE, qOverload<>(&QPushButton::setFocus));
        QObject::connect(NICKNAME_JoinEdit, &QLineEdit::returnPressed, Btn_confirmNICKNAME, qOverload<>(&QPushButton::setFocus));
        QObject::connect(Btn_confirmJoin, SIGNAL(clicked()), LoginPage, SLOT(JoinProgress()));
        QObject::connect(Btn_FindIDBack, SIGNAL(clicked()), LoginPage, SLOT(gotoLogin()));
        QObject::connect(NAME_FindIDEdit, &QLineEdit::returnPressed, PHONE_FindIDEdit, qOverload<>(&QLineEdit::setFocus));
        QObject::connect(PHONE_FindIDEdit, &QLineEdit::returnPressed, Btn_confirmFindID, qOverload<>(&QPushButton::click));
        QObject::connect(Btn_FindID, SIGNAL(clicked()), LoginPage, SLOT(gotoSID()));
        QObject::connect(Btn_confirmFindID, SIGNAL(clicked()), LoginPage, SLOT(RequestSID()));
        QObject::connect(Btn_FindPWBack, SIGNAL(clicked()), LoginPage, SLOT(gotoLogin()));
        QObject::connect(Btn_FindPW, SIGNAL(clicked()), LoginPage, SLOT(gotoSPW()));
        QObject::connect(ID_FindPWEdit, &QLineEdit::returnPressed, NAME_FindPWEdit, qOverload<>(&QLineEdit::setFocus));
        QObject::connect(NAME_FindPWEdit, &QLineEdit::returnPressed, PHONE_FindPWEdit, qOverload<>(&QLineEdit::setFocus));
        QObject::connect(PHONE_FindPWEdit, &QLineEdit::returnPressed, Btn_confirmFindPW, qOverload<>(&QPushButton::click));
        QObject::connect(Btn_confirmFindPW, SIGNAL(clicked()), LoginPage, SLOT(RequestSPW()));

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QWidget *LoginPage)
    {
        LoginPage->setWindowTitle(QCoreApplication::translate("LoginPage", "Form", nullptr));
        lb_Logo->setText(QString());
        Btn_FindPW->setText(QString());
        lb_Pw->setText(QCoreApplication::translate("LoginPage", "PW", nullptr));
        lb_ID->setText(QCoreApplication::translate("LoginPage", "ID", nullptr));
        PW_Edit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \353\271\204\353\260\200\353\262\210\355\230\270 \354\236\205\353\240\245", nullptr));
        Btn_Join->setText(QCoreApplication::translate("LoginPage", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        ID_Edit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \354\225\204\354\235\264\353\224\224 \354\236\205\353\240\245", nullptr));
        Btn_FindID->setText(QString());
        Btn_Login->setText(QCoreApplication::translate("LoginPage", "\353\241\234\352\267\270\354\235\270", nullptr));
        PW_JoinEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \353\271\204\353\260\200\353\262\210\355\230\270 \354\236\205\353\240\245", nullptr));
        lb_Join_NAME->setText(QCoreApplication::translate("LoginPage", "\354\235\264\353\246\204", nullptr));
        lb_Join_PHONE->setText(QCoreApplication::translate("LoginPage", "\354\240\204\355\231\224\353\262\210\355\230\270", nullptr));
        NAME_JoinEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \354\235\264\353\246\204 \354\236\205\353\240\245", nullptr));
        Btn_confirmNICKNAME->setText(QCoreApplication::translate("LoginPage", "\354\244\221\353\263\265\355\231\225\354\235\270", nullptr));
        lb_Join_NICKNAME->setText(QCoreApplication::translate("LoginPage", "\353\213\211\353\204\244\354\236\204", nullptr));
        ID_JoinEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \354\225\204\354\235\264\353\224\224 \354\236\205\353\240\245", nullptr));
        lb_Join_ID->setText(QCoreApplication::translate("LoginPage", "ID", nullptr));
        Btn_confirmJoin->setText(QCoreApplication::translate("LoginPage", "\355\232\214\354\233\220\352\260\200\354\236\205", nullptr));
        PHONE_JoinEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \354\240\204\355\231\224\353\262\210\355\230\270 \354\236\205\353\240\245", nullptr));
        NICKNAME_JoinEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \353\213\211\353\204\244\354\236\204 \354\236\205\353\240\245", nullptr));
        lb_Join_PW->setText(QCoreApplication::translate("LoginPage", "PW", nullptr));
        Btn_JoinBack->setText(QCoreApplication::translate("LoginPage", "\354\235\264\354\240\204", nullptr));
        Btn_confirmID->setText(QCoreApplication::translate("LoginPage", "\354\244\221\353\263\265\355\231\225\354\235\270", nullptr));
        Btn_confirmPHONE->setText(QCoreApplication::translate("LoginPage", "\354\244\221\353\263\265\355\231\225\354\235\270", nullptr));
        lbl_ckID->setText(QCoreApplication::translate("LoginPage", "\354\225\204\354\235\264\353\224\224\353\245\274 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224.", nullptr));
        lbl_ckPW->setText(QCoreApplication::translate("LoginPage", "\353\271\204\353\260\200\353\262\210\355\230\270\353\245\274 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224.", nullptr));
        Btn_confirmFindID->setText(QCoreApplication::translate("LoginPage", "ID \354\260\276\352\270\260", nullptr));
        lb_FindID_PHONE->setText(QCoreApplication::translate("LoginPage", "\354\240\204\355\231\224\353\262\210\355\230\270", nullptr));
        lb_FindID_NAME->setText(QCoreApplication::translate("LoginPage", "\354\235\264\353\246\204", nullptr));
        NAME_FindIDEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \354\235\264\353\246\204 \354\236\205\353\240\245", nullptr));
        PHONE_FindIDEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \353\213\211\353\204\244\354\236\204 \354\236\205\353\240\245", nullptr));
        Btn_FindIDBack->setText(QCoreApplication::translate("LoginPage", "\354\235\264\354\240\204", nullptr));
        lbl_noticID->setText(QCoreApplication::translate("LoginPage", "\354\260\276\354\235\200 \354\225\204\354\235\264\353\224\224", nullptr));
        lbl_SID->setText(QString());
        NAME_FindPWEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \354\235\264\353\246\204 \354\236\205\353\240\245", nullptr));
        lb_FindPW_NICKNAME->setText(QCoreApplication::translate("LoginPage", "\354\235\264\353\246\204", nullptr));
        ID_FindPWEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \354\225\204\354\235\264\353\224\224 \354\236\205\353\240\245", nullptr));
        lb_FindPW_ID->setText(QCoreApplication::translate("LoginPage", "ID", nullptr));
        PHONE_FindPWEdit->setPlaceholderText(QCoreApplication::translate("LoginPage", "  \353\213\211\353\204\244\354\236\204 \354\236\205\353\240\245", nullptr));
        lb_FindPW_PHONE->setText(QCoreApplication::translate("LoginPage", "\354\240\204\355\231\224\353\262\210\355\230\270", nullptr));
        Btn_FindPWBack->setText(QCoreApplication::translate("LoginPage", "\354\235\264\354\240\204", nullptr));
        Btn_confirmFindPW->setText(QCoreApplication::translate("LoginPage", "PW \354\260\276\352\270\260", nullptr));
        lbl_noticPW->setText(QCoreApplication::translate("LoginPage", "\354\260\276\354\235\200 \353\271\204\353\260\200\353\262\210\355\230\270", nullptr));
        lbl_SPW->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
