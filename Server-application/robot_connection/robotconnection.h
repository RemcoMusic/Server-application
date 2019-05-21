#ifndef ROBOTCONNECTION_H
#define ROBOTCONNECTION_H
#include "swarmbotcommunicationsettings.h"
#include <QObject>
#include <QUdpSocket>
#include <QDebug>
#include "robotlocation.h" // for the UDP struct
#include "robotlocationmanager.h"
#include <QList>
#include <QTime>
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
    void updateRobots();
signals:
    void done();

private:
    QUdpSocket * socket;
    QString lastRequestedBotIP;
    QTime myTimer;


    void processIP(QString ip);
    void turnRobotOn(QString ip);


};

#endif // ROBOTCONNECTION_H
