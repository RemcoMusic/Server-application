#ifndef CHARGESTATOIN_H
#define CHARGESTATOIN_H

#include "objectsbase.h"
#include "robotlocation.h"
#include "globalhelperfunctions.h"


enum class ChargeStatus
{
    NOT_CHARGING = 0,
    IN_QUEUE = 1,
    DRIVING_INTO_STATION = 2,
    DRIVING_TO_DRIVEWAY = 3,
    CHARGING = 4,
    DRIVING_OUT = 5
};

class ChargeStation : public Object
{
public:
    ChargeStation();
    double angle = M_PI;
    int size = 100;//mm
    int drivewayDistance = 200;

    int getDrivewayX();
    int getDrivewayY();

    RobotLocation* chargingRobot;
    ChargeStatus chargeStatus = ChargeStatus::NOT_CHARGING;


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    int drivewayX = x;
    int drivewayY = y;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // CHARGESTATOIN_H
