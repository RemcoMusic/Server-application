#include "chargealgorithm.h"

ChargeAlgorithm::ChargeAlgorithm()
{
    algorithmDiscription.name = "charge algorithm";
    algorithmDiscription.discription = "drive bots to the charge station";
    algorithmDiscription.minimalAmountOfBots = 1;
    algorithmDiscription.maximalAmountOfBots = 100;
    algorithmDiscription.systemAlgorithm = true;
    //first make a special robot group for the robots that are (or want to) charging
    chargeGroup = new RobotGroup();
    chargeGroup->name = "charge group";
    locationManager.groups.append(chargeGroup);
}
void ChargeAlgorithm::update()
{
    scanBatteryVoltageAllRobots();
    generateLists();

    driveNewRobotsToChargeStation();

    QListIterator<ChargeStation*> i(chargeStations);
    while (i.hasNext())
    {
        chargeStationUpdate(i.next());
    }
    //todo queue robots if there are more robots in the group than charging stations
}

//a chargingstation have a pointer to a robot location, if the robot location is delete the software acces a dangling pointer and so non allocated memory,
//this method prevents that by checking if the robot still exist
void ChargeAlgorithm::validateChargeStationPointers()
{
    QListIterator<ChargeStation*> i(chargeStations);
    while (i.hasNext())
    {
        bool pointerIsValid = false;
        ChargeStation* chargeStation  = i.next();
        QListIterator<RobotLocation*> robotsIterator(chargeRobots);
        while (robotsIterator.hasNext())
        {
            RobotLocation* currentRobot = robotsIterator.next();
            if(chargeStation->chargingRobot == currentRobot)
            {
                pointerIsValid = true;
            }
        }
        if(!pointerIsValid)
        {
            chargeStation->chargingRobot = nullptr;
        }
    }
}
//if a chargingstation have no robot to charge, it can look for new robots with empty battery
void ChargeAlgorithm::driveNewRobotsToChargeStation()
{
    QListIterator<ChargeStation*> i(chargeStations);
    while (i.hasNext())
    {
        ChargeStation* currentChargeStation = i.next();
        if(currentChargeStation->chargingRobot == nullptr)//station is available
        {
            //the station is available, now choose a robot which is not already charging

            //do for each robot in the list
            QListIterator<RobotLocation*> robotIterator(chargeRobots);
            while (robotIterator.hasNext())
            {
                bool alreadyCharging = false;
                RobotLocation* currentRobot = robotIterator.next();
                //and for each charge station
                QListIterator<ChargeStation*> secondStationsIterator(chargeStations);
                while (secondStationsIterator.hasNext())
                {
                    ChargeStation* currentChargeStation = secondStationsIterator.next();
                    if(currentChargeStation->chargingRobot == currentRobot)
                    {
                        alreadyCharging = true;
                    }
                }
                if(!alreadyCharging)
                {
                    currentChargeStation->chargingRobot = currentRobot;
                    currentChargeStation->chargeStatus = ChargeStatus::NOT_CHARGING;
                    qDebug("found robot for charge station");
                    break;
                }
            }
        }
    }
}
void ChargeAlgorithm::chargeStationUpdate(ChargeStation* chargeStation)
{
    if(chargeStation->chargingRobot == nullptr)return;

    if(chargeStation->chargeStatus == ChargeStatus::NOT_CHARGING)
    {
        qDebug("not charging");
        chargeStation->chargeStatus = ChargeStatus::DRIVING_TO_DRIVEWAY;
    }
    if(chargeStation->chargeStatus == ChargeStatus::DRIVING_TO_DRIVEWAY)
    {
         qDebug("drving to driveway");
        chargeStation->chargingRobot->destinationX = chargeStation->getDrivewayX();
        chargeStation->chargingRobot->destinationY = chargeStation->getDrivewayY();
        chargeStation->chargingRobot->speed = swarmAlgorithmsSettings.robotSpeed;
        chargeStation->chargingRobot->endAngle = chargeStation->angle;
        if(!isMoving(chargeStation->chargingRobot))
        {
                chargeStation->chargeStatus = ChargeStatus::DRIVING_INTO_STATION;
        }
    }
    if(chargeStation->chargeStatus == ChargeStatus::DRIVING_INTO_STATION)
    {
         qDebug("driving into chargestation");
        chargeStation->chargingRobot->destinationX = chargeStation->x;
        chargeStation->chargingRobot->destinationY = chargeStation->y;
        chargeStation->chargingRobot->endAngle = chargeStation->angle;
        chargeStation->chargingRobot->speed = swarmAlgorithmsSettings.robotSpeed;

        if(!isMoving(chargeStation->chargingRobot))
        {
                chargeStation->chargeStatus = ChargeStatus::CHARGING;
        }
    }
    if(chargeStation->chargeStatus == ChargeStatus::CHARGING)
    {
         qDebug("charging");
        if(chargeStation->chargingRobot->batteryVoltage >= globalSettings.batteryVoltageFull)
        {
            chargeStation->chargeStatus = ChargeStatus::DRIVING_OUT;
        }
        if(distanceBetweenPoints(chargeStation->x,chargeStation->y,chargeStation->chargingRobot->x, chargeStation->chargingRobot->y) > 100)//if robot is taken out
        {
            chargeStation->chargeStatus = ChargeStatus::DRIVING_TO_DRIVEWAY;
        }
    }
    if(chargeStation->chargeStatus == ChargeStatus::DRIVING_OUT)
    {
         qDebug("driving out");
        chargeStation->chargingRobot->destinationX = chargeStation->getDrivewayX();
        chargeStation->chargingRobot->destinationY = chargeStation->getDrivewayY();
        chargeStation->chargingRobot->speed = swarmAlgorithmsSettings.robotSpeed;

        if(!isMoving(chargeStation->chargingRobot))
        {
            chargeStation->chargingRobot->group = nullptr;
            chargeStation->chargingRobot = nullptr;
            chargeStation->chargeStatus = ChargeStatus::NOT_CHARGING;
        }
    }
}

bool sortRobots(RobotLocation* robot1, RobotLocation* robot2)
{
    return robot1->batteryVoltage < robot2->batteryVoltage;
}
//generate a list of robots that are in the specific group chargeGroup
//also generate a list of charging stations
void ChargeAlgorithm::generateLists()
{
    chargeRobots.clear();
    QListIterator<RobotLocation*> i(locationManager.robots);
    while (i.hasNext())
    {
        RobotLocation* currentRobot = i.next();
        if(currentRobot->group == chargeGroup)
        {
           chargeRobots.append(currentRobot);
        }
    }
    std::sort(chargeRobots.begin(),chargeRobots.end(),sortRobots);

    //and the list of chargestations
    chargeStations.clear();
    QListIterator<Object*> chargeStationsIterator(locationManager.objects);
    while (chargeStationsIterator.hasNext())
    {
        Object* currentObject = chargeStationsIterator.next();
        ChargeStation* chargeStation = dynamic_cast<ChargeStation*>(currentObject);//not sure if it is a chargestation object
        if(chargeStation!=nullptr)//if it is a chargestation
        {
            chargeStations.append(chargeStation);
        }
    }
    validateChargeStationPointers();
}

//check for each robot if the battery is empty, if so add it to the special group of charging robots
void ChargeAlgorithm::scanBatteryVoltageAllRobots()
{
    QListIterator<RobotLocation*> i(locationManager.robots);
    while (i.hasNext())
    {
        RobotLocation* currentRobot = i.next();
        if(currentRobot->batteryVoltage < globalSettings.batteryVoltageThreshold)
        {
            currentRobot->group = chargeGroup;
        }
    }
}
