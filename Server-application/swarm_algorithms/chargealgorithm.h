#pragma once

#include "robotlocation.h"
#include "robotgroup.h"
#include "locationmanager.h"
#include "chargestation.h"
#include "globalhelperfunctions.h"

class ChargeAlgorithm : public SwarmAlgorithmBase
{
public:
    ChargeAlgorithm();
    void update();
    void scanBatteryVoltageAllRobots();
private:
    QList<RobotLocation*> chargeRobots;
    QList<ChargeStation*> chargeStations;
    RobotGroup* chargeGroup;

    void validateChargeStationPointers();
    void driveNewRobotsToChargeStation();
    void generateLists();
    void chargeStationUpdate(ChargeStation *chargeStation);
};
