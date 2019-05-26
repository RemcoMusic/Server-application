#ifndef SWARMSIMULATIONSETTINGS_H
#define SWARMSIMULATIONSETTINGS_H

#include <QObject>

class SwarmSimulationSettings
{
public:
    SwarmSimulationSettings();
    int maxSpeed = 2;
    int realisticSimulationEnabled = true;
    int acceleartionControlEnabled = true;
    int badMotorsEnbabled = true;
};
extern SwarmSimulationSettings swarmSimulationSettings;
#endif // SWARMSIMULATIONSETTINGS_H
