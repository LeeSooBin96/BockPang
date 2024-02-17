#include "garbagecenter.h"
#include "ui_garbagecenter.h"

GarbageCenter::GarbageCenter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GarbageCenter)
{
    ui->setupUi(this);
    // qDebug()<<nick<<" 접속 ";
}

GarbageCenter::~GarbageCenter()
{
    delete ui;
}

void GarbageCenter::connectingUser(QString nick)
{

    ui->LWCustomList->addItem(nick);
    QListWidget* chatScreen= new QListWidget(this);
    chatScreen->setSelectionMode(QAbstractItemView::NoSelection);
    ui->stackedWidget->addWidget(chatScreen);

    ChatMatch[nick]=chatScreen; //위젯 저장

    QString msg=nick+"님 환영합니다. \n복팡이츠 고객센터입니다.\n무엇을 도와드릴까요?";
    text=new QListWidgetItem(msg);
    text->setTextAlignment(Qt::AlignRight);
    chatScreen->addItem(text);
    emit signal_sendMSG(nick,msg);
}
//문의내용 수신
void GarbageCenter::ReceiveQuestion(QString nick,QString msg)
{
    text=new QListWidgetItem(nick+" : "+msg);
    text->setTextAlignment(Qt::AlignLeft);
    ChatMatch[nick]->addItem(text);

    ui->LWCustomList->setCurrentRow(ui->stackedWidget->indexOf(ChatMatch[nick]));
    emit ui->LWCustomList->clicked(ui->LWCustomList->currentIndex());
}
void GarbageCenter::on_LWCustomList_clicked(const QModelIndex &index) //채팅방 이동
{
    ui->stackedWidget->setCurrentIndex(index.row());
}

