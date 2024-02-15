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
    void ResultJPH(QString); //휴대폰 중복검사 결과 처리
    void ResultNICK(QString); //닉네임 중복검사 결과 처리
    void ResultSID(QString); //아이디 찾기 결과
    void ResultSPW(QString); //비밀번호 찾기 결과


signals:
    void signal_sendMSG(QByteArray);

private:
    Ui::LoginPage *ui;
    QString myCode; //서버와 통신시 사용할 코드 ( U+클라이언트번호 )

    //회원가입시 검사값
    bool ckID=false;
    bool ckPHONE=false;
    bool ckNICK=false;
    //회원가입 인증 정보 저장
    QString ATid;
    QString ATphone;
    QString ATnick;

private slots:
    void LoginProgress(); //로그인 진행
    void CheckID(const QString &arg1); //아이디 검사(회원가입)
    void SendJoinID(); //서버에 입력된 아이디 전송해 중복검사 요청
    void CheckPW(const QString &arg1); //비밀번호 검사(회원가입)
    void CheckPHONE(); //휴대폰번호 검사(회원가입)
    void SendNICK(); //서버에 닉네임 중복검사 요청
    void JoinProgress(); //회원가입 진행
    void RequestSID(); //서버에 아이디 찾기 요청
    void RequestSPW(); //서버에 비밀번호 찾기 요청

    //화면이동 슬롯
    void gotoLogin(); //로그인 화면으로
    void gotoJoin(); //회원가입 화면으로
    void gotoSID(); //아이디 찾기 화면으로
    void gotoSPW(); //비밀번호 찾기 화면으로


};

#endif // LOGINPAGE_H
