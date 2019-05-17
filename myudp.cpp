#include "myudp.h"

Myudp::Myudp(QObject *parent) : QObject(parent)
{

}

/***********************************************/
// z 函数名称:初始化
// h 函数作用:NULL
// u 函数参数:NULL
// x 函数返回值:NULL
// y 备注:NULL
/***********************************************/
void Myudp::initUdpSlot()
{
    udpPtr = new QUdpSocket(this);
    RET_IF_EAQU(udpPtr,NULL);
    udpPtr->bind(QHostAddress(localIp),localPort);
    QObject::connect(udpPtr,SIGNAL(readyRead()),this,SLOT(onRequest()));
}

/***********************************************/
// z 函数名称:接收数据
// h 函数作用:NULL
// u 函数参数:NULL
// x 函数返回值:NULL
// y 备注:NULL
/***********************************************/
void Myudp::onRequest()
{
    if(udpPtr->pendingDatagramSize() == 0)
    {
        return;
    }
    QByteArray ba;
    ba.resize(udpPtr->pendingDatagramSize());
    QHostAddress tempHost("");
    quint16 port = 0;
    udpPtr->readDatagram(ba.data(),udpPtr->pendingDatagramSize(),&tempHost,&port);
    RET_IF_EAQU(ba.size(),0);
    //qDebug()<<"rcv:"<<ba.toHex().toUpper();
    emit rcvdDataSignal(ba);
}

/**
 *函数名:发送槽函数
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void Myudp::sendSlot(const QByteArray &info)
{
    if(info.size()==udpPtr->writeDatagram(info,QHostAddress(cpuIp),cpuPort))
    {
        QString str = info.toHex().toUpper();
        Mymethod::GetInstance()->addSpaceInQString(str);
        emit sendedSignal(str);
    }
}
