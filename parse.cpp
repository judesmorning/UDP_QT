#include "parse.h"

Parse::Parse(QObject *parent) : QObject(parent)
{
    HEAD.resize(2);
    HEAD[0]=char(0xCC);
    HEAD[1]=char(0xDD);
}
/***********************************************/
// z 函数名称:数据入口
// h 函数作用:NULL
// u 函数参数:NULL
// x 函数返回值:NULL
// y 备注:NULL
/***********************************************/
void Parse::recvdDataSlot(const QByteArray &ba)
{
    allBa.append(ba);//读取数据
    int head = allBa.indexOf(HEAD);//报文头的位置
    QByteArray tempBa;
    while (-1 != head)
    {
        allBa = allBa.mid(head);//去掉报头之前的
        int length = allBa.size();
        if(length <= 4)
        {
            break;
        }
        if(allBa[2] == (char)0x01)//can转发报文
        {
            if(length < LENTH_CAN)
            {
                break;
            }
            else
            {
                tempBa = allBa.mid(0,LENTH_CAN);
                if(RET_ERR == Mymethod::GetInstance()->getSumCheckRet(tempBa))//通不过校验
                {
                    allBa = allBa.mid(2);
                    continue;
                }
                else//通过校验
                {
                    //开始解析
                    workCanPacket(tempBa);
                    allBa = allBa.mid(2);
                }

            }
        }
        else if(allBa[2] == (char)0x02)//控制主机信息报文
        {
            if(length < LENTH_INFO)
            {
                break;
            }
            else
            {
                tempBa = allBa.mid(0,LENTH_INFO);
                if(RET_ERR == Mymethod::GetInstance()->getSumCheckRet(tempBa))
                {
                    allBa = allBa.mid(2);
                    continue;
                }
                else
                {
                    QString ret,tempStr;
                    tempStr = tempBa.toHex().toUpper();
                    ret += "转发的控制主机信息报文 ";
                    Mymethod::GetInstance()->addSpaceInQString(tempStr);
                    ret += "数据:"+tempStr;
                    if(packetTYpe==PACKET_ALL || packetTYpe==PACKET_INFO)
                    {
                        emit workResultSignal(ret);
                    }
                    allBa = allBa.mid(2);
                }

            }
        }
        else if(allBa[2] == (char)0x03)//控制主机命令报文
        {
            if(length < LENTH_ORDER)
            {
                break;
            }
            else
            {
                tempBa = allBa.mid(0,LENTH_ORDER);
                if(RET_ERR == Mymethod::GetInstance()->getSumCheckRet(tempBa))
                {
                    allBa = allBa.mid(2);
                    continue;
                }
                else
                {
                    QString ret,tempStr;
                    tempStr = tempBa.toHex().toUpper();
                    ret += "转发的控制主机命令报文 ";
                    Mymethod::GetInstance()->addSpaceInQString(tempStr);
                    ret += "数据:"+tempStr;
                    if(packetTYpe==PACKET_ALL || packetTYpe==PACKET_ORDER)
                    {
                        emit workResultSignal(ret);
                    }
                    allBa = allBa.mid(2);
                }

            }
        }
        else//非协议报文
        {
            allBa = allBa.mid(2);
        }
        head = allBa.indexOf(HEAD);//刷新报文头的位置
    }
}

/**
 *函数名:解析can的转发报文
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
void Parse::workCanPacket(const QByteArray& ba)
{
    VCI_CAN_OBJ obj;memset(obj.Data,0,8);
    obj.DataLen = 8;
    memcpy(obj.Data,ba.data()+5,8);
    QString ret="";
    if((char)0x11==ba[3])//采集报文
    {
        if((char)0xF2==ba[4])
        {
            PackeManager pm(GATHER_PACKET);
            pm.setPacket(obj);
            ret += "公共信号板采集报文 ";
            QByteArray dataBa;dataBa.resize(obj.DataLen);memcpy(dataBa.data(),obj.Data,obj.DataLen);
            QString dataStr = dataBa.toHex().toUpper();
            Mymethod::GetInstance()->addSpaceInQString(dataStr);
            ret += "数据:" + dataStr + "\n";
            ret += "解析:"+pm.getMeaningByType();
        }
        else
        {
            qDebug()<<"ret in:"<<__FILE__<<" at:"<<__LINE__;
            return;
        }
    }
    else if((char)0x21==ba[3])//控制报文
    {
        if((char)0xF1==ba[4])
        {
            PackeManager pm(CONTROL_PACKET);
            pm.setPacket(obj);
            ret += "设备间主控箱控制报文 ";
            QByteArray dataBa;dataBa.resize(obj.DataLen);memcpy(dataBa.data(),obj.Data,obj.DataLen);
            QString dataStr = dataBa.toHex().toUpper();
            Mymethod::GetInstance()->addSpaceInQString(dataStr);
            ret += "数据:" + dataStr + "\n";
            ret += "解析:"+pm.getMeaningByType();
        }
        else
        {
            qDebug()<<"ret in:"<<__FILE__<<" at:"<<__LINE__;
            return;
        }
    }
    else if((char)0x31==ba[3])//状态报文
    {
        if((char)0xF3==ba[4])
        {
            ret += "沉箱状态报文 ";
        }
        else if((char)0xF4==ba[4])
        {
            ret += "侧箱状态报文 ";
        }
        else if((char)0xF5==ba[4])
        {
            ret += "车顶状态报文 ";
        }
        else
        {
            qDebug()<<"ret in:"<<__FILE__<<" at:"<<__LINE__;
            return;
        }
        PackeManager pm(STATE_PACKET);
        pm.setPacket(obj);
        QByteArray dataBa;dataBa.resize(obj.DataLen);memcpy(dataBa.data(),obj.Data,obj.DataLen);
        QString dataStr = dataBa.toHex().toUpper();
        Mymethod::GetInstance()->addSpaceInQString(dataStr);
        ret += "数据:" + dataStr + "\n";
        ret += "解析:"+pm.getMeaningByType();
    }
    else if((char)0x41==ba[3])//监测报文
    {
        if((char)0xF2==ba[4])
        {
            PackeManager pm(TESTING_PACKET);
            pm.setPacket(obj);
            ret += "轨旁控制箱状态监测报文 ";
            QByteArray dataBa;dataBa.resize(obj.DataLen);memcpy(dataBa.data(),obj.Data,obj.DataLen);
            QString dataStr = dataBa.toHex().toUpper();
            Mymethod::GetInstance()->addSpaceInQString(dataStr);
            ret += "数据:" + dataStr + "\n";
            ret += "解析:"+pm.getMeaningByType();
        }
        else
        {
            qDebug()<<"ret in:"<<__FILE__<<" at:"<<__LINE__;
            return;
        }
    }
    else if((char)0x51==ba[3])//信息报文
    {
        if((char)0xF1==ba[4])
        {
            ret += "主控箱信息报文 ";
        }
        else if((char)0xF2==ba[4])
        {
            ret += "公共信号板信息报文 ";
        }
        else if((char)0xF3==ba[4])
        {
            ret += "沉箱信息报文 ";
        }
        else if((char)0xF4==ba[4])
        {
            ret += "侧信息报文 ";
        }
        else if((char)0xF5==ba[4])
        {
            ret += "车顶信息报文 ";
        }
        else
        {
            qDebug()<<"ret in:"<<__FILE__<<" at:"<<__LINE__;
            return;
        }
        PackeManager pm(INFO_PACKET);
        pm.setPacket(obj);
        QByteArray dataBa;dataBa.resize(obj.DataLen);memcpy(dataBa.data(),obj.Data,obj.DataLen);
        QString dataStr = dataBa.toHex().toUpper();
        Mymethod::GetInstance()->addSpaceInQString(dataStr);
        ret += "数据:" + dataStr + "\n";
        ret += "解析:"+pm.getMeaningByType();
    }
    else
    {
        qDebug()<<"ret in:"<<__FILE__<<" at:"<<__LINE__;
        return;
    }
    //qDebug()<<ret;
    if(packetTYpe==PACKET_ALL || packetTYpe==PACKET_CAN)
    {
        emit workResultSignal(ret);
    }
}
