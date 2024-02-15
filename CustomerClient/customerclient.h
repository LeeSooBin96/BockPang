#ifndef CUSTOMERCLIENT_H
#define CUSTOMERCLIENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CustomerClient;
}
QT_END_NAMESPACE

class CustomerClient : public QWidget
{
    Q_OBJECT

public:
    CustomerClient(QWidget *parent = nullptr);
    ~CustomerClient();

private:
    Ui::CustomerClient *ui;
};
#endif // CUSTOMERCLIENT_H
