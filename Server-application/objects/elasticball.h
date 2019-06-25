#pragma once

#include "ball.h"
#include "objectsbase.h"

class ElasticBall : public Ball
{
public:
    ElasticBall();
    double speed = 200;
    double direction = qrand()%2*M_PI;

    double pressX;
    double pressY;
    clock_t pressTime;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

