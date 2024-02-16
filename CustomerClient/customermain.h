#ifndef CUSTOMERMAIN_H //메인 진행 - 서버와 통신
#define CUSTOMERMAIN_H

#include <QWidget>
#include <QTcpSocket> //통신하기 위해

#include "loginpage.h" //로그인 페이지 클래스 추가
#include "orderpage.h" //주문 페이지 클래스 추가

namespace Ui {
class CustomerMain;
}

class CustomerMain : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerMain(QWidget *parent = nullptr);
    ~CustomerMain();


private:
    Ui::CustomerMain *ui;
    QTcpSocket* tcpSocket; //서버와 통신하기 위한 소켓
    QString myNum; //서버로부터 부여받은 번호
    LoginPage* login; //로그인 클래스
    OrderPage* order; //주문 페이지 클래스

    void connectServer(); //서버와 연결

private slots:
    void disconnected(); //서버 연결 끊겼을때
    void readMSG(); //서버로부터 메시지 수신
    void sendServerMSG(QByteArray msg); //서버에 메시지 전송
    void gotoLogin(); //로그인 페이지로 이동

};

#endif // CUSTOMERMAIN_H
