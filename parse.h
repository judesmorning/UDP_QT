#ifndef PARSE_H
#define PARSE_H

#include <QObject>

#include "mymethod.h"
#include "packemanager.h"
class Parse : public QObject
{
    Q_OBJECT
public:
    explicit Parse(QObject *parent = 0);
private:
    QByteArray HEAD;
    QByteArray allBa;
    int packetTYpe=PACKET_CAN;
private:
    void workCanPacket(const QByteArray&);
signals:
    void workResultSignal(const QString&);

public slots:
    void recvdDataSlot(const QByteArray&);
public:
    void setPacket(int a){packetTYpe=a;}
};

#endif // PARSE_H
