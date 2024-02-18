//소켓 통신
#include <QtWidgets>
#include <QDebug>
#include "chatserver.h"


ChatServer::ChatServer(QObject *parent): QTcpServer(parent)
{
    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("/Users/Aiot/Documents/Bokpang");

    if(!DB.open())
        qDebug() << "fail Database";
    else
        qDebug() << "Connect";
    //고객센터 오픈
    center=new GarbageCenter();
    center->hide();

    QSqlQuery qry1;
    qry1.prepare("UPDATE MARCKET_INFO SET FLAG = 'F' WHERE NUM = 1;");
    qry1.exec();

    connect(center,SIGNAL(signal_sendMSG(QString,QString)),this,SLOT(send_MSG(QString,QString)));
}

ChatServer::~ChatServer()
{
    foreach(QTcpSocket *client,qset_clntChatList)
        client->disconnectFromHost();
}

void ChatServer::incomingConnection(qintptr socketfd) //오버라이드? --새로운 연결 요청 들어올때마다
{
    QTcpSocket *newConnectedChat = new QTcpSocket(this);

    newConnectedChat -> setSocketDescriptor(socketfd); //소켓 디스크립터 설정

    qset_clntChatList.insert(newConnectedChat); //소켓 집합에 추가
    emit chat_update_ChatCNT(qset_clntChatList.count()); //접속자수 갱신

    QString str = QString("새로운 접속자 : %1").arg(newConnectedChat->peerAddress().toString());
    emit chat_showMSG(str); //접속자 정보 출력

    connect(newConnectedChat,SIGNAL(readyRead()),this,SLOT(read_MSG()));

    connect(newConnectedChat,SIGNAL(disconnected()),this,SLOT(Chat_disconnected()));
}
void ChatServer::read_MSG()
{
    QTcpSocket* senderChat = (QTcpSocket*)sender();
    QString line = QString::fromUtf8(senderChat->readAll()).trimmed();

    if(line.size() == 1 )
    {
        newchat.append(senderChat);

        int index = newchat.indexOf(senderChat);
        senderChat -> write(QString::number(index).toUtf8());
    }
    else if(line.split('^')[0].front() == 'Q') //고객 문의창으로
    {
        if(line.split('^')[1]=="")
        {
            center->connectingUser(qmap_userList[senderChat]);
            if(center->isHidden())
                center->show();
        }
        else if(line.split('^')[1]=="Q")
        {
            center->ReceiveQuestion(qmap_userList[senderChat],line.split('^')[2]);
        }
    }
    else if(line.split('^')[0].front() == 'U')                  // 고객 로그인 / 회원가입 관련 처리
    {
        QString Login = line.split('^')[1];
        QString Join = line.split('^')[1];
        QString FindID = line.split('^')[1];
        QString FindPW = line.split('^')[1];
        if(Login == "L")
        {
            QString ID,PW,NICKNAME;
            ID = line.split('^')[2];
            PW = line.split('^')[3];

            QSqlQuery query1,query2;
            query1.prepare("SELECT ID,PW FROM USER_DATA WHERE ID = '"+ID+"' AND PW = '"+PW+"';");
            query2.prepare("SELECT NICKNAME FROM USER_DATA WHERE ID = '"+ID+"' AND PW = '"+PW+"';");
            query1.bindValue(":ID",ID);
            query1.bindValue(":PW",PW);
            if(query1.exec() && query1.next() && query2.exec() && query2.next())
            {
                NICKNAME = query2.value(0).toString();
                if(qmap_userList.values().contains(NICKNAME)) //이미 등록된 소켓 있으면
                {
                    senderChat-> write("U@LS@"+NICKNAME.toUtf8()+"@F");
                    return;
                }
                qmap_userList[senderChat]=NICKNAME;

                senderChat-> write("U@LS@"+NICKNAME.toUtf8()+"@S");
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
    else if(line.split('^')[0].front() == 'S')                      // 검색
    {
        QSqlQuery qry;
        QString keyword;
        qry.prepare("SELECT NUM,MARCKET,MAINMENU,TIP,FLAG FROM MARCKET_INFO");
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
                message.push_back(QByteArray("@"));
                message.push_back(qry.value(4).toByteArray());
                senderChat->write(message);
                senderChat->waitForBytesWritten(1000);
                senderChat->waitForReadyRead(3000);
                senderChat->readAll();
                message.clear();
            }
        }
    }
    else if(line.split('^')[0].front() == 'T')                      // 카테고리 선택
    {
        QSqlQuery qry;
        QString keyword;
        keyword = line.split('^')[1];
        qry.prepare("SELECT NUM,MARCKET,MAINMENU,TIP,FLAG FROM MARCKET_INFO WHERE CATEGORY = "+keyword+";");
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
            message.push_back(QByteArray("@"));
            message.push_back(qry.value(4).toByteArray());
            senderChat->write(message);
            senderChat->waitForBytesWritten(1000);
            senderChat->waitForReadyRead(3000);
            senderChat->readAll();
            message.clear();
        }
    }
    else if(line.split('^')[0].front() == 'M')                      // 매장 선택
    {
        if(line.split('^')[1] == 'C')                               // 카테고리별 메뉴이름 / 소개 / 가격
        {
            QString Category,NUM;
            QSqlQuery qry1,qry2;
            NUM = line.split('^')[2];
            Category = line.split('^')[3];
            qry1.prepare("SELECT COUNT(CATEGORY) FROM MENU_TYPE_"+NUM+" WHERE CATEGORY = "+Category+";");
            qry2.prepare("SELECT NUM,MENU,INTRODUCE,PAY FROM MENU_TYPE_"+NUM+" WHERE CATEGORY = "+Category+";");
            qry1.exec();
            qry2.exec();
            QByteArray message;
            message.push_back(QByteArray("MC@"));
            qry1.next();
            message.push_back(qry1.value(0).toByteArray());
            for(int i=0; i<qry1.value(0).toInt();i++)
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
        else if(line.split('^')[1] == 'N')                              // 옵션
        {
            QString Opt_num;
            QSqlQuery qry1,qry2;
            Opt_num = line.split('^')[2];
            qry1.prepare("SELECT (COUNT(NUM)-1) FROM MENU_OPTION_1 GROUP BY NUM;");
            qry2.prepare("SELECT OPTION,PAY FROM MENU_OPTION_1;");
            qry1.exec();
            qry2.exec();
            QByteArray message;
            message.push_back(QByteArray("MO"));
            while(qry1.next())
            {
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(0).toByteArray());
                for(int i=0; i<=qry1.value(0).toInt();i++)
                {
                    qry2.next();
                    message.push_back(QByteArray("@"));
                    message.push_back(qry2.value(0).toByteArray());
                    message.push_back(QByteArray("@"));
                    message.push_back(qry2.value(1).toByteArray());
                }
            }
            senderChat->write(message);
        }
        else if(line.split('^')[1] == 'D')                               // 매장 소개
        {
            QString MC_NUM;
            QSqlQuery qry1;
            MC_NUM = line.split('^')[2];
            qry1.prepare("SELECT INTRODUCE,PHONE,PAYMENT,CEO,COMPANY,CEONUMBER,ORIGIN FROM MARCKET_INFO;");
            qry1.exec();
            QByteArray message;

            message.push_back(QByteArray("MD@"));
            while(qry1.next())
            {
                message.push_back(qry1.value(0).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(1).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(2).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(3).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(4).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(5).toByteArray());
                message.push_back(QByteArray("@"));
                message.push_back(qry1.value(6).toByteArray());
                message.push_back(QByteArray("@"));
            }
            senderChat->write(message);
        }
        else if(line.split('^')[0] == "MO")
        {
            newchat.append(senderChat);

            int index = newchat.indexOf(senderChat);
            senderChat -> write(QString::number(index).toUtf8());

            QString Flag;
            QSqlQuery qry1;
            Flag = line.split('^')[1];
            qry1.prepare("SELECT NUM,FLAG FROM MARCKET_INFO WHERE NUM = "+Flag+";");

            QByteArray message;
            if(qry1.exec() && qry1.next())
            {
                QString NUM = qry1.value(0).toString();
                QString FLAG = qry1.value(1).toString();
                if(FLAG == "F")
                {
                    qry1.prepare("UPDATE MARCKET_INFO SET FLAG = 'T' WHERE NUM = "+Flag+";");
                    qry1.exec();

                }
                senderChat -> write(NUM.toUtf8());
            }
        }

        else
        {
            QSqlQuery qry1,qry2,qry3;                       // 카테고리 선택시 선택창에 뜨는 정보
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
    else if(line.split('^')[0].front() == 'P')                              // 주문 정보 저장 및 주문 번호 전송
    {
        QSqlQuery qry1,qry2;
        QString NICKNAME,MARCKET_NUM,EA,MENU,TOTAL,PAYMENT,ORDER_NUM;
        NICKNAME = line.split('^')[1];
        MARCKET_NUM = line.split('^')[2];
        EA = line.split('^')[3];
        MENU = line.split('^')[4];
        TOTAL = line.split('^')[5];
        PAYMENT = line.split('^')[6];

        qry1.prepare("INSERT INTO ORDER_INFO_1 (NICKNAME,MARCKET_NUM,EA,MENU,TOTAL,PAYMENT) VALUES ('"+NICKNAME+"',"+MARCKET_NUM+","+EA+",'"+MENU+"',"+TOTAL+","+PAYMENT+");");
        qry2.prepare("SELECT ORDER_NUM FROM ORDER_INFO_1 WHERE NICKNAME = '"+NICKNAME+"';");
        qry1.exec();
        qry2.exec();
        if(qry2.next())
        {
            QString ORDER_NUM = qry2.value(0).toString();
            senderChat-> write("P@"+ORDER_NUM.toUtf8());
        }
        else
        {
            senderChat-> write("P@F");
        }

    }
}
//고객센터 문의 응답 내용 전송
void ChatServer::send_MSG(QString nick,QString msg)
{
    qDebug()<<nick<<msg;
    qmap_userList.key(nick)->write("Q@"+msg.toUtf8());
}
void ChatServer::Chat_disconnected()
{
    QTcpSocket *Chat = (QTcpSocket*)sender();

    qset_clntChatList.remove(Chat);
    emit chat_update_ChatCNT(qset_clntChatList.count());

    // QString user = qmap_userList[Chat];
    qmap_userList.remove(Chat);

    QString str = QString("*연결 종료 IP: %2").arg(Chat->peerAddress().toString());
    emit chat_showMSG(str);

}
