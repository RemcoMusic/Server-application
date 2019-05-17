#ifndef LINEARMOTIONALGORITHMS_H
#define LINEARMOTIONALGORITHMS_H

#include <QObject>
#include "swarmalgorithmbase.h"
#include "robotlocationmanager.h"
#include "math.h"
class LinearMotionAlgorithms : public SwarmAlgorithmBase
{
public:

    LinearMotionAlgorithms();
    struct Destination
    {
        int x;
        int y;
        bool occupied=false;
        RobotLocation* robot = nullptr;
    };
    QList<Destination*> destinations;
    void update();

    struct DistanceObject
    {
        RobotLocation* robot = nullptr;
        int distance;
    };
private:
    void calculateDestination();


    void moveRobotTo(RobotLocation *robot, Destination *destination);
};

#endif // LINEARMOTIONALGORITHMS_H
