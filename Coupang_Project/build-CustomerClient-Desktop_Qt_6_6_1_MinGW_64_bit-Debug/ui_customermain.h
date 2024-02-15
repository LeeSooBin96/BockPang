/********************************************************************************
** Form generated from reading UI file 'customermain.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERMAIN_H
#define UI_CUSTOMERMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomerMain
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *mainStack;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Btn_first;

    void setupUi(QWidget *CustomerMain)
    {
        if (CustomerMain->objectName().isEmpty())
            CustomerMain->setObjectName("CustomerMain");
        CustomerMain->resize(375, 665);
        CustomerMain->setMinimumSize(QSize(375, 665));
        CustomerMain->setMaximumSize(QSize(375, 665));
        verticalLayout = new QVBoxLayout(CustomerMain);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mainStack = new QStackedWidget(CustomerMain);
        mainStack->setObjectName("mainStack");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Btn_first = new QPushButton(page);
        Btn_first->setObjectName("Btn_first");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Image/first.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_first->setIcon(icon);
        Btn_first->setIconSize(QSize(375, 665));
        Btn_first->setAutoDefault(false);
        Btn_first->setFlat(true);

        verticalLayout_2->addWidget(Btn_first);

        mainStack->addWidget(page);

        verticalLayout->addWidget(mainStack);


        retranslateUi(CustomerMain);
        QObject::connect(Btn_first, SIGNAL(clicked()), CustomerMain, SLOT(gotoLogin()));

        mainStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CustomerMain);
    } // setupUi

    void retranslateUi(QWidget *CustomerMain)
    {
        CustomerMain->setWindowTitle(QCoreApplication::translate("CustomerMain", "Form", nullptr));
        Btn_first->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CustomerMain: public Ui_CustomerMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERMAIN_H
