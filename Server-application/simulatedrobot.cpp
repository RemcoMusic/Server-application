#include "simulatedrobot.h"

#define toRad(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define toDeg(angleRadians) ((angleRadians) * 180.0 / M_PI)


SimulatedRobot::SimulatedRobot(RobotLocation *baseRobot)
{
    myColor.setAlpha(0.3);
    destinationX = baseRobot->destinationX;
    destinationY = baseRobot->destinationY;
    x = baseRobot->x;
    y = baseRobot->y;
    angle = baseRobot->angle;
    speed = baseRobot->speed;
    endAngle = baseRobot->endAngle;
}

void SimulatedRobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPos(x-globalSettings.botDiameter*0.5,y-globalSettings.botDiameter*0.5);
    QRectF rect = boundingRect();
        QColor brushColor = Qt::black;
        brushColor.setAlphaF(0.3);
        QBrush brush(brushColor);

        QColor penColor = Qt::red;
        penColor.setAlphaF(0.3);
        QPen pen(penColor);
        pen.setWidth(1);
        QFont f;

        double d = globalSettings.botDiameter;

        painter->translate(0.5*d,0.5*d);
        painter->rotate(toDeg(angle)+ 90);
        painter->translate(-0.5*d,-0.5*d);

        painter->setPen(pen);
        painter->setBrush(brush);

        painter->drawEllipse(0,0,d,d);

        brush.setColor(myColor);//statusColor
        painter->setBrush(brush);
        double p = 0.1; //value
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(brushColor);//statusColor
        painter->setBrush(brush);
        p = 0.2;
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(penColor);//statusColor
        painter->setBrush(brush);
        p = 0.45;
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(penColor);//statusColor
        painter->setBrush(brush);
        double v =0.01;
        painter->drawRect(d/2-d*v,0,2*d*v,0.5*d);

}



