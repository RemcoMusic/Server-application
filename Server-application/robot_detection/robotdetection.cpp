#include "robotdetection.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <QList>
#include <QString>
#include <QtDebug>

robotDetection::robotDetection()
{
}

void robotDetection::run()
{
    detectSomething(); //make sure it has an infinite loop - tyvm will do
}

int robotDetection::detectSomething()
{
    cv::VideoCapture cap(0);
    cv::Mat originalFrame;
    cv::Mat threshold;
    cv::Mat HSV;


    if(!cap.isOpened()) {
        return -1;
    }

    for(;;) {
        cap >> originalFrame;
        cv::cvtColor(originalFrame,HSV,cv::COLOR_BGR2HSV);
        threshold = detectColors(HSV);
        morphOps(threshold);
        trackFilteredObject(threshold,HSV,originalFrame);

        imshow("Color detection", originalFrame);

        emit newFrameFinished();
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;
}

void robotDetection::trackFilteredObject(cv::Mat threshold,cv::Mat HSV, cv::Mat &originalFrame)
{
    bool newRobot = true;
    cv::Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    cv::findContours(temp,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<50)
        {
            for (int index = 0; index >= 0; index = hierarchy[index][0])
            {
                cv::Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;
                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>200)
                {
                    if(robotList.isEmpty()) {
                        robotList.insert(0,"ID_1");
                        robotXcoordinates.insert(0, moment.m10/area);
                        robotYcoordinates.insert(0, moment.m01/area);
                    }else {
//                          for(int i =0;i<robotLocationManager.robots.size();
//                                RobotLocation* ptr = robotLocationManager.robots.at(i);
//                                if(ptr->type == RobotLocation::RobotType::REAL){
//                                }
//                            }
                        for (int i = 0; i < robotList.size(); i++) {
                            if (robotXcoordinates.at(i) >= (moment.m10/area - 30) && robotXcoordinates.at(i) <= (moment.m10/area + 30)) {
                                if(robotYcoordinates.at(i) >= (moment.m01/area -30) && robotYcoordinates.at(i) <= (moment.m01/area + 30)) {
                                    newRobot = false;
                                    robotXcoordinates.replace(i, moment.m10/area);
                                    robotYcoordinates.replace(i, moment.m01/area);
                                    break;
                              }
                            }
                        }
                        if (newRobot) {
                            emit makeANewRobot(500,500);
//                          RobotLocation *newFoundRobot = new RobotLocation();
//                          newFoundRobot->x = moment.m10/area;
//                          newFoundRobot->y = moment.m01/area;
//                          newFoundRobot->type = RobotLocation::RobotType::REAL;
//                          robotLocationManager.robots.append(newFoundRobot);

                            int x = robotList.size()+1;
                            QString f = "ID_";
                            f += QString::number(x);
                            robotList.insert(index + 1, f);
                            robotXcoordinates.insert(index + 1, moment.m10/area);
                            robotYcoordinates.insert(index + 1, moment.m01/area);
                            newRobot = true;
                        }
                    }
                    objectFound = true;
                }
                else objectFound = false;
            }
            if(objectFound ==true)
            {
                drawObjects(originalFrame);
            }
        }
    }
}

void robotDetection::drawObjects(cv::Mat &frame) {

    for(int i =0; i<robotList.size(); i++) {
        cv::circle(frame,cv::Point(robotXcoordinates.at(i),robotYcoordinates.at(i)),10,cv::Scalar(0,0,255));
        cv::putText(frame,std::to_string(robotXcoordinates.at(i))+ " , " + std::to_string(robotYcoordinates.at(i)),
                cv::Point(robotXcoordinates.at(i),robotYcoordinates.at(i)+10),1,1,cv::Scalar(0,255,0));
        cv::putText(frame,robotList.at(i).toLocal8Bit().constData(),cv::Point(robotXcoordinates.at(i),robotYcoordinates.at(i)-15),1,2,cv::Scalar(0,0,255));
    }
}

void robotDetection::morphOps(cv::Mat &thresh) {

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    cv::Mat erodeElement = getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    cv::Mat dilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(8,8));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
}

cv::Mat robotDetection::detectColors(cv::Mat frame) {

    cv::Mat allDetectedColors;
    cv::Mat redDetectedColor;
    cv::Mat low;
    cv::Mat high;

    inRange(frame, cv::Scalar(robotDetectionSettings.redLowerBHue, robotDetectionSettings.redLowerBSaturation, robotDetectionSettings.redLowerBValue),
            cv::Scalar(robotDetectionSettings.redLowerBHue2, robotDetectionSettings.redLowerBSaturation2, robotDetectionSettings.redLowerBValue2), low);
    inRange(frame, cv::Scalar(robotDetectionSettings.redHigherBHue, robotDetectionSettings.redHigherBSaturation, robotDetectionSettings.redHigherBValue),
            cv::Scalar(robotDetectionSettings.redHigherBHue2, robotDetectionSettings.redHigherBSaturation2, robotDetectionSettings.redHigherBValue2), high);

//    inRange(frame, cv::Scalar(robotDetectionSettings.blueLowerBHue, robotDetectionSettings.blueLowerBSaturation, robotDetectionSettings.blueLowerBValue),
//            cv::Scalar(robotDetectionSettings.blueHigherBHue, robotDetectionSettings.blueHigherBSaturation, robotDetectionSettings.blueHigherBValue), blueColorFrame);
//    inRange(frame, cv::Scalar(robotDetectionSettings.greenLowerBHue, robotDetectionSettings.greenLowerBSaturation, robotDetectionSettings.greenLowerBValue),
//            cv::Scalar(robotDetectionSettings.greenHigherBHue, robotDetectionSettings.greenHigherBSaturation, robotDetectionSettings.greenHigherBValue), greenColorFrame);

    cv::addWeighted(low, 1.0, high, 1.0, 0.0, allDetectedColors);
    //cv::addWeighted(redDetectedColor, 1.0, blueColorFrame, 1.0, 0.0, allDetectedColors);
    return allDetectedColors;
}
