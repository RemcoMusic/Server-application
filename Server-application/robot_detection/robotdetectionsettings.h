#ifndef ROBOTDETECTIONSETTINGS_H
#define ROBOTDETECTIONSETTINGS_H

#include <QObject>
#include <opencv2/core/core.hpp>

enum ColorNames{
    NOCOLOR = -1,
    RED = 0,
    BLUE = 1,
    GREEN = 2,
    ORANGE = 3,
    PINK = 4,
    YELLOW = 5,
};

struct Hsv{
    int c = ColorNames::NOCOLOR;
    int h_low =0; //0-179
    int s_low=0; //0-255
    int v_low=0; //0-255
    int h_high =0; //0-179
    int s_high=0; //0-255
    int v_high=0; //0-255
};

class RobotDetectionSettings
{
public:
    RobotDetectionSettings();

    QList<Hsv*> HSVColorValues;
    QString objectColorTracking = "Orange";
    int erodeObject = 1; //Default 1-20
    int dilateObject = 4; //Default 1-20
    int xyDeviationMilimeter = 50; //Has to be implemented
    int selectCamera = 2;
    bool drawRobots = false; //Default
    bool enableDetection = true; //Default
    cv::Mat processedFrame;
    cv::Mat processedRedFrame;
    cv::Mat processedGreenFrame;
    cv::Mat processedBlueFrame;
    cv::Mat processedOrangeFrame;

    QList<int> availableCameras;

};
extern RobotDetectionSettings robotDetectionSettings;
#endif // ROBOTDETECTIONSETTINGS_H
