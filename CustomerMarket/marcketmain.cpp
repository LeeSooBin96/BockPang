#include "marcketmain.h"
#include "ui_marcketmain.h"

MarcketMain::MarcketMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MarcketMain)
{
    ui->setupUi(this);
}

MarcketMain::~MarcketMain()
{
    delete ui;
}
//서버와 연결
void MarcketMain::connectServer()
{
    tcpSocket = new QTcpSocket(this);

    // QHostAddress server("10.10.20.111");
    QHostAddress server("192.168.0.14");
    qint64 portNum=99999;

    tcpSocket->connectToHost(server,portNum);
    tcpSocket->write("MO^1");

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMSG()));
    connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));
}
//서버로부터 메시지 수신
void MarcketMain::readMSG()
{
    QString msg;
    if(tcpSocket->bytesAvailable()>0) //읽을 메시지가 있다면
    {
        msg=tcpSocket->readAll();
        qDebug()<<"서버로부터 "<<msg;
    }
    if(msg.split('@').size()==1) //번호만 보낸것이기에
    {
        myNum=msg; //부여받은 번호 저장
        qDebug()<<"부여받은 번호:"<<myNum;
        this->setStatusTip("서버에 연결되었습니다.");
    }
}
