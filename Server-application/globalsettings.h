#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>

class GlobalSettings
{
public:
    GlobalSettings();
    int fieldSizeX=1140;//mm
    int fieldSizeY=860;//mm

    int cameraX= 1280;
    int cameraY= 720;

    int botDiameter = 100;//mm
    int botDistanceBetweenWheels = 80;
    int simulationSpeed = 10;

    bool printRobotDetection = 0;
    bool printSwarmAlgoritme = 0;

    QList<int> HSVColorDetection; //Every 3 items in the list is 1 HSV color will be total of 12
    int erodeObject = 3; //Default
    int dilateObject = 8; //Default
    int xDeviationMilimeter = 0; //Has to be implemented
    int yDeviationMilimeter = 0; //Has to be implemented
    bool drawRobots = false; //Default
};
extern GlobalSettings globalSettings;
#endif // GLOBALSETTINGS_H
