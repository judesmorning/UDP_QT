#ifndef MAKEPACKET_H
#define MAKEPACKET_H

#include <QDialog>
#include "includes.h"
#include "mymethod.h"

namespace Ui {
class MakePacket;
}

class MakePacket : public QDialog
{
    Q_OBJECT

public:
    explicit MakePacket(QWidget *parent = 0);
    ~MakePacket();

private slots:
    void on_checkBox_clicked(bool checked);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MakePacket *ui;
signals:
    void getUdpFramSignal(const UDP_SEND_FRAME_STRUCT&);
};

#endif // MAKEPACKET_H
