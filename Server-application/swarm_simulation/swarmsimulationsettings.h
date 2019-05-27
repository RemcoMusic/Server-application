#ifndef SWARMSIMULATIONSETTINGS_H
#define SWARMSIMULATIONSETTINGS_H

#include <QObject>

class SwarmSimulationSettings
{
public:
    SwarmSimulationSettings();
    int maxSpeed = 2;   //1
    int realisticSimulationEnabled = true;  //1
    int acceleartionControlEnabled = true;  //1
    int badMotorsEnbabled = true;   //1
};
extern SwarmSimulationSettings swarmSimulationSettings;
#endif // SWARMSIMULATIONSETTINGS_H
