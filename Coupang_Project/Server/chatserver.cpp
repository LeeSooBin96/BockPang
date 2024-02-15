#include <QtWidgets>
#include <QDebug>
#include "chatserver.h"


ChatServer::ChatServer(QObject *parent): QTcpServer(parent)
{
    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("/Users/IOT/Desktop/Important/Coupang_Project/Bokpang");

    if(!DB.open())
        qDebug() << "fail Database";
    else
        qDebug() << "Connect";
}

ChatServer::~ChatServer()
{
    foreach(QTcpSocket *client,qset_clntChatList)
        client->disconnectFromHost();
}

void ChatServer::incomingConnection(qintptr socketfd)
{
    qDebug() << Q_FUNC_INFO;

    QTcpSocket *newConnectedChat = new QTcpSocket(this);

    newConnectedChat -> setSocketDescriptor(socketfd);

    qset_clntChatList.insert(newConnectedChat);
    emit chat_update_ChatCNT(qset_clntChatList.count());

    QString str = QString("새로운 접속자 : %1").arg(newConnectedChat->peerAddress().toString());
    emit chat_showMSG(str);

    connect(newConnectedChat,SIGNAL(readyRead()),this,SLOT(read_MSG()));

    connect(newConnectedChat,SIGNAL(disconnected()),this,SLOT(Chat_disconnected()));
}
void ChatServer::read_MSG()
{
    QTcpSocket* senderChat = (QTcpSocket*)sender();
    QString line = QString::fromUtf8(senderChat->readAll()).trimmed();
    qDebug() << line;
    if(line.size() == 2)
    {
        newchat.append(senderChat);

        int index = newchat.indexOf(senderChat);
        senderChat -> write(QString::number(index).toUtf8());
        qDebug() << index;
    }
    if(line.size() == 1 )
    {
        newchat.append(senderChat);

        int index = newchat.indexOf(senderChat);
        senderChat -> write(QString::number(index).toUtf8());
        qDebug() << index;
    }
    else if(line.split('^')[0].front() == 'U')                  // 고객 로그인 / 회원가입 관련 처리
    {
        QString Login = line.split('^')[1];
        QString Join = line.split('^')[1];
        QString FindID = line.split('^')[1];
        QString FindPW = line.split('^')[1];
        if(Login == "L")
        {
            QString ID,PW;
            ID = line.split('^')[2];
            PW = line.split('^')[3];

            QSqlQuery query;
            query.prepare("SELECT ID,PW FROM USER_DATA WHERE ID = '"+ID+"' AND PW = '"+PW+"';");
            query.bindValue(":ID",ID);
            query.bindValue(":PW",PW);
            if(query.exec() && query.next())
            {
                senderChat-> write("U@LS");
            }
            else
                senderChat->write("U@LF");
        }
        else if(Join == "JI")
        {
            QString ID;
            ID = line.split('^')[2];

            QSqlQuery query;
            query.prepare("SELECT ID FROM USER_DATA WHERE ID = '"+ID+"';");
            query.bindValue(":ID",ID);
            if(query.exec() && query.next())
            {
                senderChat-> write("U@JI@F");
            }
            else
                senderChat->write("U@JI@S");
        }
        else if(Join == "JPH")
        {
            QString PHONE;
            PHONE = line.split('^')[2];

            QSqlQuery query;
            query.prepare("SELECT PHONE FROM USER_DATA WHERE PHONE = '"+PHONE+"';");
            query.bindValue(":PHONE",PHONE);
            if(query.exec() && query.next())
            {
                senderChat-> write("U@JPH@F");
            }
            else
                senderChat->write("U@JPH@S");
        }
        else if(Join == "JN")
        {
            QString NICKNAME;
            NICKNAME = line.split('^')[2];

            QSqlQuery query;
            query.prepare("SELECT PHONE FROM USER_DATA WHERE PHONE = '"+NICKNAME+"';");
            query.bindValue(":NICKNAME",NICKNAME);
            if(query.exec() && query.next())
            {
                senderChat-> write("U@JN@F");
            }
            else
                senderChat->write("U@JN@S");
        }
        else if(Join == "J")
        {
            QString ID,PW,NAME,PHONE,NICKNAME;
            ID = line.split('^')[2];
            PW = line.split('^')[3];
            NAME = line.split('^')[4];
            PHONE = line.split('^')[5];
            NICKNAME = line.split('^')[6];

            QSqlQuery query;
            query.prepare("INSERT INTO USER_DATA (ID,PW,NAME,PHONE,NICKNAME)"
                          "VALUES ('"+ID+"','"+PW+"','"+NAME+"','"+PHONE+"','"+NICKNAME+"');");

            query.bindValue(":ID",ID);
            query.bindValue(":PW",PW);
            query.bindValue(":NAME",NAME);
            query.bindValue(":PHONE",PHONE);
            query.bindValue(":NICKNAME",NICKNAME);
            query.exec();
        }
        else if(FindID == "SID")
        {
            QString NAME,PHONE;
            NAME = line.split('^')[2];
            PHONE = line.split('^')[3];

            QSqlQuery query;
            query.prepare("SELECT ID FROM USER_DATA WHERE NAME = '"+NAME+"' AND PHONE = '"+PHONE+"';");
            query.bindValue(":NAME",NAME);
            query.bindValue(":PHONE",PHONE);
            if(query.exec() && query.next())
            {
                QString ID = query.value(0).toString();
                senderChat-> write("U@SID@"+ID.toUtf8());
            }
            else
                senderChat->write("U@SID@F");
        }
        else if(FindPW == "SPW")
        {
            QString ID,NAME,PHONE;
            ID = line.split('^')[2];
            NAME = line.split('^')[3];
            PHONE = line.split('^')[4];

            QSqlQuery query;
            query.prepare("SELECT PW FROM USER_DATA WHERE ID = '"+ID+"' AND NAME = '"+NAME+"' AND PHONE = '"+PHONE+"';");
            query.bindValue(":ID",ID);
            query.bindValue(":NAME",NAME);
            query.bindValue(":PHONE",PHONE);
            if(query.exec() && query.next())
            {
                QString PW = query.value(0).toString();
                senderChat-> write("U@SPW@"+PW.toUtf8());
            }
            else
                senderChat->write("U@SPW@F");
        }
    }
}

void ChatServer::Chat_disconnected()
{
    QTcpSocket *Chat = (QTcpSocket*)sender();

    qset_clntChatList.remove(Chat);
    emit chat_update_ChatCNT(qset_clntChatList.count());

    QString user = qmap_userList[Chat];
    qmap_userList.remove(Chat);

    QString str = QString("*연결 종료 IP: %2").arg(Chat->peerAddress().toString());
    emit chat_showMSG(str);

}
