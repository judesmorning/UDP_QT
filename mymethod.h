#ifndef MYMETHOD_H
#define MYMETHOD_H
#include <QByteArray>
#include "includes.h"
class Mymethod
{
public:
    static Mymethod *GetInstance();
private:
    Mymethod();
public:
    int getBytesFromQString(QString& str,QByteArray& ba);//十六进制字符串转数组
    int getSumCheckRet(const QByteArray&);//判断校验是否正确
    int addSpaceInQString(QString& str);//每两个字符加一个空格
    int addSumCheck(QByteArray& ba);
};

#endif // MYMETHOD_H
