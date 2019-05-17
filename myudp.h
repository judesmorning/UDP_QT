#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include "includes.h"
#include <QUdpSocket>
#include "mymethod.h"
class Myudp : public QObject
{
    Q_OBJECT
private:
    QPointer<QUdpSocket> udpPtr;
    const QString localIp="10.2.1.57";
    const quint16 localPort=8899;
    const QString cpuIp="10.2.1.57";
    const quint16 cpuPort=6677;
public:
    explicit Myudp(QObject *parent = 0);

signals:
    void rcvdDataSignal(const QByteArray&);
    void sendedSignal(const QString&);//发送成功
private slots:
    void initUdpSlot();
    void onRequest();
    void sendSlot(const QByteArray&);
};

#endif // MYUDP_H
