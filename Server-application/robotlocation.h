//Swarmbotron application
//Rene Schouten
//5-2019
//this class represent a single robot of the swarm, it can be both simulated or real
#pragma once

#include <QObject>
#include "robotgroup.h"
#include "globalsettings.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QFrame>
#include <math.h>
#include "objectsbase.h"


enum robotStatus{
    OFF = 0,
    STARTUP = 1,
    NORMAL = 2,
    CHARGING = 3,
};
#define DIRECTION_FORWARD 0
#define DIRECTION_BACKWARD 1
#define DIRECTION_BOTH 2
struct  UdpData {
  uint16_t currentX = 0;
  uint16_t currentY = 0;
  uint16_t newX = 0;
  uint16_t newY = 0;
  uint16_t currentAngle = 360;
  uint8_t speed = 0;
  uint8_t status = robotStatus::OFF;
  uint8_t drivingDirection = DIRECTION_BOTH;
};


//status
// 0 = off
// 1 = startup (middle led on)
// 2 = direction leds
// 3 = charging


class RobotLocation: public Object
{
public:    
    UdpData sharedData; // <-- must be used for all data that the bots must know

    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setRotation(int r);

    RobotLocation(RobotGroup *group = nullptr);
    ~RobotLocation();
    bool isReady();

    QString ip = "0.0.0.0";  // 0.0.0.0 equals no IP

    RobotLocation *simulatedRobot = nullptr;
    clock_t lastDisplacement = 0;
    bool userInput = false;//if displaced by the user
    bool collision = false;//if a collision occured, for the status color


    double angle = 0;



    double speed = 1;
    double currentSpeedLeft = 0;
    double currentSpeedRight = 0;

    int destinationX = 0;
    int destinationY = 0;
    double endAngle = 0;

    double batteryVoltage=7.4;

    RobotGroup* group = nullptr;

    void print();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

