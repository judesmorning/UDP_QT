#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "includes.h"
#include "parse.h"
#include "myudp.h"
#include "makepacket.h"
#include "mytimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private:
    Myudp udp;
    Parse parse;
    QThread udpThread,parseThread;
    MakePacket mp;
    std::vector<MyTimer*> timerVc;
private:
    int init();//初始化函数

private slots:

void workResultSlot(const QString&);
void getUdpFramSlot(const UDP_SEND_FRAME_STRUCT&);
void sendedSlot(const QString&);
void on_comboBox_3_currentIndexChanged(int index);

void on_pushButton_11_clicked();

void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_pushButton_3_clicked();

void on_pushButton_4_clicked();

void on_pushButton_5_clicked();

signals:
    void initUdpSignal();
};


#endif // MAINWINDOW_H
