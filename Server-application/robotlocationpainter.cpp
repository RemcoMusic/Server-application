#include <robotlocation.h>
#include "locationmanager.h"
#define toRad(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define toDeg(angleRadians) ((angleRadians) * 180.0 / M_PI)
QRectF RobotLocation::boundingRect() const
{
    return QRectF(0,0,globalSettings.botDiameter,globalSettings.botDiameter);
}

void RobotLocation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPos(x-globalSettings.botDiameter*0.5,y-globalSettings.botDiameter*0.5);
    QRectF rect = boundingRect();
        QBrush brush(Qt::black);
        QPen pen(Qt::red);
        pen.setWidth(1);
        QFont f;

        double d = globalSettings.botDiameter;

        painter->translate(0.5*d,0.5*d);
        painter->rotate(toDeg(angle)+ 90);
        painter->translate(-0.5*d,-0.5*d);

        painter->setPen(pen);
        painter->setBrush(brush);

        for(int i=0;i<LocationManager::currentSelectedObjects.size();i++)
        {
            if(LocationManager::currentSelectedObjects.at(i) == this)
            {
                painter->setBrush(Qt::red);
                break;
            }
        }
        painter->drawEllipse(0,0,d,d);

        if(type == Type::SIMULATED)
        {
            brush.setColor(Qt::yellow);//statusColor
        }
        else {
            brush.setColor(Qt::red);//statusColor
        }
        painter->setBrush(brush);
        double p = 0.1; //value
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        if(userInput)
        {
            brush.setColor(Qt::blue);//statusColor
        }
        else if(collision)
        {
            brush.setColor(Qt::cyan);//statusColor
        }
        else if(batteryVoltage < 6.4){
            brush.setColor(Qt::white);//statusColor
        }
        else
        {
            brush.setColor(Qt::black);//statusColor
        }
        painter->setBrush(brush);
        p = 0.2;
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(Qt::red);//statusColor
        painter->setBrush(brush);
        p = 0.45;
        painter->drawEllipse(p*d,p*d,d-2*p*d,d-2*p*d);

        brush.setColor(Qt::red);//statusColor
        painter->setBrush(brush);
        double v =0.01;
        painter->drawRect(d/2-d*v,0,2*d*v,0.5*d);

//        for(int i = 0;i<=5;i++)
//        {

//            painter->drawArc(0,100-10*i,20*i,20*i,(-70)*16,(140)*16);


//        }


//    painter->translate(100,100);
//    painter->rotate(angle);
//    painter->translate(-100,-100);
//    painter->drawImage(0,0,a);


//    QString i;
//    i.append("X = ");
//    i.append(QString::number(x));
//    i.append("  y = ");
//    i.append(QString::number(y));
//    painter->drawText(0,230, i);


}
void RobotLocation::setRotation(int r){
    angle = r;
}


