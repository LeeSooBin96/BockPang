#ifndef CHATSERVER_H
#define CHATSERVER_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QTcpServer>
#include<QTcpSocket>

#include "garbagecenter.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent = 0);
    ~ChatServer();
protected:
    void incomingConnection(qintptr socketfd);
private:
    QSet<QTcpSocket *> qset_clntChatList; //소켓리스트(고객,매장,배달 구별 x 저장)
    QMap<QTcpSocket *, QString> qmap_userList; //소켓리스트(고객 소켓-닉네임 매핑)
    QMap<QString, QTcpSocket*> qmap_marcketList;//소켓리스트(매장소켓,매장번호 매핑)
    QMap<QString, QTcpSocket*> qmap_orderList;
    QList<QTcpSocket*> newchat;
    QSqlDatabase* DB;


    GarbageCenter* center;

signals:
    void chat_update_ChatCNT(int NO_Users);
    void chat_showMSG(QString msg);


private slots:
    void read_MSG();
    void Chat_disconnected();

    //고객센터 문의 응답
    void send_MSG(QString nick,QString msg);
};

#endif // CHATSERVER_H
