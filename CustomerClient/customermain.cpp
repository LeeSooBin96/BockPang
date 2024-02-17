#include <QMessageBox>

#include "customermain.h"
#include "ui_customermain.h"

CustomerMain::CustomerMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomerMain)
{
    ui->setupUi(this);

    //초기 세팅
    connectServer(); //서버와 연결

}

CustomerMain::~CustomerMain()
{
    delete ui;
}
//서버와 연결
void CustomerMain::connectServer()
{
    tcpSocket = new QTcpSocket(this);

    // QHostAddress server("10.10.20.111");
    QHostAddress server("192.168.0.14");
    qint64 portNum=99999;

    tcpSocket->connectToHost(server,portNum);
    tcpSocket->write("U");

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMSG()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
}
void CustomerMain::disconnected()
{
    qDebug()<<"서버 연결 종료";
}
//서버로 메시지 송신
void CustomerMain::sendServerMSG(QByteArray msg)
{
    tcpSocket->write(msg);
    qDebug()<<"서버로 전송된 메시지 "<<msg;
}
//서버로부터 메시지 수신
void CustomerMain::readMSG()
{
    QString msg;
    if(tcpSocket->bytesAvailable()>0) //읽을 메시지가 있다면
    {
        msg.append(tcpSocket->readAll());
        qDebug()<<"서버로부터 "<<msg;
        // msg.append(tcpSocket->readAll()); //너무 길면 더 읽어야하는데
    }
    if(msg.split('@').size()==1) //번호만 보낸것이기에
    {
        myNum=msg; //부여받은 번호 저장
        qDebug()<<"부여받은 번호:"<<myNum;

        //확인용----------------------------------------------------------------나중에 꼭 지워
        // myNum="1"; //임시

        // order = new OrderPage(this,&myNum);
        // ui->mainStack->addWidget(order);
        // ui->mainStack->setCurrentWidget(order);

        // connect(order,SIGNAL(signal_sendMSG(QByteArray)),this,SLOT(sendServerMSG(QByteArray)));
        //-----------------------------------------------------------------------

    }
    else if(msg.split('@')[0]=="Q") //고객 문의 응답
    {
        order->ArriveQuestionAnswer(msg.split('@')[1]);
    }
    else if(msg.split('@')[0]=="S") //검색 결과 수신
    {
        order->PrintResultSearch(msg.split('@'));
    }
    else if(msg.split('@')[0]=="T") //카테 목록 수신
    {
        order->PrintSelectedCate(msg.split('@'));
    }
    else if(msg.split('@')[0]=="M") //가게 정보 수신
    {
        order->PrintMarcketBase(msg.split('@'));
    }
    else if(msg.split('@')[0]=="MC") //메뉴 정보 수신
    {
        //길면 잘리기 때문에 대비하기 --안먹힘
        // while(msg.split('@').size()<msg.split('@')[1].toInt()*4+2) msg.append(tcpSocket->readAll()); //메뉴 개수
        for(int i=0;i<1000;i++) msg.append(tcpSocket->readAll());
        order->PrintMenuList(msg.split('@'));
    }
    else if(msg.split('@')[0]=="MD") //매장 상세 정보 수신
    {
        // while(tcpSocket->bytesAvailable()>0) msg.append(tcpSocket->readAll()); //메뉴 개수
        // for(int i=0;i<1000000000;i++) msg.append(tcpSocket->readAll());
        // qDebug()<<msg.size();
        // qDebug()<<tcpSocket->readAll()
        // while()
        //하 길이 길어지니까 길이 접두사 없이 통신하기 힘드네
        // int len=msg.split('@')[1].toInt()+msg.split('@')[1].size()+4;
        // while(msg.size()<len) msg.append(tcpSocket->readAll());
        // for(int i=0;i<1000000;i++) msg.append(tcpSocket->readAll());
        order->PrintMarcketInfo(msg.split('@'));

    }
    else if(msg.split('@')[0]=="MO") //옵션 내용 수신
    {
        order->PrintMenuOPtion(msg.split('@'));
    }
    else if(msg.split('@')[0]=="U") //로그인 관련 수신 메시지
    {
        QString ck=msg.split('@')[1];
        //로그인 성공 여부 판단
        if(ck=="LS")
        {
            Nickname=msg.split('@')[2]; //로그인된 유저 닉네임 저장
            qDebug()<<Nickname;
            // ui->mainStack->setCurrentIndex(1); //넘어가는 화면 만들까
            //메인 주문 화면으로
            order = new OrderPage(this,&myNum);
            ui->mainStack->addWidget(order);
            ui->mainStack->setCurrentWidget(order);

            connect(order,SIGNAL(signal_sendMSG(QByteArray)),this,SLOT(sendServerMSG(QByteArray)));
        }
        else if(ck=="LF")
        {
            QMessageBox::critical(this,"경고","아이디 또는 비밀번호가 일치하지 않습니다.",QMessageBox::Ok);
        }
        //아이디 중복검사 결과
        else if(ck=="JI")
        {
            login->ResultJID(msg.split('@')[2]);
        }
        //휴대폰 중복검사 결과
        else if(ck=="JPH")
        {
            login->ResultJPH(msg.split('@')[2]);
        }
        //닉네임 중복검사 결과
        else if(ck=="JN")
        {
            login->ResultNICK(msg.split('@')[2]);
        }
        //아이디 찾기 결과
        else if(ck=="SID")
        {
            login->ResultSID(msg.split('@')[2]);
        }
        //비밀번호 찾기 결과
        else if(ck=="SPW")
        {
            login->ResultSPW(msg.split('@')[2]);
        }

    }
}
//로그인 페이지로 이동
void CustomerMain::gotoLogin()
{
    //로그인 페이지
    login = new LoginPage(this,&myNum);
    ui->mainStack->addWidget(login);
    ui->mainStack->setCurrentWidget(login);

    connect(login,SIGNAL(signal_sendMSG(QByteArray)),this,SLOT(sendServerMSG(QByteArray)));
}
