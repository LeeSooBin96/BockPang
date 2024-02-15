#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include "chatserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Server;
}
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private:
    Ui::Server *ui;

    QHostAddress hostAddress;
    qint16 hostPort;
    QString title;
    QHostAddress getMyIP();

    ChatServer *server;
private slots:
    void server_update_ChatCNT(int users);
    void server_showMSG(QString msg);
};
#endif // SERVER_H
