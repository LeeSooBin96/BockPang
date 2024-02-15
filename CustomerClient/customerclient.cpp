#include "customerclient.h"
#include "ui_customerclient.h"

CustomerClient::CustomerClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomerClient)
{
    ui->setupUi(this);
}

CustomerClient::~CustomerClient()
{
    delete ui;
}
