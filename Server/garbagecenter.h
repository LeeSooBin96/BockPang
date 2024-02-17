#ifndef GARBAGECENTER_H
#define GARBAGECENTER_H

#include <QDialog>

namespace Ui {
class GarbageCenter;
}

class GarbageCenter : public QDialog
{
    Q_OBJECT

public:
    explicit GarbageCenter(QWidget *parent = nullptr,QString *nick=nullptr);
    ~GarbageCenter();

private:
    Ui::GarbageCenter *ui;
};

#endif // GARBAGECENTER_H
