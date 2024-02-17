#include "garbagecenter.h"
#include "ui_garbagecenter.h"

GarbageCenter::GarbageCenter(QWidget *parent,QString *nick)
    : QDialog(parent)
    , ui(new Ui::GarbageCenter)
{
    ui->setupUi(this);
}

GarbageCenter::~GarbageCenter()
{
    delete ui;
}
