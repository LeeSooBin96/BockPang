#include "marcketmain.h"
#include "ui_marcketmain.h"

MarcketMain::MarcketMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MarcketMain)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(3,250);


}

MarcketMain::~MarcketMain()
{
    delete ui;
}
//서버와 연결
void MarcketMain::connectServer()
{
    tcpSocket = new QTcpSocket(this);

    // QHostAddress server("10.10.20.111");
    QHostAddress server("10.10.20.98");
    qint64 portNum=99999;

    tcpSocket->connectToHost(server,portNum);
    tcpSocket->write("MO^1");

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMSG()));
    connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));
}
//서버로부터 메시지 수신
void MarcketMain::readMSG()
{
    QString msg;
    if(tcpSocket->bytesAvailable()>0) //읽을 메시지가 있다면
    {
        msg=tcpSocket->readAll();
        qDebug()<<"서버로부터 "<<msg;
    }
    if(msg.split('@').size()==1) //번호만 보낸것이기에
    {
        myNum=msg; //부여받은 번호 저장
        qDebug()<<"부여받은 번호:"<<myNum;
        this->setStatusTip("서버에 연결되었습니다.");
    }
    else if(msg.split('@')[0]=="P") //주문내용 수신
    {
        PrintOrderInfo(msg.split('@')); //화면에 출력
    }
}
//수신된 주문 정보 출력
void MarcketMain::PrintOrderInfo(QStringList olist)
{
    int index=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(index);
    QTableWidgetItem* item=new QTableWidgetItem(QString::number(ui->tableWidget->rowCount()+1));
    ui->tableWidget->setItem(index,0,item);
    item=new QTableWidgetItem(olist[1]); //주문번호
    orderList.push_back(olist[1]); //주문번호 리스트에 추가
    ui->tableWidget->setItem(index,1,item);
    item=new QTableWidgetItem(olist[2]); //고객 닉네임
    ui->tableWidget->setItem(index,2,item);
    item=new QTableWidgetItem(olist[5].split('/').join('\n')); //메뉴내용
    ui->tableWidget->setItem(index,3,item);
    item=new QTableWidgetItem(olist[6]);
    ui->tableWidget->setItem(index,4,item);
    item=new QTableWidgetItem(olist[7]);
    ui->tableWidget->setItem(index,5,item);
}
//서버에 주문 승인 여부 전송
void MarcketMain::SendOrderAccept()
{
    int index=ui->tableWidget->currentRow(); //선택된 행
    qDebug()<<index;
    QByteArray msg="O"+myNum.toUtf8()+"^";
    if(sender()->objectName().split('_')[1]=="ok")
    {
        msg.append("S^");
    }
    else
    {
        msg.append("F^");
    }
    msg.append(orderList[index].toUtf8());
    tcpSocket->write(msg);
    qDebug()<<"서버로 전송된 메시지 : "<<msg;
    //거절된 주문정보 삭제
    if(sender()->objectName().split('_')[1]=="back")
    {
        orderList.removeAt(index);
        ui->tableWidget->removeRow(index);
    }
}
//서버에 조리 완료 신호
void MarcketMain::SendCookFinish()
{
    int index=ui->tableWidget->currentRow(); //선택된 행
    qDebug()<<index;

    tcpSocket->write("F"+myNum.toUtf8()+"^"+orderList[index].toUtf8());
    qDebug()<<"조리 완료";
}
