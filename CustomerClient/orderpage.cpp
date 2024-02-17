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

    expageNum.append(ui->stackedWidget->currentIndex()); //이전으로 기능을 위해 인덱스 저장
    ui->stackedWidget->setCurrentIndex(3);
    ui->tabWidget->setCurrentIndex(0);
    ui->lblBoarderIMG->setPixmap(QPixmap(":/resources/"+QString::number(selectedmNum)+"_board.png"));
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
}
//메뉴 옵션 내용 출력
void OrderPage::PrintMenuOPtion(QStringList oplist)
{
    qDebug()<<oplist.size();
    int index=2;
    static qint64 opNum=1;
    while(true)
    {
        if(index>oplist.size()) break; //숫자가 아니면
        qDebug()<<oplist[index-1].toInt();
        QGroupBox* gbox=new QGroupBox(this);
        gbox->setTitle(oplist[index]);
        QVBoxLayout* vlay=new QVBoxLayout;
        for(int i=0;i<oplist[index-1].toInt()*2;i+=2)
        {
            QRadioButton* rbtn=new QRadioButton(this);
            rbtn->setObjectName("op_"+QString::number(opNum));
            qDebug()<<rbtn->objectName();
            rbtn->setText(oplist[index+2+i]);
            QLabel* lbl=new QLabel(this);
            lbl->setText("+"+oplist[index+3+i]+"원");
            lbl->setStyleSheet("color: rgb(162, 162, 162);");
            QHBoxLayout* hlay=new QHBoxLayout;
            hlay->addWidget(rbtn,8);
            hlay->addWidget(lbl,2);
            vlay->addLayout(hlay);
            opNum++;
        }
        gbox->setLayout(vlay);
        ui->OPVlayout->addWidget(gbox);

        index=index+(oplist[index-1].toInt()+1)*2+1;
        qDebug()<<index;
    }
    //그룹박스 만들어서 라디오버튼 추가해야함
    // ui->OPVlayout->setStretch(0,10);
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
    for(QString l:ilist) if(l=="0") l="";
    ui->lblItroduce->setText(ilist[1]);
    ui->lblTel->setText(ilist[2]);
    ui->lblPayWay->setText(ilist[3]);
    ui->lblCEO->setText(ilist[4]);
    ui->lblBrand->setText(ilist[5]);
    ui->lblCnum->setText(ilist[6]);
    ui->lblOrigin->setText(ilist[7]);
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
    ui->stackedWidget->setCurrentIndex(expageNum.last());
    expageNum.pop_back();
    for(quint64 i: expageNum) qDebug()<<i;
}
void OrderPage::gotoQuestionPage() //고객 문의 창으로
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->TEQuestion->setText("센터에 접속중입니다...기다려주세요");
    emit signal_sendMSG("Q"+myCode.toUtf8()+"@");
}








