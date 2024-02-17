#ifndef GARBAGECENTER_H
#define GARBAGECENTER_H

#include <QDialog>
#include <QTextBrowser>
#include <QListWidgetItem>

namespace Ui {
class GarbageCenter;
}

class GarbageCenter : public QDialog
{
    Q_OBJECT

public:
    explicit GarbageCenter(QWidget *parent = nullptr);
    ~GarbageCenter();

    void connectingUser(QString); //유저 접속
    void ReceiveQuestion(QString,QString); //문의 수신

signals:
    void signal_sendMSG(QString nick,QString msg);

private slots:
    void on_LWCustomList_clicked(const QModelIndex &index);

private:
    Ui::GarbageCenter *ui;
    QMap<QString,QListWidget*> ChatMatch;
    QListWidgetItem *text;

};

#endif // GARBAGECENTER_H
