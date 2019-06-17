#include "locationmanager.h"

LocationManager robotLocationManager;
LocationManager locationManager;
LocationManager::LocationManager()
{

}

void LocationManager::printAllRobots()
{
    QListIterator<RobotLocation*> i(locationManager.robots);
    while (i.hasNext())
    {
        i.next()->print();
    }
}
RobotLocation *LocationManager::addSimulatedRobot(RobotGroup *group)
{
    RobotLocation *l = new RobotLocation(group);
    l->type = Object::Type::SIMULATED;
    l->sharedData.status = robotStatus::NORMAL;



    int x = qrand() % globalSettings.fieldSizeX;
    int y = qrand() % globalSettings.fieldSizeY;
    int a = qrand() % 360;


    l->x = x;
    l->y = y;
    l->setX(x-0.5*globalSettings.botDiameter);
    l->setY(y-0.5*globalSettings.botDiameter);
    l->destinationX = x;
    l->destinationY = y;
    l->setRotation(a);
    l->simulatedRobot = new SimulatedRobot(l);
    dataScene->addItem(l->simulatedRobot);
    dataScene->addItem(l);
    robots.append(l);

    return l;
}
void LocationManager::deleteAllSimulatedRobots()
{
    QMutableListIterator<RobotLocation*> i(robots);
    while (i.hasNext())
    {
        if(i.next()->type == Object::Type::SIMULATED)
        {
            i.remove();
        }
    }
}
void LocationManager::deleteAllSimulatedRobotsFromGroup(RobotGroup *group)
{
    QMutableListIterator<RobotLocation*> i(robots);
    while (i.hasNext())
    {
        auto val = i.next();
        if(val->type == Object::Type::SIMULATED)
        {
            if(val->group == group)
            {
                i.remove();
            }
        }
    }
}

void LocationManager::addObject(Object *object)
{
    objects.append(object);
}



void LocationManager::makeNewRealRobot(int x, int y)
{
    RobotLocation *newRobot = new RobotLocation();
    newRobot->type = Object::Type::REAL;
    newRobot->sharedData.status = robotStatus::STARTUP;  //when the camera connects, it must be set to startup because it has no IP as of this moment
    newRobot->x = x;
    newRobot->y = y;
    newRobot->sharedData.status = robotStatus::STARTUP;
    newRobot->simulatedRobot = new SimulatedRobot(newRobot);
    robots.append(newRobot);
    //dataScene.addItem(newRobot);
    //Ui::ui->dataSene->addItem(newRobot);

    dataScene->addItem(newRobot->simulatedRobot);
    dataScene->addItem(newRobot);
    qDebug() << "MADE A NEW ROBOT";
}
void LocationManager::resetEverything(){
    //turn off all robots.
    communicationSettings.turnOffAllRobots();  // will also reset IP list

    while(robots.size() > 0){
        RobotLocation* toDelete = robots.takeAt(0);
        dataScene->removeItem(toDelete);
        delete toDelete;
    }

    RobotLocation::currentSelectedRobotptr = nullptr;
    //remove all robots in the robotLocation
    //locationManager.robots.clear();
    //reset IP list tracker


    //add fieldsize back
    dataScene->addRect(0,0,globalSettings.fieldSizeX,globalSettings.fieldSizeY);
}
