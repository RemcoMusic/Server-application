#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>

class GlobalSettings
{
public:
    int fieldSizeX=1660;//mm
    int fieldSizeY=1250;//mm

    int cameraX= 640;
    int cameraY= 480;

    int botDiameter = 100;//mm
    int botDistanceBetweenWheels = 80;

    bool printRobotDetection = 0;
    bool printSwarmAlgoritme = 0;

    double batteryVoltageThreshold = 6.0;
    double batteryVoltageFull = 8.4;
};
extern GlobalSettings globalSettings;
#endif // GLOBALSETTINGS_H
