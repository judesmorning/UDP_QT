#include "mymethod.h"

Mymethod::Mymethod()
{

}

/**
 *函数名:返回单列对象
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
Mymethod *Mymethod::GetInstance()
{
    static Mymethod gp;
    return &gp;
}

/**
 *函数名:NULL
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
int Mymethod::getBytesFromQString(QString &str, QByteArray &ba)
{
    int ret = RET_OK;
    str.remove(QRegExp("\\s"));//去掉空格
    if(0 != str.size()%2)//如果不是偶数个字符则加上0
    {
        str = "0"+str;
    }
    ba.resize(str.size()/2);
    QString tmpStr;
    int j=0;
    for(int i=0;i<str.size();i++)
    {
        tmpStr = str[i++];
        tmpStr += str[i];
        ba[j++] = tmpStr.toUInt(nullptr,16);
    }
    return ret;
}

/**
 *函数名:每两个字符加一个空格
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
int Mymethod::addSpaceInQString(QString &str)
{
    int ret = RET_OK;
    QString retStr;
    for(int i=0;i<str.size();i++)
    {
        retStr += str.mid(i,2);
        retStr += " ";
        i++;
    }
    str = retStr;
    return ret;
}

/**
 *函数名:求和校验是否正确
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
int Mymethod::getSumCheckRet(const QByteArray &ba)
{
    int ret = RET_OK;
    uchar sum=0;
    for(int i=0;i<(ba.size()-1);i++)
    {
        sum += (uchar)ba[i];
    }
    if(sum != (uchar)ba[ba.size()-1])
    {
        ret = RET_ERR;
    }

    return ret;
}

/**
 *函数名:添加校验和
 *函数参数:NULL
 *函数作用:NULL
 *函数返回值:NULL
 *备注:NULL
 */
int Mymethod::addSumCheck(QByteArray &ba)
{
    int ret = RET_OK;
    uchar sum=0;
    for(int i=0;i<ba.size()-1;i++)
    {
        sum += (uchar)ba[i];
    }
    ba[ba.size()-1] = (char)sum;

    return ret;
}
