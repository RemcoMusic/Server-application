#pragma once

#include "locationmanager.h"
#include <QListIterator>
#include "robotlocation.h"
#include "globalhelperfunctions.h"
class RobotDisplacementDetection
{
public:
    RobotDisplacementDetection();
    void update();
    void sync();

private:
    void applyComplementeryFilter(RobotLocation *robotLocation);
};

