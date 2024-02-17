#ifndef CHATSERVER_H
#define CHATSERVER_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QTcpServer>
#include<QTcpSocket>

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent = 0);
    ~ChatServer();
protected:
    void incomingConnection(qintptr socketfd);
private:
    QSet<QTcpSocket *> qset_clntChatList;
    QMap<QTcpSocket *, QString> qmap_userList;
    QList<QTcpSocket*> newchat;
    QSqlDatabase* DB;

signals:
    void chat_update_ChatCNT(int NO_Users);
    void chat_showMSG(QString msg);

private slots:
    void read_MSG();
    void Chat_disconnected();
    // void sendPerformList();
};

#endif // CHATSERVER_H
