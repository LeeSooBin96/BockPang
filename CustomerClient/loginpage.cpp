#include <QMessageBox>

#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent,QString *code)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    myCode="U"+*code;
    ui->setupUi(this);

    gotoLogin();
}

LoginPage::~LoginPage()
{
    delete ui;
}
//로그인 진행
void LoginPage::LoginProgress()
{
    if(ui->ID_Edit->text().isEmpty()||ui->PW_Edit->text().isEmpty()) //하나라도 입력이 없으면
    {
        QMessageBox::critical(this,"경고","모두 입력해주세요",QMessageBox::Ok);
        return;
    }
    QByteArray msg;
    msg=myCode.toUtf8()+"^L^"+ui->ID_Edit->text().toUtf8()+"^"+ui->PW_Edit->text().toUtf8();
    emit signal_sendMSG(msg); //와 시그널로 데이터 넘기기 성공!
}

//회원가입 부분===========================================================================================
//아이디 검사
void LoginPage::CheckID(const QString &arg1)
{
    if(arg1.isEmpty()) return;
    ui->lbl_ckID->setText("영문으로 시작하는 6~20자 영문(소문자), 숫자만 사용");
    if(arg1[0].isLower()&&arg1.size()>=6&&arg1.size()<=20)
    {
        for(QChar l:arg1)
        {
            if(!l.isLower()&&!l.isDigit())
            {
                ui->lbl_ckID->setText("영문으로 시작하는 6~20자 영문(소문자), 숫자만 사용");
                return;
            }
            else
            {
                ui->lbl_ckID->clear();
                ui->Btn_confirmID->setEnabled(true);
            }
        }
    }
}
//입력된 아이디 서버에 전달 (중복검사 위함 )
void LoginPage::SendJoinID()
{
    QByteArray msg;
    msg=myCode.toUtf8()+"^JI^"+ui->ID_JoinEdit->text().toUtf8();
    emit signal_sendMSG(msg);
}
void LoginPage::ResultJID(QString ck)
{
    if(ck=="S")
    {
        ui->lbl_ckID->setText("사용가능한 아이디입니다.");
        ui->PW_JoinEdit->setFocus();
        ckID=true;
    }
    else
    {
        ui->lbl_ckID->setText("중복된 아이디입니다.");
        ui->ID_JoinEdit->clear();
        ui->Btn_confirmID->setEnabled(false);
    }
}
//비밀번호 검사
void LoginPage::CheckPW(const QString &arg1)
{
    if(arg1.isEmpty()) return;
    unsigned short lnum=0, dnum=0, pnum=0;
    ui->lbl_ckPW->setText("8~12자의 영문, 숫자, 특수문자 중 2가지 이상");
    if(arg1.size()>=8&&arg1.size()<=12)
    {
        for(QChar l: arg1)
        {
            if(l.isLetter())
            {
                lnum++;
            }
            else if(l.isDigit())
            {
                dnum++;
            }
            else if(l.isPunct())
            {
                pnum++;
            }
            else
            {
                ui->lbl_ckPW->setText("8~12자의 영문, 숫자, 특수문자 중 2가지 이상");
                return;
            }
        }
    }
    if((lnum>0&&dnum>0)||(lnum>0&&pnum>0)||(pnum>0&&dnum>0))
    {
        ui->lbl_ckPW->clear();
    }
}
//휴대폰 번호 검사
void LoginPage::CheckPHONE()
{
    ui->PHONE_JoinEdit->setText(ui->PHONE_JoinEdit->text().trimmed().split('-').join(""));
    for(QChar l:ui->PHONE_JoinEdit->text())
    {
        if(!l.isDigit())
        {
            QMessageBox::critical(this,"경고","숫자만 입력해주세요",QMessageBox::Ok);
            ui->PHONE_JoinEdit->clear();
            return;
        }
    }
    QByteArray msg=myCode.toUtf8()+"^JPH^"+ui->PHONE_JoinEdit->text().toUtf8();
    emit signal_sendMSG(msg);
}
// void LoginPage::ResultJID(QString ck)
// {
//     if(ck=="S")
//     {
//         ui->lbl_ckID->setText("사용가능한 아이디입니다.");
//         ui->PW_JoinEdit->setFocus();
//         ckID=true;
//     }
//     else
//     {
//         ui->lbl_ckID->setText("중복된 아이디입니다.");
//         ui->ID_JoinEdit->clear();
//         ui->Btn_confirmID->setEnabled(false);
//     }
// }

//로그인 화면으로
void LoginPage::gotoLogin()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->ID_Edit->clear();
    ui->PW_Edit->clear();
}
//회원가입 화면으로
void LoginPage::gotoJoin()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->ID_JoinEdit->clear();
    ui->PW_JoinEdit->clear();
    ui->NAME_JoinEdit->clear();
    ui->PHONE_JoinEdit->clear();
    ui->NICKNAME_JoinEdit->clear();

    ui->Btn_confirmJoin->setEnabled(false);
    ui->Btn_confirmID->setEnabled(false);
    ui->Btn_confirmPHONE->setEnabled(false);
    ui->Btn_confirmNICKNAME->setEnabled(false);
}









