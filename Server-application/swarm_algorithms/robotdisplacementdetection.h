#ifndef ROBOTDISPLACEMENTDETECTION_H
#define ROBOTDISPLACEMENTDETECTION_H

#include "robotlocationmanager.h"
#include <QListIterator>
#include "robotlocation.h"

class RobotDisplacementDetection
{
public:
    RobotDisplacementDetection();
    void update();
    void sync();

private:
    void applyComplementeryFilter(RobotLocation *robotLocation);
};

#endif // ROBOTDISPLACEMENTDETECTION_H
