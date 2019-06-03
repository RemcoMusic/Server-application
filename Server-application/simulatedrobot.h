#pragma once

#include "robotlocation.h"



class SimulatedRobot : public RobotLocation
{

public:
    SimulatedRobot(RobotLocation* baseRobot);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event){}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event){}
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){}
};

