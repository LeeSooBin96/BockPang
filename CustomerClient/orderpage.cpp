#include "orderpage.h"
#include "ui_orderpage.h"

OrderPage::OrderPage(QWidget *parent,QString *code)
    : QWidget(parent)
    , ui(new Ui::OrderPage)
{
    myCode=*code; //번호만 저장함
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    //확인용
    // QString list=QString("S@1@청년피자-송정어룡점@할라불고기, 진짜감자피자,토핑농장@1200");
    // PrintMenuInfo(list.split('@'));
}

OrderPage::~OrderPage()
{
    delete ui;
}
//서버에 검색어 전송
void OrderPage::SendSearchKey()
{
    if(!ui->Search_Edit->text().isEmpty())
    {
        QString keyword=ui->Search_Edit->text(); //검색창에 입력된 키워드
        QByteArray msg="S"+myCode.toUtf8()+"^"+keyword.toUtf8();
        emit signal_sendMSG(msg);

        ui->Search_Edit_2->setText(keyword);
        ui->Search_Edit->clear();
        ui->stackedWidget->setCurrentIndex(1);
        ui->listWidget->clear();
        mNumlist.clear();
    }
}
//검색 결과 출력
void OrderPage::PrintResultSearch(QStringList slist)
{
    //받아온 데이터 : S@(가게번호)@(해당하는 가게이름)@(대표메뉴)@(배달팁)
    mNumlist.push_back(slist[1].toInt());
    //가게 이름, 대표 메뉴, 배달팁 출력
    QListWidgetItem* item= new QListWidgetItem;
    item->setIcon(QIcon(":/resources/"+slist[1]+"_board.png"));

    item->setText(slist[2]+"\n"+slist[3]+"\n"+"배달팁: "+slist[4]+"원");
    item->setTextAlignment(Qt::AlignLeft);
    item->setTextAlignment(Qt::AlignVCenter);
    ui->listWidget->addItem(item);
    ui->listWidget->setIconSize(QSize(100,100));
    emit signal_sendMSG("y");
}
//카테고리 번호 전송
void OrderPage::SendCateNum()
{
    QString cate=sender()->objectName().split('_')[2];
    QByteArray msg="T"+myCode.toUtf8()+"^"+cate.toUtf8();
    emit signal_sendMSG(msg);

    ui->stackedWidget->setCurrentIndex(2);
    switch (cate.toInt()) {
    case 1:
        ui->lb_Categoryname->setText("카테고리-피자");
        break;
    case 2:
        ui->lb_Categoryname->setText("카테고리-치킨");
        break;
    case 3:
        ui->lb_Categoryname->setText("카테고리-패스트푸드");
        break;
    case 4:
        ui->lb_Categoryname->setText("카테고리-족발/보쌈");
        break;
    default:
        break;
    }
    ui->listWidget_2->clear();
    mNumlist.clear();
}
//카테고리 목록 출력
void OrderPage::PrintSelectedCate(QStringList clist)
{
    mNumlist.push_back(clist[1].toInt());
    QListWidgetItem* item= new QListWidgetItem;
    item->setIcon(QIcon(":/resources/"+clist[1]+"_board.png"));

    item->setText(clist[2]+"\n"+clist[3]+"\n"+"배달팁: "+clist[4]+"원");
    item->setTextAlignment(Qt::AlignLeft);
    item->setTextAlignment(Qt::AlignVCenter);
    ui->listWidget_2->addItem(item);
    ui->listWidget_2->setIconSize(QSize(100,100));
    emit signal_sendMSG("y");
}
//서버에 가게 번호 전송
void OrderPage::SendMarcketNum(const QModelIndex &index)
{
    selectedmNum=mNumlist[index.row()];
    QByteArray msg="M"+myCode.toUtf8()+"^"+QString::number(selectedmNum).toUtf8();
    emit signal_sendMSG(msg);

    expageNum=ui->stackedWidget->currentIndex(); //이전으로 기능을 위해 인덱스 저장
    ui->stackedWidget->setCurrentIndex(3);
    ui->tabWidget->setCurrentIndex(0);
    ui->lblBoarderIMG->setPixmap(QPixmap(":/resources/"+QString::number(selectedmNum)+"_board.png"));
}

//가게 정보 출력
void OrderPage::PrintMarcketBase(QStringList mlist)
{
    ui->lblMTitle->setText(mlist[1]);
    ui->lblOTime->setText(mlist[2]);
    ui->lblMinOrder->setText(mlist[3]);
    ui->lblDTip->setText(mlist[4]+"원");

    //기존에 있던것 삭제
    for(int i=ui->toolBMenuCate->count();i>0;i--)
    {
        ui->toolBMenuCate->removeItem(i);
    }
    menuLWlist.clear();

    //메뉴 카테고리 툴박스 생성
    ui->toolBMenuCate->setItemText(0,mlist[6]);
    menuLWlist.push_back(ui->LWmenuCate_1);
    for(int i=1;i<mlist[5].toInt();i++)
    {
        QListWidget* lw=new QListWidget(this);
        lw->setObjectName("LWmenuCate_"+QString::number(i));
        lw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->toolBMenuCate->insertItem(i,lw,mlist[6+i]);
        menuLWlist.push_back(lw);

        //리스트위젯 커넥션 연결해야함 -- 메뉴 클릭했을때

    }
    ui->toolBMenuCate->setCurrentIndex(0);
}
//메뉴 카테고리 선택시
void OrderPage::SendMenuCateNum(int index)
{
    QByteArray msg="M"+myCode.toUtf8()+"^C^"+QString::number(selectedmNum).toUtf8()+"^"+QString::number(index+1).toUtf8();
    emit signal_sendMSG(msg);

    selectedmcNum=index;
    menuLWlist[index]->clear();
}
//메뉴 리스트 출력
void OrderPage::PrintMenuList(QStringList mlist)
{
    //오는 데이터 순서: 메뉴번호+메뉴이름+메뉴소개+메뉴가격
    for(int i=0;i<mlist[1].toInt()*4;i+=4)
    {
        QListWidgetItem* item= new QListWidgetItem;
        item->setIcon(QIcon(":/resources/"+QString::number(selectedmNum)+"_menu"+mlist[2+i]+".png"));

        item->setText(mlist[3+i]+"\n"+mlist[4+i]+"\n"+mlist[5+i]+"원");
        item->setTextAlignment(Qt::AlignLeft);
        item->setTextAlignment(Qt::AlignVCenter);
        menuLWlist[selectedmcNum-1]->addItem(item);
        menuLWlist[selectedmcNum-1]->setIconSize(QSize(100,100));
    }
}

//화면 이동
void OrderPage::gotoHome() //홈화면으로
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->Search_Edit->clear();
}
void OrderPage::gotoExPage() //이전화면으로
{
    ui->stackedWidget->setCurrentIndex(expageNum);
}



