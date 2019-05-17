#ifndef INCLUDES_H
#define INCLUDES_H
/*头文件包含*/
#include <QDebug>
#include <QThread>
#include <memory>
#include <iostream>
#include <QSharedPointer>
#include <QPointer>
#include <QTimer>
#include <QMetaType>
#include <QThread>
#include <QDateTime>
#include <windows.h>
#include <QMessageBox>
/*返回值枚举类型*/
enum RET_VALUE{
    RET_ERR=-1,
    RET_OK
};
/*返回宏*/
#define RET_VALUE_IF_NOT_EAQU(a,b,c)  \
    do {  \
    if(a!=b) \
{        \
    return c; \
    }        \
    } while (false)

#define RET_VALUE_IF_EAQU(a,b,c)  \
    do {  \
    if(a==b) \
{        \
    qDebug()<<"returnd at line:"<<__LINE__<<"in source:"<<__FILE__;    \
    return c; \
    }        \
    } while (false)

#define RET_IF_NOT_EAQU(a,b)  \
    do {  \
    if(a!=b) \
{        \
    return; \
    }        \
    } while (false)

#define RET_IF_EAQU(a,b)  \
    do {  \
    if(a==b) \
{        \
    qDebug()<<"returnd at line:"<<__LINE__<<"in source:"<<__FILE__;    \
    return; \
    }        \
    } while (false)


/*报文类型*/
enum PACKET_TYPE{
    PACKET_CAN=0x01,
    PACKET_INFO,
    PACKET_ORDER,
    PACKET_ALL
};

/*报文长度*/
#define LENTH_CAN 14
#define LENTH_INFO 8
#define LENTH_ORDER 8


/*定义CAN信息帧的数据类型*/
typedef  struct  _VCI_CAN_OBJ{
    UINT	ID;
    UINT	TimeStamp;
    BYTE	TimeFlag;
    BYTE	SendType;
    BYTE	RemoteFlag;//是否是远程帧
    BYTE	ExternFlag;//是否是扩展帧
    BYTE	DataLen;
    BYTE	Data[8];
    BYTE	Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

/*报文类型*/
enum CAN_PACKET_TYPE{
    GATHER_PACKET=1,//信号采集板采集报文
    CONTROL_PACKET,//设备间主控箱控制报文
    STATE_PACKET,//采集模块状态报文
    TESTING_PACKET,//轨旁控制箱状态检测报文
    INFO_PACKET,//板卡信息报文
    ALL_PACKET//所有的报文
};

/*传输类型*/
enum CAN_TRANSMIT_TYPE{
    CAN_SEND=0,//发送
    CAN_RCV//接收
};

struct UDP_SEND_FRAME_STRUCT{
    UDP_SEND_FRAME_STRUCT()
    {
        type="";
        time="";
        data="";
    }
    QString type;
    QString time;
    QString data;
};

#endif // INCLUDES_H
