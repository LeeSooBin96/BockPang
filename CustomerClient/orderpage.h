#ifndef ORDERPAGE_H //주문 페이지 - 어플 메인 화면
#define ORDERPAGE_H

#include <QWidget>
#include <QTimer>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QButtonGroup>
#include <QVBoxLayout>


//주문 정보 저장할 구조체 만들자
struct OrderedMenu{
    qint64 marketNum; //가게 번호
    QVector<qint64> menuNum; //메뉴번호 저장
    QVector<QString> menu; //메뉴 이름
    QMap<QString,qint64> price;  //가격
    QMap<QString,QStringList> option; //메뉴별 옵션 내용
};

namespace Ui {
class OrderPage;
}

class OrderPage : public QWidget
{
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr,QString* code = nullptr); //생성될때 코드 받아와야함
    ~OrderPage();

    //서버에서 사용
    void PrintResultSearch(QStringList); //검색 결과 출력
    void PrintSelectedCate(QStringList); //카테고리에 해당하는 목록 출력
    void PrintMarcketBase(QStringList); //가게 정보 출력
    void PrintMenuList(QStringList); //메뉴 리스트 출력
    void PrintMarcketInfo(QStringList); //매장 상세정보 출력
    void PrintMenuOPtion(QStringList); //메뉴 옵션 내용 출력

    void ArriveResultOrder(QString); //주문 결과 수신
    void ArriveOrderProgress(QStringList); //주문 진행 사항 수신
    void ArriveQuestionAnswer(QString); //고객 센터 응답 수신

signals:
    void signal_sendMSG(QByteArray);

private:
    Ui::OrderPage *ui;
    QString myCode; //서버와 통신시 사용할 코드 ( 요청코드+클라이언트번호 )
    QVector<int> mNumlist; //목록에 있는 가게번호 저장
    QVector<QString> mStatelist; //목록에 있는 가게 오픈상태 저장
    QVector<int> settedCateNum; //요청된 카테고리 번호 배열 -- 중복 요청 방지
    QList<QListWidget*> menuLWlist; //메뉴 리스트위젯 모음
    quint64 selectedmNum,selectedmcNum; //선택된 가게 번호,메뉴 카테고리번호 저장
    QList<quint64> expageNum; //이전 페이지 인덱스 저장 - 이전 화면으로 돌아갈때 사용
    OrderedMenu* shopCart; //장바구니(주문정보)
    QMap<QString,QString> opName; //옵션 라디오버튼 - 이름 연결
    QMap<QString,qint64> opPrice; //옵션 라디오버튼-가격 연결

    QList<QGroupBox*> opBoxlist; //옵션 그룹박스 리스트--삭제 해야해...

private slots:
    void SendSearchKey(); //서버에 검색어 전송
    void SendCateNum(); //서버에 카테고리 번호 전송
    void SendMarcketNum(const QModelIndex &index); //서버에 가게 번호 전송
    void SendMenuCateNum(int index); //서버에 메뉴카테고리 번호 전송
    void SendMenuNum(QListWidgetItem *item); //서버에 선택된 메뉴 번호 전송
    void SendMarcketNumforDetail(int index); //서버에 가게 상세 정보 요청
    void radioButtonToggled(bool checked); //옵션 라디오 버튼 건드릴때
    void AddtoShopCart(); //장바구니 담기 선택 시
    void SendOderInfo(); //서버에 주문정보 전송


    void SendQuestion(); //고객센터에 문의 송신

    //화면 이동
    void gotoHome(); //홈화면으로 이동
    void gotoExPage(); //이전 화면으로 이동
    void gotoQuestionPage(); //고객 문의 창으로 이동
    void gotoNotice(); //알림 목록 창으로
    void gotoShopCart(); //장바구니 화면으로 이동

};

#endif // ORDERPAGE_H
