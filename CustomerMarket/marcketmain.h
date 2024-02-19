#ifndef MARCKETMAIN_H
#define MARCKETMAIN_H

#include <QMainWindow>
#include <QTcpSocket> //서버와 통신 위함

QT_BEGIN_NAMESPACE
namespace Ui {
class MarcketMain;
}
QT_END_NAMESPACE

class MarcketMain : public QMainWindow
{
    Q_OBJECT

public:
    MarcketMain(QWidget *parent = nullptr);
    ~MarcketMain();

private:
    Ui::MarcketMain *ui;
    QTcpSocket* tcpSocket; //통신을 위한 소켓
    QString myNum; //서버로부터 부여받은 번호
    QVector<QString> orderList; //들어온 주문 번호 리스트

    void PrintOrderInfo(QStringList olist); //수신된 주문 내용 출력

private slots:
    void connectServer(); //서버와 연결
    void readMSG(); //서버로부터 메시지 수신

    void SendOrderAccept(); //서버에 주문 승인 여부 전송
    void SendCookFinish(); //서버에 조리 완료 신호
};
#endif // MARCKETMAIN_H
