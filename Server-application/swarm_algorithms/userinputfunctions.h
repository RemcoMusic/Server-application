#pragma once

#include <objectsbase.h>
#include <robotlocation.h>
#include <locationmanager.h>

class UserInputFunctions
{
protected:
    UserInputFunctions();

    void findRobotMovementInputs(QList<RobotLocation*>& swarmRobots);
    void findObjectInputs();
    QList<Object *> userInputs;
    void constrainPoint(QPoint *point, int xMin, int yMin, int xMax, int yMax);
};
