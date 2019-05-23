#ifndef ROBOTDETECTIONSETTINGS_H
#define ROBOTDETECTIONSETTINGS_H

#include <QObject>
#include <opencv2/core/core.hpp>
enum ColorNames{
    NOCOLOR = -1,
    RED_LOW = 0,
    RED_HIGH = 1,
    BLUE_LOW = 2,
    BLUE_HIGH = 3,
    GREEN_LOW = 4,
    GREEN_HIGH = 5
};

struct Hsv{
    int c = ColorNames::NOCOLOR;
    int h =0; //0-179
    int s=0; //0-255
    int v=0; //0-255
};

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

    QList<Hsv> HSVColorValues; //Every 3 items in the list is 1 HSV color will be total of 12
    int erodeObject = 3; //Default 1-20
    int dilateObject = 8; //Default 1-20
    int xyDeviationMilimeter = 0; //Has to be implemented
    bool drawRobots = false; //Default
    cv::Mat processedFrame;



};
extern RobotDetectionSettings robotDetectionSettings;
#endif // ROBOTDETECTIONSETTINGS_H
