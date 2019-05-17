#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include <mymethod.h>
class MyTimer : public QTimer
{
    Q_OBJECT
public:
    MyTimer();
    void setData(const QString&);

private slots:
    void timeoutSot();
private:
    QByteArray info;
    void setData(const QByteArray& ba){this->info = ba;}
signals:
    void sendSignal(const QByteArray& ba);
};
extern bool autoAdd;
#endif // MYTIMER_H
