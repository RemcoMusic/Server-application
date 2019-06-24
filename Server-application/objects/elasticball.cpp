#include "elasticball.h"

ElasticBall::ElasticBall()
{
}
void ElasticBall::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Object::mousePressEvent(event);//call super class
    pressX = x;
    pressY = y;
    pressTime = clock();
}

void ElasticBall::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Ball::mouseMoveEvent(event);//call super class

}

void ElasticBall::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Ball::mouseReleaseEvent(event);//call super class
    int deltaX = x - pressX;
    int deltaY = y - pressY;
    double deltaT = (double)(clock() - pressTime)/CLOCKS_PER_SEC;
    speed = sqrt(deltaX * deltaX + deltaY * deltaY) * deltaT;
    direction = atan2(deltaY, deltaX);
}
