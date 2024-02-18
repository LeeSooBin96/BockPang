#include <QtNetwork>
#include "server.h"
#include "chatserver.h"
#include "ui_server.h"

Server::Server(QWidget *parent) : QWidget(parent), ui(new Ui::Server)
{
    ui->setupUi(this);

    hostAddress = getMyIP();
    hostPort = qint16(99999);
    title = "Bokpang_eats 고객센터 (" + hostAddress.toString() + " " + QString::number(hostPort) + ")";
    setWindowTitle(title);

    server = new ChatServer(this);
    server -> listen(hostAddress, hostPort);

    connect(server,SIGNAL(chat_update_ChatCNT(int)),this,SLOT(server_update_ChatCNT(int)));
    connect(server,SIGNAL(chat_showMSG(QString)),this,SLOT(server_showMSG(QString)));

}

Server::~Server()
{
    delete ui;
}
void Server::server_update_ChatCNT(int users)
{
    QString str = QString("접속자수 : %1").arg(users);
    ui -> lb_Marcket_name->setText(str);
}
void Server::server_showMSG(QString msg)
{
    ui -> textEdit->append(msg);
}
QHostAddress Server::getMyIP()
{
    QHostAddress myAddress;

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address())
        {
            myAddress = ipAddressesList.at(i);
            break;
        }
    }

    if (myAddress.toString().isEmpty())
        myAddress = QHostAddress(QHostAddress::LocalHost);

    return myAddress;
}
