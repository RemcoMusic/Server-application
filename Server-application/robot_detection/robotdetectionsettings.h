#ifndef ROBOTDETECTIONSETTINGS_H
#define ROBOTDETECTIONSETTINGS_H

#include <QObject>

class RobotDetectionSettings
{
public:
    RobotDetectionSettings();

    int redLowerBHue = 0;
    int redLowerBSaturation = 100;
    int redLowerBValue = 100;

    int redLowerBHue2 = 10;
    int redLowerBSaturation2 = 255;
    int redLowerBValue2 = 255;

    int redHigherBHue = 160;
    int redHigherBSaturation = 100;
    int redHigherBValue = 100;

    int redHigherBHue2 = 179;
    int redHigherBSaturation2 = 255;
    int redHigherBValue2 = 255;

    int blueLowerBHue = 110;
    int blueLowerBSaturation = 50;
    int blueLowerBValue= 50;
    int blueHigherBHue = 130;
    int blueHigherBSaturation = 255;
    int blueHigherBValue = 255;

    int greenLowerBHue;
    int greenLowerBSaturation;
    int greenLowerBValue;
    int greenHigherBHue;
    int greenHigherBSaturation;
    int greenHigherBValue;



};
extern RobotDetectionSettings robotDetectionSettings;
#endif // ROBOTDETECTIONSETTINGS_H
