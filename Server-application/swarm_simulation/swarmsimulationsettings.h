#ifndef SWARMSIMULATIONSETTINGS_H
#define SWARMSIMULATIONSETTINGS_H

#include <QObject>



class SwarmSimulationSettings
{
public:
    SwarmSimulationSettings();
    int realisticSimulationEnabled = true;  //1
    int acceleartionControlEnabled = true;  //1
    int badMotorsEnbabled = true;   //1
    bool enableArduinoLogging = false;
    int simulationSpeed = 1;

};
extern SwarmSimulationSettings swarmSimulationSettings;
#endif // SWARMSIMULATIONSETTINGS_H
