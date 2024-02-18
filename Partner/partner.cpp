#include "partner.h"
#include "ui_partner.h"

Partner::Partner(QWidget *parent) : QWidget(parent) , ui(new Ui::Partner)
{
    ui->setupUi(this);
    connectServer();
}

Partner::~Partner()
{
    delete ui;
}

void Partner::connectServer()
{
    tcpSocket = new QTcpSocket(this);
    QHostAddress server("10.10.20.111");
    qint64 portNum=99999;

    tcpSocket->connectToHost(server,portNum);
    tcpSocket->write("U");

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(MSG_Read()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnect()));
}
void Partner::disconnect()
{
    qDebug()<<"Server disconnected";
}
//서버로 메시지 송신
void Partner::sendServerMSG(QByteArray msg)
{
    tcpSocket->write(msg);
    qDebug()<<"Message to Server "<<msg;
}
void Partner::MSG_Read()
{
    QString msg;
    if(tcpSocket->bytesAvailable()>0) //읽을 메시지가 있다면
    {
        msg.append(tcpSocket->readAll());
        qDebug()<<"From Server "<<msg;
    }
    if(msg.split('@').size() == 1)
    {
        myNum = msg;
        qDebug() << "GET NUM" << myNum;
    }
    else if(msg.split('@')[0] == "D")
    {

    }
    else if(msg.split('@')[0] == "D")
    {

    }
}
void Partner::Accept()
{
    tcpSocket -> write("업무 시작");
    qDebug() << "ddd";
}
void Partner::Start()
{
    tcpSocket -> write("배달 시작");
    qDebug() << "sss";
}
void Partner::Complete()
{
    tcpSocket -> write("배달 완료");
    qDebug() << "aaa";
}
