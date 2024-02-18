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
    QString msg=nick+"님 환영합니다. \n복팡이츠 고객센터입니다.\n무엇을 도와드릴까요?";
    // qDebug()<<ChatMatch.contains(nick); //있는지 확인 가능
    if(ChatMatch.isEmpty()||!ChatMatch.contains(nick))
    {
        ui->LWCustomList->addItem(nick);
        QListWidget* chatScreen= new QListWidget(this);
        chatScreen->setSelectionMode(QAbstractItemView::NoSelection);
        ui->stackedWidget->addWidget(chatScreen);

        ChatMatch[nick]=chatScreen; //위젯 저장

        text=new QListWidgetItem(msg);
        text->setTextAlignment(Qt::AlignRight);
        chatScreen->addItem(text);
    }
    else
    {
        text=new QListWidgetItem(msg);
        text->setTextAlignment(Qt::AlignRight);
        ChatMatch[nick]->addItem(text);

        ui->LWCustomList->setCurrentRow(ui->stackedWidget->indexOf(ChatMatch[nick]));
        emit ui->LWCustomList->clicked(ui->LWCustomList->currentIndex());
    }
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


void GarbageCenter::on_BtnInput_clicked()
{
    if(!ui->LEInputText->text().isEmpty())
    {
        emit signal_sendMSG(ui->LWCustomList->currentItem()->text(),ui->LEInputText->text());
        text=new QListWidgetItem(ui->LEInputText->text());
        text->setTextAlignment(Qt::AlignRight);
        ChatMatch[ui->LWCustomList->currentItem()->text()]->addItem(text);

        ui->LEInputText->clear();
    }
}

