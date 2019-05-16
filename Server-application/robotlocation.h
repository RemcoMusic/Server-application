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

class RobotLocation: public QGraphicsItem
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setRotation(int r);
    RobotLocation(RobotGroup *group = nullptr);
    int angle = 90;

    int x = 0;
    int y = 0;
    QColor myColor = Qt::yellow;

    double batteryVoltage=7.4;

    int destinationX = 0;
    int destinationY = 0;

    RobotGroup* group = nullptr;
    enum class RobotType
    {
        REAL = 1,
        SIMULATED=2
    }type;
    void print();

};

