#include "marcketmain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MarcketMain w;
    w.show();
    return a.exec();
}
