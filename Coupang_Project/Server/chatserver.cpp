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
    else if(line.split('^')[0].front() == 'S')
    {
        QSqlQuery qry;
        QString keyword;
        qry.prepare("SELECT NUM,MARCKET,MAINMENU,TIP FROM MARCKET_INFO");
        qry.exec();
        QByteArray message;
        keyword = line.split('^')[1];
        while(qry.next())
        {
            bool ck=false;
            for(int i=0;i<5;i++)
            {
                if(qry.value(i).toString().indexOf(keyword)>=0)
                {
                    ck=true;
                    break;
                }
            }
            if(ck)
            {
                message.push_back(QByteArray("S@"));
                message.push_back(qry.value(0).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry.value(1).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry.value(2).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry.value(3).toByteArray());
                senderChat->write(message);
                senderChat->waitForBytesWritten(1000);
                senderChat->waitForReadyRead(3000);
                senderChat->readAll();
                message.clear();
            }
        }
    }
    else if(line.split('^')[0].front() == 'T')
    {
        QSqlQuery qry;
        QString keyword;
        keyword = line.split('^')[1];
        qry.prepare("SELECT NUM,MARCKET,MAINMENU,TIP FROM MARCKET_INFO WHERE CATEGORY = "+keyword+";");
        qry.exec();
        QByteArray message;
        while(qry.next())
        {
            message.push_back(QByteArray("T@"));
            message.push_back(qry.value(0).toByteArray());
            message.push_back(QByteArray("@"));
            message.push_back(qry.value(1).toByteArray());
            message.push_back(QByteArray("@"));
            message.push_back(qry.value(2).toByteArray());
            message.push_back(QByteArray("@"));
            message.push_back(qry.value(3).toByteArray());
            senderChat->write(message);
            senderChat->waitForBytesWritten(1000);
            senderChat->waitForReadyRead(3000);
            senderChat->readAll();
            message.clear();
        }
    }
    else if(line.split('^')[0].front() == 'M')
    {
        if(line.split('^')[1] == 'C')
        {
            QString Category;
            QSqlQuery qry1,qry2;
            Category = line.split('^')[3];
            qry1.prepare("SELECT COUNT(CATEGORY) FROM MENU_TYPE WHERE CATEGORY = "+Category+";");
            qry2.prepare("SELECT NUM,MENU,INTRODUCE,PAY FROM MENU_TYPE WHERE CATEGORY = "+Category+";");
            qry1.exec();
            qry2.exec();
            QByteArray message;
            message.push_back(QByteArray("MC@"));
            qry1.next();
            message.push_back(qry1.value(0).toByteArray());
            for(int i=0; i<qry1.value(0).toInt();i++)               // 카테고리별 메뉴이름 / 소개 / 가격
            {
                qry2.next();
                message.push_back(QByteArray("@"));
                message.push_back(qry2.value(0).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry2.value(1).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry2.value(2).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry2.value(3).toByteArray());
            }
            senderChat->write(message);
        }
        else
        {
            QSqlQuery qry1,qry2,qry3;
            QString keyword;
            keyword = line.split('^')[1];
            qry1.prepare("SELECT MARCKET,SALETIME,MINIMUMPAY,TIP FROM MARCKET_INFO WHERE CATEGORY =  "+keyword+" ;");
            qry2.prepare("SELECT COUNT(CATEGORY) FROM MENU_CATEGORY_"+keyword+";");
            qry3.prepare("SELECT CATEGORY FROM MENU_CATEGORY_"+keyword+";");
            qry1.exec();
            qry2.exec();
            qry3.exec();
            QByteArray message;
            if(qry1.next() && qry2.next())
            {
                message.push_back(QByteArray("M@"));
                message.push_back(qry1.value(0).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(1).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(2).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(3).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry2.value(0).toByteArray());
            }
            while(qry3.next())
            {
                message.push_back(QByteArray("@"));
                message.push_back(qry3.value(0).toByteArray());
            }
            senderChat->write(message);
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
