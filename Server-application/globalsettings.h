#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>

class GlobalSettings
{
public:
    GlobalSettings();
    int fieldSizeX=1720;//mm
    int fieldSizeY=1150;//mm

    int cameraX= 640;
    int cameraY= 480;

    int botDiameter = 100;//mm
    int botDistanceBetweenWheels = 80;
    int simulationSpeed = 10;

    bool printRobotDetection = 0;
    bool printSwarmAlgoritme = 0;
};
extern GlobalSettings globalSettings;
#endif // GLOBALSETTINGS_H
