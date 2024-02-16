#include "orderpage.h"
#include "ui_orderpage.h"

OrderPage::OrderPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderPage)
{
    ui->setupUi(this);
}

OrderPage::~OrderPage()
{
    delete ui;
}

void OrderPage::SendSearchKey()
{
    QString keyword=ui->Search_Edit->text(); //검색창에 입력된 키워드

}
