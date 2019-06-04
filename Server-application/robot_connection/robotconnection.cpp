#include "robotconnection.h"


#define toRad(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define toDeg(angleRadians) ((angleRadians) * 180.0 / M_PI)

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
    myTimer.start();
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

    if(communicationSettings.turnOffBots){
        communicationSettings.turnOffBots = false;
        turnOffAllRobots();
    }
    //check of new robots have come online
    if(myTimer.elapsed() <= 5000 && lastRequestedBotIP !="0.0.0.0"){   // 5 seconds to detect a bot when the status has been set to 'STARTUP'
           // check if there is a robot with a green led

        for(int i = 0; i < locationManager.robots.size();i++){
            RobotLocation *ptr = locationManager.robots.at(i);
            if(ptr->type == RobotLocation::RobotType::REAL){
                if(ptr->sharedData.status == robotStatus::STARTUP){ //only possible when camera detection has created a bot
                    ptr->sharedData.status = robotStatus::NORMAL; //the bot has been detected by the camera while the bot has joined je application by broadcasting it's IP
                    ptr->ip = lastRequestedBotIP;
                    lastRequestedBotIP = "0.0.0.0"; //so another bot can be connected
                    qDebug() << "A NEW BOT HAS ACCUIRED AN IP!";
                }
            }
        }
    }  else{
        //remove IP from list
        for(int i = 0; i < IpList.size();i++){
            if(IpList.at(i) == lastRequestedBotIP){
                IpList.removeAt(i);
                qDebug() << " removed bot with ip: " << lastRequestedBotIP << " from the IPList";
            }
        }
        //no robot showed up. lets reset and wait for another bot
        lastRequestedBotIP ="0.0.0.0";


    }
    updateRobots();
    emit done();
}

void RobotConnection::updateRobots()
{
    //send all data to new robots
    for(int i = 0; i < locationManager.robots.size();i++){
        RobotLocation *ptr = locationManager.robots.at(i);
        if(ptr->type == RobotLocation::RobotType::REAL){
            if(ptr->sharedData.status == robotStatus::NORMAL){ //only possible when camera detection has created a bot
                //update the packets of the robots
                ptr->sharedData.newX = ptr->destinationX;
                ptr->sharedData.newY = ptr->destinationY;
                ptr->sharedData.currentX = ptr->x;
                ptr->sharedData.currentY = ptr->y;
                ptr->sharedData.currentAngle = toDeg(ptr->angle);
                ptr->sharedData.speed = 130; // not tested

                //send new packet to the robots
                 socket->writeDatagram(reinterpret_cast<char*>(&ptr->sharedData), sizeof(UdpData) ,QHostAddress(ptr->ip), 4210);
            }
        }
    }
}

void RobotConnection::turnOffAllRobots()
{
    for(int i = 0; i < locationManager.robots.size();i++){
        RobotLocation *ptr = locationManager.robots.at(i);
        if(ptr->type == RobotLocation::RobotType::REAL){
            if(ptr->sharedData.status == robotStatus::NORMAL||ptr->sharedData.status == robotStatus::OFF){ //only possible when camera detection has created a bot
                //update the packets of the robots
                 ptr->sharedData.status = robotStatus::OFF;
                //send new packet to the robots
                 socket->writeDatagram(reinterpret_cast<char*>(&ptr->sharedData), sizeof(UdpData) ,QHostAddress(ptr->ip), 4210);
            }
        }
    }
    IpList.clear();
}


void RobotConnection::processIP(QString ip)
{
//check if IP is new IP
    bool found = false;
    for(int i = 0; i< IpList.size();i++){
        if(!IpList.at(i).compare(ip)){
           //equals
            found = true;
            break;
        }
    }

    if(found){
        //update Voltage
    }else{
        //turn it on
        turnRobotOn(ip);
        //add it to the list

    }
    //no?, update voltage in bots
    //yes?, add it to the list
    //ask the device to turn on ->make local pointer to the device we just asked

//check if there is a new bot with status connecting detected.

}

void RobotConnection::turnRobotOn(QString ip)
{
    if(lastRequestedBotIP =="0.0.0.0"){ //when it is not already waiting for a bot
        lastRequestedBotIP = ip;        //it will set a current bot, which will need to be detected by the camere in order to be added to the list
        UdpData packet;
        packet.status = robotStatus::STARTUP; //tell the robot to turn it's ID led on, so the camera can find it
        qDebug() << "turning robot on with ip: " << ip << endl;
        //send to IP
        socket->writeDatagram(reinterpret_cast<char*>(&packet), sizeof(UdpData) ,QHostAddress(ip), 4210);
        IpList.append(ip);
        myTimer.restart();
    }

}
