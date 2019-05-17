#include "makepacket.h"
#include "ui_makepacket.h"
#include "mytimer.h"
MakePacket::MakePacket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakePacket)
{
    ui->setupUi(this);
}

MakePacket::~MakePacket()
{
    delete ui;
}

/**
 *函数名:生命信号是否自增
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MakePacket::on_checkBox_clicked(bool checked)
{
    autoAdd = checked;
}

/**
 *函数名:生成报文
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MakePacket::on_pushButton_2_clicked()
{
    QByteArray ba;
    if(0==ui->tabWidget->currentIndex())
    {
        ba.resize(8);memset(ba.data(),0,ba.size());
        ba[0] = (char)0xCC;ba[1] = (char)0xDD;
        ba[2] = (char)0x02;
        ba[3] = (char)ui->lineEdit_3->text().toUInt();//生命信号
        ba[4] = (char)ui->lineEdit_4->text().toUInt();//软件主
        ba[5] = (char)ui->lineEdit_5->text().toUInt();//软件次
        Mymethod::GetInstance()->addSumCheck(ba);
        ui->lineEdit_6->setText("控制主机信息报文");
    }
    else if(1==ui->tabWidget->currentIndex())
    {
        char c = 0x00;
        ba.resize(8);memset(ba.data(),0,ba.size());
        ba[0] = (char)0xCC;ba[1] = (char)0xDD;
        ba[2] = (char)0x03;
        if(0==ui->comboBox->currentIndex())//除尘开关
        {
            c |= 0x01<<0;
        }
        else if(1==ui->comboBox->currentIndex())
        {
            c |= 0x02<<0;
        }
        if(0==ui->comboBox_2->currentIndex())//开关门
        {
            c |= 0x01<<2;
        }
        else if(1==ui->comboBox_2->currentIndex())
        {
            c |= 0x02<<2;
        }
        if(0==ui->comboBox_3->currentIndex())//本地远程
        {
            c |= 0x01<<4;
        }
        else if(1==ui->comboBox_3->currentIndex())
        {
            c |= 0x02<<4;
        }
        if(0==ui->comboBox_4->currentIndex())//运行维护
        {
            c |= 0x01<<6;
        }
        else if(1==ui->comboBox_4->currentIndex())
        {
            c |= 0x02<<6;
        }
        ba[3] = c;c=0x00;
        if(0==ui->comboBox_5->currentIndex())//面阵开关
        {
            c |= 0x01<<0;
        }
        else if(1==ui->comboBox_5->currentIndex())
        {
            c |= 0x02<<0;
        }
        if(0==ui->comboBox_6->currentIndex())//线阵开关
        {
            c |= 0x01<<2;
        }
        else if(1==ui->comboBox_6->currentIndex())
        {
            c |= 0x02<<2;
        }
        if(0==ui->comboBox_7->currentIndex())//加热开关
        {
            c |= 0x01<<4;
        }
        else if(1==ui->comboBox_7->currentIndex())
        {
            c |= 0x02<<4;
        }
        if(0==ui->comboBox_8->currentIndex())//散热开关
        {
            c |= 0x01<<6;
        }
        else if(1==ui->comboBox_8->currentIndex())
        {
            c |= 0x02<<6;
        }
        ba[4] = c;c=0x00;

        if(0==ui->comboBox_9->currentIndex())//模拟开关
        {
            c |= 0x01<<6;
        }
        else if(1==ui->comboBox_9->currentIndex())
        {
            c |= 0x02<<6;
        }
        ba[5] = c;c=0x00;
        Mymethod::GetInstance()->addSumCheck(ba);
        ui->lineEdit_6->setText("控制主机命令报文");
    }
    else
    {
        qDebug()<<"未知错误";
        return;
    }
    QString str=ba.toHex().toUpper();
    Mymethod::GetInstance()->addSpaceInQString(str);
    ui->lineEdit_2->setText(str);
}

/**
 *函数名:添加帧
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MakePacket::on_pushButton_clicked()
{
    UDP_SEND_FRAME_STRUCT frame;
    frame.type = ui->lineEdit_6->text();
    frame.time = ui->lineEdit->text();
    frame.data = ui->lineEdit_2->text();
    emit getUdpFramSignal(frame);
}
