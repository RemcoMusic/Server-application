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
};
extern GlobalSettings globalSettings;
#endif // GLOBALSETTINGS_H
