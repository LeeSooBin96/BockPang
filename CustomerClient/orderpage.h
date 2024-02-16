#ifndef ORDERPAGE_H //주문 페이지 - 어플 메인 화면
#define ORDERPAGE_H

#include <QWidget>

namespace Ui {
class OrderPage;
}

class OrderPage : public QWidget
{
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr);
    ~OrderPage();

private:
    Ui::OrderPage *ui;

private slots:
    void SendSearchKey(); //서버에 검색어 전송
};

#endif // ORDERPAGE_H
