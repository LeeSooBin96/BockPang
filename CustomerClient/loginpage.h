#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr,QString* code = nullptr); //생성될때 코드 받아와야함
    ~LoginPage();

    //메인에서 접근하는 함수
    void ResultJID(QString); //아이디 중복검사 결과 처리


signals:
    void signal_sendMSG(QByteArray);

private:
    Ui::LoginPage *ui;
    QString myCode; //서버와 통신시 사용할 코드 ( U+클라이언트번호 )

    //회원가입시 검사값
    bool ckID=false;
    bool ckPHONE=false;
    bool ckNICK=false;

private slots:
    void LoginProgress(); //로그인 진행
    void CheckID(const QString &arg1); //아이디 검사(회원가입)
    void SendJoinID(); //서버에 입력된 아이디 전송해 중복검사 요청
    void CheckPW(const QString &arg1); //비밀번호 검사(회원가입)
    void CheckPHONE(); //휴대폰번호 검사(회원가입)

    //화면이동 슬롯
    void gotoLogin(); //로그인 화면으로
    void gotoJoin(); //회원가입 화면으로


};

#endif // LOGINPAGE_H
