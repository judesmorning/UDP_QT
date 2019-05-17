#ifndef PACKEMANAGER_H
#define PACKEMANAGER_H

#include <QString>
#include "includes.h"
#include "mymethod.h"
class PackeManager
{
protected:
    VCI_CAN_OBJ obj;
    int packetType=0;
public:
    PackeManager(int packetType);
    virtual VCI_CAN_OBJ getObj(){return obj;}
    void setPacket(const VCI_CAN_OBJ& obj){this->obj = obj;}
    QString getMeaningByType();//根据报文类型调用下面不同函数
private:
    QString getGatherMeaning();
    QString getControlMeaning();
    QString getStateMeaning();
    QString getTestMeaning();
    QString getInfoMeaning();
private:
    std::vector<QString> addrsVc;
    std::vector<QString> packeetVc;
    const QString space=" ";
    const QString nextLine="\n";
};

#endif // PACKEMANAGER_H
