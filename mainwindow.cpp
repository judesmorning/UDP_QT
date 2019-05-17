#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    (void)this->init();
}

MainWindow::~MainWindow()
{
    udpThread.quit();
    parseThread.quit();
    delete ui;
}

/***********************************************/
// z 函数名称:初始化函数
// h 函数作用:NULL
// u 函数参数:NULL
// x 函数返回值:NULL
// y 备注:NULL
/***********************************************/
int MainWindow::init()
{
    int ret = RET_OK;
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//选中一行
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

    QObject::connect(this,SIGNAL(initUdpSignal()),&udp,SLOT(initUdpSlot()));
    QObject::connect(&udp,SIGNAL(rcvdDataSignal(QByteArray)),&parse,SLOT(recvdDataSlot(QByteArray)));
    QObject::connect(&parse,SIGNAL(workResultSignal(QString)),this,SLOT(workResultSlot(QString)));
    QObject::connect(&mp,SIGNAL(getUdpFramSignal(UDP_SEND_FRAME_STRUCT)),this,SLOT(getUdpFramSlot(UDP_SEND_FRAME_STRUCT)));
    QObject::connect(&udp,SIGNAL(sendedSignal(QString)),this,SLOT(sendedSlot(QString)));
    qRegisterMetaType<UDP_SEND_FRAME_STRUCT>("UDP_SEND_FRAME_STRUCT");//注册结构体
    emit initUdpSignal();
    this->showMaximized();
    return ret;
}

/**
 *函数名:显示解析结果
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::workResultSlot(const QString &info)
{
    if(ui->checkBox_4->isChecked())
    {
        ui->plainTextEdit_2->appendPlainText(info);
    }
}

/**
 *函数名:添加帧
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::getUdpFramSlot(const UDP_SEND_FRAME_STRUCT &frame)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(frame.type));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(frame.time));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(frame.data));
}

/**
 *函数名:发送成功
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::sendedSlot(const QString &info)
{
    if(ui->checkBox->isChecked())
    {
        ui->plainTextEdit->appendPlainText(info);
    }
}

/**
 *函数名:设置解析类型
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    parse.setPacket(index+1);
}

/**
 *函数名:清空
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::on_pushButton_11_clicked()
{
    ui->plainTextEdit_2->setPlainText("");
}

/**
 *函数名:添加帧
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::on_pushButton_clicked()
{
    mp.exec();
}

/**
 *函数名:删除帧
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

/**
 *函数名:开始发送
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::on_pushButton_3_clicked()
{
    if(timerVc.size()!=0)
    {
        QMessageBox::warning(this,"错误","请先停止发送");
        return;
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        timerVc.push_back(new MyTimer());
        timerVc[i]->setInterval(ui->tableWidget->item(i,1)->text().toInt());
        timerVc[i]->setData(ui->tableWidget->item(i,2)->text());
        QObject::connect(timerVc[i],SIGNAL(sendSignal(QByteArray)),&udp,SLOT(sendSlot(QByteArray)));
        timerVc[i]->start();
    }
}

/**
 *函数名:停止发送
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::on_pushButton_4_clicked()
{
    for(int i=0;i<(int)timerVc.size();i++)
    {
        timerVc[i]->stop();
        delete timerVc[i];
    }
    std::vector<MyTimer*>().swap(timerVc);
    timerVc.resize(0);
}

/**
 *函数名:清空
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MainWindow::on_pushButton_5_clicked()
{
    ui->plainTextEdit->setPlainText("");
}
