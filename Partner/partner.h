#ifndef PARTNER_H
#define PARTNER_H

#include <QWidget>
#include <QTcpSocket> //통신하기 위해

QT_BEGIN_NAMESPACE
namespace Ui {
class Partner;
}
QT_END_NAMESPACE

class Partner : public QWidget
{
    Q_OBJECT

public:
    explicit Partner(QWidget *parent = nullptr);
    ~Partner();

private:
    Ui::Partner *ui;
    QTcpSocket* tcpSocket;
    QString myNum;

    void connectServer();

private slots:
    void MSG_Read();
    void disconnect();
    void sendServerMSG(QByteArray msg);
    void Accept();
    void Start();
    void Complete();
};
#endif // PARTNER_H
