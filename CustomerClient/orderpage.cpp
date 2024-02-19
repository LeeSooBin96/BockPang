#include "orderpage.h"
#include "ui_orderpage.h"

OrderPage::OrderPage(QWidget *parent,QString *code)
    : QWidget(parent)
    , ui(new Ui::OrderPage)
{
    myCode=*code; //번호만 저장함
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->redPoint->hide();
    ui->TWShoplist->setColumnWidth(0,20);
    ui->TWShoplist->setColumnWidth(1,30);
    ui->TWShoplist->setColumnWidth(2,150);
    ui->TWShoplist->setColumnWidth(3,60);
    ui->TWShoplist->setColumnWidth(4,30);



    //확인용
    // selectedmNum=1;
    // QString list=QString("코드@가게이름@운영시간@최소주문@배달팁@2@카테고리1@카테고리2");
    // PrintMarcketBase(list.split('@'));
    // QString list2=QString("코드@2@1@메뉴1@메뉴소개1@메뉴가격1@2@메뉴2@메뉴소개2@메뉴가격2");
    // PrintMenuList(list2.split('@'));
    // ui->stackedWidget->setCurrentIndex(3);
    // emit ui->toolBMenuCate->currentChanged(0);
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
        mStatelist.clear();
    }
}
//검색 결과 출력
void OrderPage::PrintResultSearch(QStringList slist)
{
    //받아온 데이터 : S@(가게번호)@(해당하는 가게이름)@(대표메뉴)@(배달팁)
    mStatelist.push_back(slist[5]); //가게 오픈 상태 저장
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
    mStatelist.clear();
}
//카테고리 목록 출력
void OrderPage::PrintSelectedCate(QStringList clist)
{
    mStatelist.push_back(clist[5]); //가게 오픈상태 저장
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
    if(mStatelist[index.row()]=="F") //가게 오픈 상태 검사
    {
        QMessageBox::information(this,"알림","매장 오픈 준비중입니다.",QMessageBox::Ok);
    }
    else
    {
        selectedmNum=mNumlist[index.row()];
        QByteArray msg="M"+myCode.toUtf8()+"^"+QString::number(selectedmNum).toUtf8();
        emit signal_sendMSG(msg);

        expageNum.append(ui->stackedWidget->currentIndex()); //이전으로 기능을 위해 인덱스 저장
        ui->stackedWidget->setCurrentIndex(3);
        ui->tabWidget->setCurrentIndex(0);
        ui->lblBoarderIMG->setPixmap(QPixmap(":/resources/"+QString::number(selectedmNum)+"_board.png"));
    }
}

//가게 정보 출력
void OrderPage::PrintMarcketBase(QStringList mlist)
{
    // "코드@가게이름@운영시간@최소주문@배달팁@2@카테고리1@카테고리2"
    ui->lblMTitle->setText(mlist[1]);
    ui->lblOTime->setText(mlist[2]);
    ui->lblOTime_2->setText(mlist[2]);
    ui->lblMinOrder->setText(mlist[3]);
    ui->lblMinOrder_2->setText(mlist[3]);
    ui->lblDTip->setText(mlist[4]+"원");
    ui->lblDTip_2->setText(mlist[4]+"원");

    //기존에 있던것 삭제
    for(int i=ui->toolBMenuCate->count();i>0;i--)
    {
        ui->toolBMenuCate->removeItem(i);
    }
    menuLWlist.clear();

    //메뉴 카테고리 툴박스 생성
    ui->toolBMenuCate->setItemText(0,mlist[6]);
    menuLWlist.push_back(ui->LWmenuCate_1);
    connect(ui->LWmenuCate_1,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(SendMenuNum(QListWidgetItem*)));
    for(int i=1;i<mlist[5].toInt();i++)
    {
        QListWidget* lw=new QListWidget(this);
        lw->setObjectName("LWmenuCate_"+QString::number(i+1)); //모두 해결 완료
        lw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->toolBMenuCate->insertItem(i,lw,mlist[6+i]);
        menuLWlist.push_back(lw);

        //리스트위젯 커넥션 연결해야함 -- 메뉴 클릭했을때
        connect(lw,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(SendMenuNum(QListWidgetItem*)));
    }
    for(int i=0;i<menuLWlist.size();i++)
    {
        qDebug()<<menuLWlist[i]->objectName(); //확인용 //잘들어가라
    }
    settedCateNum.clear();
    emit ui->toolBMenuCate->currentChanged(0);
}
//메뉴 카테고리 선택시
void OrderPage::SendMenuCateNum(int index)
{
    if(settedCateNum.indexOf(index)<0) //없으면 -1
    {
        QByteArray msg="M"+myCode.toUtf8()+"^C^"+QString::number(selectedmNum).toUtf8()+"^"+QString::number(index+1).toUtf8();
        emit signal_sendMSG(msg);

        settedCateNum.append(index);
        selectedmcNum=index;
        menuLWlist[index]->clear();
    }
}
//메뉴 리스트 출력
void OrderPage::PrintMenuList(QStringList mlist)
{
    // for(QString m: mlist) qDebug()<<m;
    // "코드@2@1@메뉴1@메뉴소개1@메뉴가격1@메뉴2@메뉴소개2@메뉴가격2"
    //오는 데이터 순서: 코드+메뉴개수+메뉴번호+메뉴이름+메뉴소개+메뉴가격
    for(int i=0;i<mlist[1].toInt()*4&&mlist.size()-2==mlist[1].toInt()*4;i+=4) //잘돌아감 확인함 --오는 메시지가 너무 크면 잘려서 와서 오류 난것 어떻게 해결할까
    {
        // qDebug()<<mlist[i+2]<<mlist[i+3]<<mlist[i+4]<<mlist[i+5];
        QListWidgetItem* item= new QListWidgetItem;
        item->setWhatsThis("menu_"+mlist[2+i]);
        item->setIcon(QIcon(":/resources/"+QString::number(selectedmNum)+"_menu"+mlist[2+i]+".png"));
        if(mlist[4+i]=="0") mlist[4+i]="";
        item->setText(mlist[3+i]+"\n"+mlist[4+i]+"\n"+mlist[5+i]+"원");
        item->setTextAlignment(Qt::AlignLeft);
        item->setTextAlignment(Qt::AlignVCenter);
        menuLWlist[selectedmcNum]->addItem(item);
        // qDebug()<<menuLWlist[selectedmcNum]->objectName();
        // qDebug()<<item->whatsThis(); //오브젝트네임은 없지만 이걸로 구분해보자
    }
    menuLWlist[selectedmcNum]->setIconSize(QSize(100,100));
}
//서버에 선택한 메뉴 번호 전송
void OrderPage::SendMenuNum(QListWidgetItem *item)
{
    if(ui->TWShoplist->rowCount()!=0&&shopCart->marketNum!=selectedmNum)
    {
        QMessageBox::critical(this,"경고","장바구니에 있는 다른 매장의 메뉴를 삭제하고 와주세요.",QMessageBox::Ok);
        return;
    }
    qDebug()<<item->whatsThis(); //menu_메뉴번호

    QByteArray msg="M"+myCode.toUtf8()+"^N^"+item->whatsThis().split('_')[1].toUtf8();
    emit signal_sendMSG(msg);

    expageNum.append(3);
    ui->stackedWidget->setCurrentIndex(4);

    //메뉴 사진, 이름, 소개, 가격 배치
    ui->lblOPmenuIMG->setStyleSheet("border-image: url(:/resources/"+QString::number(selectedmNum)+"_menu"+item->whatsThis().split('_')[1]+".png);");
    ui->lblOPmenuName->setText(item->text().split('\n')[0]);
    ui->lblOPmenuIntro->setText(item->text().split('\n')[1]);
    ui->lblOPmenuPrice->setText(item->text().split('\n')[2]);
    ui->lblSelectedPrice->setText(item->text().split('\n')[2]);
    //이때 가게번호, 메뉴 이름, 가격 저장하기
    shopCart=new OrderedMenu;
    shopCart->marketNum=selectedmNum;
    shopCart->menuNum.append(item->whatsThis().split('_')[1].toInt());
    shopCart->menu.append(item->text().split('\n')[0]);
    shopCart->price[item->text().split('\n')[0]]=(item->text().split('\n')[2].remove("원")).toInt();
    //기존의 정보들 삭제
    opName.clear(); opPrice.clear();
    // qDebug()<<shopCart->marketNum<<shopCart->menu[0]<<shopCart->price[shopCart->menu[0]];
}
//메뉴 옵션 내용 출력
void OrderPage::PrintMenuOPtion(QStringList oplist)
{
    //기존 옵션 리스트 삭제해야함
    // ui->OPVlayout.dele
    // ui->OPVlayout->itemAt(int) //
    if(opBoxlist.size()!=0) //테스트 못해봄 안되면 삭제하자 -됨 안됨 모르겠다
    {
        for(int i=0;i<opBoxlist.size();i++)
        {
            // qDebug()<<i;
            // opBoxlist[i]->deleteLater();
            ui->OPVlayout->removeWidget(opBoxlist[i]);
            delete opBoxlist[i];
        }
        opBoxlist.clear();
    }
    // qDebug()<<oplist.size();
    int index=2;
    qint64 opNum=1;
    while(true)
    {
        if(index>oplist.size()) break; //숫자가 아니면
        // qDebug()<<oplist[index-1].toInt();
        QGroupBox* gbox=new QGroupBox(this);
        gbox->setTitle(oplist[index]);
        // if(oplist[index].contains("가능"))
        QVBoxLayout* vlay=new QVBoxLayout;
        QButtonGroup* group=new QButtonGroup(this);
        for(int i=0;i<oplist[index-1].toInt()*2;i+=2)
        {

            QRadioButton* rbtn=new QRadioButton(this);
            rbtn->setObjectName("op_"+QString::number(opNum));
            // rbtn->setWhatsThis(oplist[index+2+i]);
            // qDebug()<<rbtn->objectName();
            rbtn->setText(oplist[index+2+i]);
            group->addButton(rbtn);
            QLabel* lbl=new QLabel(this);
            lbl->setText("+"+oplist[index+3+i]+"원");
            lbl->setStyleSheet("color: rgb(162, 162, 162);");
            //라디오버튼 - 라벨 매핑해야함

            opName[rbtn->objectName()]=oplist[index+2+i];
            opPrice[rbtn->objectName()]=oplist[index+3+i].toInt();

            QHBoxLayout* hlay=new QHBoxLayout;
            hlay->addWidget(rbtn,8);
            hlay->addWidget(lbl,2);
            vlay->addLayout(hlay);
            opNum++;

            //라디오 버튼에 슬롯 연결해야함 (선택될때/ 해제될때)
            connect(rbtn,SIGNAL(toggled(bool)),this,SLOT(radioButtonToggled(bool)));
        }
        gbox->setLayout(vlay);
        ui->OPVlayout->addWidget(gbox);
        opBoxlist.append(gbox);
        if(oplist[index].contains("가능")) group->setExclusive(false);
        else group->setExclusive(true);

        index=index+(oplist[index-1].toInt()+1)*2+1;
        // qDebug()<<index;
    }
    //그룹박스 만들어서 라디오버튼 추가해야함
    // ui->OPVlayout->setStretch(0,10);

}
//옵션 라디오 버튼 체크시 (체크 true / 해제 false )
void OrderPage::radioButtonToggled(bool checked)
{
    if(checked) //선택됨
    {
        //옵션 이름, 가격 업데이트
        shopCart->option[ui->lblOPmenuName->text()].append(opName[sender()->objectName()]); //옵션 이름 추가
        shopCart->price[ui->lblOPmenuName->text()]+=opPrice[sender()->objectName()]; //가격 더하기
    }
    else //해제됨
    {
        shopCart->option[ui->lblOPmenuName->text()].pop_back(); //옵션 이름 빼기
        shopCart->price[ui->lblOPmenuName->text()]-=opPrice[sender()->objectName()]; //가격 빼기
    }
    ui->lblSelectedPrice->setText(QString::number(shopCart->price[ui->lblOPmenuName->text()])+"원");
    // for(QString l: shopCart->option[ui->lblOPmenuName->text()]) qDebug()<<l;
    // qDebug()<<shopCart->price[ui->lblOPmenuName->text()]<<"원";
}
//장바구니 담기 선택시
void OrderPage::AddtoShopCart()
{
    qDebug()<<shopCart->marketNum;
    qDebug()<<shopCart->menuNum.last()<<shopCart->menu.last();
    qDebug()<<shopCart->option[shopCart->menu.last()];
    qDebug()<<shopCart->price[shopCart->menu.last()];

    int rowNum=ui->TWShoplist->rowCount();
    ui->TWShoplist->insertRow(rowNum);
    //메뉴 개수 넘버링
    QTableWidgetItem* item=new QTableWidgetItem(QString::number(rowNum+1));
    // item->setText(QString::number(rowNum+1));
    ui->TWShoplist->setItem(rowNum,0,item);
    //메뉴 이미지
    item=new QTableWidgetItem;
    item->setIcon(QIcon(":/resources/"+QString::number(shopCart->marketNum)+"_menu"+QString::number(shopCart->menuNum.last())+".png"));
    ui->TWShoplist->setItem(rowNum,1,item);
    //메뉴명
    item=new QTableWidgetItem(shopCart->menu.last()+"(");
    for(int i=0;i<shopCart->option[shopCart->menu.last()].size();i++)
    {
        item->setText(item->text().append(shopCart->option[shopCart->menu.last()][i]));
    }
    item->setText(item->text().append(")"));
    item->setToolTip(item->text());
    ui->TWShoplist->setItem(rowNum,2,item);
    //메뉴 가격
    item=new QTableWidgetItem(QString::number(shopCart->price[shopCart->menu.last()]));
    ui->TWShoplist->setItem(rowNum,3,item);
    //삭제 버튼
    item=new QTableWidgetItem;
    QPushButton* del=new QPushButton(this);
    del->setText("삭제");
    item->setSelected(true);
    ui->TWShoplist->setCellWidget(rowNum,4,del);

    quint64 tprice=0;
    for(int i=0;i<ui->TWShoplist->rowCount();i++)
    {
        tprice+=ui->TWShoplist->item(i,3)->text().toUInt();
    }
    ui->lblTotalPrice->setText(QString::number(tprice)+"원");

    QMessageBox::information(this,"알림","메뉴가 담겼습니다. 이전화면으로 돌아갑니다.",QMessageBox::Ok);
    gotoExPage();
}
//서버에 주문정보 전송
void OrderPage::SendOderInfo()
{
    //P1^고객닉네임^매장번호^메뉴개수^메뉴이름(옵션내용)/메뉴이름(옵션내용)/...^총가격^결제수단
    QByteArray msg="P^"+QString::number(shopCart->marketNum).toUtf8()+"^"+QString::number(ui->TWShoplist->rowCount()).toUtf8()+"^";
    for(int i=0;i<ui->TWShoplist->rowCount()-1;i++)
    {
        msg.append(ui->TWShoplist->item(i,2)->text().toUtf8()+"/");
    }msg.append(ui->TWShoplist->item(ui->TWShoplist->rowCount()-1,2)->text().toUtf8()+"^"+ui->lblTotalPrice->text().remove("원").toUtf8()+"^"+ui->ComboBoxPayWay->currentText().toUtf8());
    emit signal_sendMSG(msg);

    QMessageBox::information(this,"알림","주문이 접수되었습니다. 이전화면으로 돌아갑니다.",QMessageBox::Ok);
    gotoExPage();
}
//서버에 가게 상세정보 요청
void OrderPage::SendMarcketNumforDetail(int index)
{
    if(index==1&&ui->lblCnum->text()=="TextLabel") //요청된 데이터 중복요청 방지
    {
        QByteArray msg="M"+myCode.toUtf8()+"^D^"+QString::number(selectedmNum).toUtf8();
        emit signal_sendMSG(msg);
    }
    else //0일때
    {
        ui->toolBMenuCate->setCurrentIndex(0);
    }
}
//매장 상세 정보 출력
void OrderPage::PrintMarcketInfo(QStringList ilist)
{
    for(QString l:ilist) if(l=="0") l.clear();
    ui->lblItroduce->setText(ilist[1]);
    ui->lblTel->setText(ilist[2]);
    ui->lblPayWay->setText(ilist[3]);
    ui->lblCEO->setText(ilist[4]);
    ui->lblBrand->setText(ilist[5]);
    ui->lblCnum->setText(ilist[6]);
    ui->lblOrigin->setText(ilist[7]);
}
//고객센터 응답 수신
void OrderPage::ArriveQuestionAnswer(QString msg)
{
    QListWidgetItem* item=new QListWidgetItem(msg);
    item->setTextAlignment(Qt::AlignLeft);
    ui->LWQuestion->addItem(item);

    if(ui->stackedWidget->currentIndex()!=5)
    {
        //알림 기능 추가
        QLabel* lbl = new QLabel(this);
        lbl->setText("🔔 알림이 도착했습니다.");
        lbl->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        lbl->setStyleSheet("color:blue;font:700 15pt;border-radius:15px;background-color: rgba(255, 255, 255,0.8);");
        lbl->setGeometry(0,0,375,50);
        lbl->show();
        QTimer* timer=new QTimer(this);
        timer->start(3000);
        connect(timer,SIGNAL(timeout()),lbl,SLOT(hide()));

        item=new QListWidgetItem("고객센터로부터 메시지가 도착했습니다.\n고객센터 :"+msg);
        ui->LWNoticelist->addItem(item);
        ui->redPoint->show();
    }
}
//고객센터 문의 송신
void OrderPage::SendQuestion()
{
    if(!ui->LEInputMSG->text().isEmpty())
    {
        QListWidgetItem* item=new QListWidgetItem(ui->LEInputMSG->text());
        item->setTextAlignment(Qt::AlignRight);
        ui->LWQuestion->addItem(item);
        emit signal_sendMSG("Q"+myCode.toUtf8()+"^Q^"+ui->LEInputMSG->text().toUtf8());

        ui->LEInputMSG->clear();
    }
}
//주문 결과 송신
void OrderPage::ArriveResultOrder(QString ok)
{
    QString msg;
    if(ok=="F") //주문 취소 당함
    {
        msg="가게 측에서 주문을 거절하였습니다. \n기타 문의사항은 고객센터로 부탁드립니다.";
        qDebug()<<"주문 취소 당함";
    }
    else //주문 승낙
    {
        msg="주문이 접수되었습니다. \n주문번호 :"+ok;
        qDebug()<<"주문 승낙 주문번호: "<<ok;
    }
    QLabel* lbl = new QLabel(this);
    lbl->setText("🔔 알림이 도착했습니다.");
    lbl->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    lbl->setStyleSheet("color:blue;font:700 15pt;border-radius:15px;background-color: rgba(255, 255, 255,0.8);");
    lbl->setGeometry(0,0,375,50);
    lbl->show();
    QTimer* timer=new QTimer(this);
    timer->start(3000);
    connect(timer,SIGNAL(timeout()),lbl,SLOT(hide()));

    QListWidgetItem* item=new QListWidgetItem("서버로부터 메시지가 도착했습니다.\n주문결과 :"+msg);
    ui->LWNoticelist->addItem(item);
    ui->redPoint->show();
}
//주문 진행 사항 수신
void OrderPage::ArriveOrderProgress(QStringList plist)
{
    QString msg="주문번호 : ";
    if(plist[1]=="D")
    {
        msg.append(plist[2] +" 의 배달이 완료되었습니다.");
    }
    else
    {
        msg.append(plist[1] +" 의 조리가 완료되었습니다.");
    }
    QLabel* lbl = new QLabel(this);
    lbl->setText("🔔 알림이 도착했습니다.");
    lbl->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    lbl->setStyleSheet("color:blue;font:700 15pt;border-radius:15px;background-color: rgba(255, 255, 255,0.8);");
    lbl->setGeometry(0,0,375,50);
    lbl->show();
    QTimer* timer=new QTimer(this);
    timer->start(3000);
    connect(timer,SIGNAL(timeout()),lbl,SLOT(hide()));

    QListWidgetItem* item=new QListWidgetItem("서버로부터 메시지가 도착했습니다.\n진행사항 :"+msg);
    ui->LWNoticelist->addItem(item);
    ui->redPoint->show();
}

//화면 이동
void OrderPage::gotoHome() //홈화면으로
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->Search_Edit->clear();
    expageNum.clear();
}
void OrderPage::gotoExPage() //이전화면으로
{
    //옵션 선택창일때
    if(ui->TWShoplist->rowCount()!=shopCart->menu.size()&&ui->stackedWidget->currentIndex()==4)
    {
        shopCart->price[shopCart->menu.last()]=0;
        shopCart->option[shopCart->menu.last()].clear();
        shopCart->menu.pop_back();
    }
    ui->stackedWidget->setCurrentIndex(expageNum.last());
    expageNum.pop_back();


    // for(quint64 i: expageNum) qDebug()<<i;
}
void OrderPage::gotoQuestionPage() //고객 문의 창으로
{
    ui->stackedWidget->setCurrentIndex(5);
    QListWidgetItem* item=new QListWidgetItem("센터에 접속중입니다...기다려주세요");
    item->setTextAlignment(Qt::AlignLeft);
    ui->LWQuestion->addItem(item);
    emit signal_sendMSG("Q"+myCode.toUtf8()+"^");
}
void OrderPage::gotoNotice() //알림 목록 창으로
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->redPoint->hide();
}
void OrderPage::gotoShopCart() //장바구니 화면으로
{
    expageNum.append(ui->stackedWidget->currentIndex());   //이전 페이지 정보 저장
    ui->stackedWidget->setCurrentIndex(7);
}














