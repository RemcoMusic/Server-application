#ifndef USERINPUTFUNCTIONS_H
#define USERINPUTFUNCTIONS_H

#include <objectsbase.h>
#include <robotlocation.h>
#include <locationmanager.h>


class UserInputFunctions
{
public:
    UserInputFunctions();
protected:
    void findRobotMovementInputs(QList<RobotLocation*>& swarmRobots);
    void findObjectInputs(bool simulated);
    QList<Object *> userInputs;
};

#endif // USERINPUTFUNCTIONS_H
