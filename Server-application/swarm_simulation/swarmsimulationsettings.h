#ifndef SWARMSIMULATIONSETTINGS_H
#define SWARMSIMULATIONSETTINGS_H

#include <QObject>

class SwarmSimulationSettings
{
public:
    SwarmSimulationSettings();
    int maxSpeed = 5;
};
extern SwarmSimulationSettings swarmSimulationSettings;
#endif // SWARMSIMULATIONSETTINGS_H
