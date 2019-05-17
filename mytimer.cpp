#include "mytimer.h"
bool autoAdd=false;
MyTimer::MyTimer()
{
    QObject::connect(this,SIGNAL(timeout()),this,SLOT(timeoutSot()));
}

/**
 *函数名:定时发送
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MyTimer::timeoutSot()
{
    if(info[2]==(char)0x02)
    {
        if(autoAdd)
        {
            info[3] = ((uchar)info[3]) + 1;
            Mymethod::GetInstance()->addSumCheck(info);
        }
    }
    emit sendSignal(info);
}

/**
 *函数名:设置发送数据
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void MyTimer::setData(const QString &info)
{
    QByteArray ba;
    QString str=info;
    Mymethod::GetInstance()->getBytesFromQString(str,ba);
    this->setData(ba);
}
