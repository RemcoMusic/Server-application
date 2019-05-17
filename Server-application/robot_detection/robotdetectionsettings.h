#ifndef ROBOTDETECTIONSETTINGS_H
#define ROBOTDETECTIONSETTINGS_H

#include <QObject>

class RobotDetectionSettings
{
public:
    RobotDetectionSettings();

    int redLowerBHue;
    int redLowerBSaturation;
    int redLowerBValue;
    int redHigherBHue;
    int redHigherBSaturation;
    int redHigherBValue;


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
