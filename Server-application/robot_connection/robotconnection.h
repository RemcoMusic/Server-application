#ifndef ROBOTCONNECTION_H
#define ROBOTCONNECTION_H
#include "swarmbotcommunicationsettings.h"
#include <QObject>
#include <QUdpSocket>
#include <QDebug>
#include "robotlocation.h" // for the UDP struct
#include <QList>
extern SwarmBotCommunicationSettings communicationSettings;
class RobotConnection : public QObject
{
    Q_OBJECT
public:
    RobotConnection();
    QList<QString> IpList;
    void sendUDP(QByteArray byteArray,QString ip, int port);
public slots:
    void readyRead();
    void connectionloop();
signals:
    void done();

private:
    QUdpSocket * socket;
    QString lastRequestedBotIP;

    void processIP(QString ip);
    void turnRobotOn(QString ip);


};

#endif // ROBOTCONNECTION_H
