#include "customerclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomerClient w;
    w.show();
    return a.exec();
}
