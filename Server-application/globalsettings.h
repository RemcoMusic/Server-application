#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QObject>

class GlobalSettings
{
public:
    GlobalSettings();
    int fieldSizeX=1000;//mm
    int fieldSizeY=1000;//mm

    int botDiameter = 100;//mm

    bool printRobotDetection = 0;
    bool printSwarmAlgoritme = 0;

};
extern GlobalSettings globalSettings;
#endif // GLOBALSETTINGS_H
