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
    myNum="1"; //임시

}

CustomerMain::~CustomerMain()
{
    delete ui;
}
//서버와 연결
void CustomerMain::connectServer()
{
    tcpSocket = new QTcpSocket(this);

    QHostAddress server("10.10.20.111");
    qint64 portNum=99999;

    tcpSocket->connectToHost(server,portNum);
    tcpSocket->write("U");

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMSG()));
    connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));
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
        msg=tcpSocket->readAll();
        qDebug()<<"서버로부터 "<<msg;
    }
    if(msg.split('@').size()==1) //번호만 보낸것이기에
    {
        myNum=msg; //부여받은 번호 저장
        qDebug()<<"부여받은 번호:"<<myNum;
    }
    else if(msg.split('@')[0]=="U") //로그인 관련 수신 메시지
    {
        QString ck=msg.split('@')[1];
        //로그인 성공 여부 판단
        if(ck=="LS")
        {
            //메인 화면으로
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
    ui->mainStack->setCurrentIndex(1);

    connect(login,SIGNAL(signal_sendMSG(QByteArray)),this,SLOT(sendServerMSG(QByteArray)));
}
