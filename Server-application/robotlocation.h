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
enum robotStatus{
    OFF = 0,
    STARTUP = 1,
    NORMAL = 2,
    CHARGING = 3,
};
struct UdpData {
  uint16_t currentX = 0;
  uint16_t currentY = 0;
  uint16_t newX = 0;
  uint16_t newY = 0;
  uint16_t currentAngle = 360;
  uint8_t speed = 0;
  uint8_t status = robotStatus::OFF;
};


//status
// 0 = off
// 1 = startup (middle led on)
// 2 = direction leds
// 3 = charging


class RobotLocation: public QGraphicsItem, public QFrame
{
public:
    UdpData sharedData; // <-- must be used for all data that the bots must know

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setRotation(int r);
    RobotLocation(RobotGroup *group = nullptr);




    int angle = 90;

    double x = 0;
    double y = 0;

    double speed = 1;

    int destinationX = 0;
    int destinationY = 0;

    QColor myColor = Qt::yellow;

    double batteryVoltage=7.4;

    RobotGroup* group = nullptr;
    enum class RobotType
    {
        REAL = 1,
        SIMULATED=2
    }type;
    void print();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

