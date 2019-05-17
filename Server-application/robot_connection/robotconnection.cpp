#include "robotconnection.h"

RobotConnection::RobotConnection()
{
    communicationSettings.settingVariables.updateRate=0;

    qDebug() << "udp setup"<<endl;
    //QNetworkInterface hotspot;
//    QHostAddress hotspotAddress;
//    foreach(QNetworkAddressEntry address, hotspot.addressEntries())
//    {
//        if(address.ip().protocol()== QAbstractSocket::IPv4Protocol)
//        {
//            hotspotAddress=address.ip();
//        }
//    }

    //ipAdress = ip;

//    //qDebug()<<hotspot.addressEntries();
//    qDebug()<<hotspotAddress;
//    qDebug()<<
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any,4210);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void RobotConnection::sendUDP(QByteArray byteArray, QString ip, int port)
{

}

void RobotConnection::readyRead()
{

    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);

    qDebug() << "Message From: " << sender.toString();
    qDebug() << "Message Port: " << senderPort;
    qDebug() << "Message: " << Buffer;

    processIP(sender.toString());

}

void RobotConnection::connectionloop()
{
 emit done();
}

void RobotConnection::processIP(QString ip)
{
//check if IP is new IP
    //no?, update voltage in bots
    //yes?, add it to the list
    //ask the device to turn on ->make local pointer to the device we just asked

//check if there is a new bot with status connecting detected.

}
