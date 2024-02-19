#include "partner.h"
#include "ui_partner.h"

Partner::Partner(QWidget *parent) : QWidget(parent) , ui(new Ui::Partner)
{
    ui->setupUi(this);
    // connectServer();
}

Partner::~Partner()
{
    delete ui;
}

void Partner::connectServer()
{
    tcpSocket = new QTcpSocket(this);
    QHostAddress server("10.10.20.98");
    qint64 portNum=99999;

    tcpSocket->connectToHost(server,portNum);
    tcpSocket->write("D");

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
    if(msg.split('@')[0]=="W") //주문 들어왔을때
    {
        ui->listWidget->addItem("주문이 들어왔습니다.\n주문번호 :"+msg.split('@')[1]); //다중 정말 생각 안하고 짠 코드 나중에 수정하자
        orderList.push_back(msg.split('@')[1]);
    }

}
void Partner::Accept()
{
    qDebug()<<"업무 시작";
    // tcpSocket -> write("업무 시작");
    connectServer();
}
void Partner::Start()
{
    int index=ui->listWidget->currentRow();
    tcpSocket -> write("W"+myNum.toUtf8()+"^"+orderList[index].toUtf8());
    qDebug() << "sss";
}
void Partner::Complete()
{
    int index=ui->listWidget->currentRow();
    tcpSocket -> write("F"+myNum.toUtf8()+"^D^"+orderList[index].toUtf8());
    qDebug() << "aaa";
}
