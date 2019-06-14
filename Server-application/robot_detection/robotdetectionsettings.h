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
    GREEN_HIGH = 5,
    ORANGE_HIGH = 6,
    ORANGE_LOW = 7,
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

    QList<Hsv*> HSVColorValues;
    int erodeObject = 1; //Default 1-20
    int dilateObject = 4; //Default 1-20
    int xyDeviationMilimeter = 50; //Has to be implemented
    int selectCamera = 0;
    bool drawRobots = false; //Default
    bool enableDetection = true; //Default
    cv::Mat processedFrame;
    cv::Mat processedRedFrame;
    cv::Mat processedGreenFrame;
    cv::Mat processedBlueFrame;



};
extern RobotDetectionSettings robotDetectionSettings;
#endif // ROBOTDETECTIONSETTINGS_H
