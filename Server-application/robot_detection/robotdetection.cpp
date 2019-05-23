#include "robotdetection.h"

robotDetection::robotDetection() {
    for (int i = 0; i < 6; i++) {
        Hsv temporary;
        temporary.c = i;
        temporary.h = 0;
        temporary.s = 0;
        temporary.v = 0;

        robotDetectionSettings.HSVColorValues.append(temporary);
    }
}

void robotDetection::run() {
    startDetecting();
}

int robotDetection::startDetecting() {
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

        threshold = detectColors(HSV, "Green");
        morphOps(threshold);
        detectNewRobots(threshold,originalFrame);

        threshold = detectColors(HSV, "Red");
        morphOps(threshold);
        trackFilteredObject(threshold,originalFrame);

        imshow("Thresholded Frame", threshold);
        imshow("Color detection", originalFrame);
        robotDetectionSettings.processedFrame = originalFrame;

        emit newFrameFinished();
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}

void robotDetection::detectNewRobots(cv::Mat threshold, cv::Mat &originalFrame) {
    bool newRobot = true;
    cv::Mat temp;
    threshold.copyTo(temp);
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(temp,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE );
    bool objectFound = false;
    if (hierarchy.size() > 0 && hierarchy.size()<50) {
        for (int index = 0; index >= 0; index = hierarchy[index][0]) {
            cv::Moments moment = moments((cv::Mat)contours[index]);
            double area = moment.m00;
            if(area>100) {
                for(int i =0;i<robotLocationManager.robots.size(); i++) {
                    RobotLocation* ptr = robotLocationManager.robots.at(i);
                    if(ptr->type == RobotLocation::RobotType::REAL){
                        if (ptr->x >= (moment.m10/area - 30) && ptr->x <= (moment.m10/area + 30)) {
                            if(ptr->y >= (moment.m01/area -30) && ptr->y <= (moment.m01/area + 30)) {
                                newRobot = false;
                                ptr->x=moment.m10/area;
                                ptr->y=moment.m01/area;
                                break;
                            }
                        }
                    }
                }
                if (newRobot) {
                    emit makeANewRobot(moment.m10/area,moment.m01/area);
                    newRobot = true;
                }
                objectFound = true;
            }
            else objectFound = false;
        }
        if(objectFound)
        {
            drawObjects(originalFrame);
        }
    }
}

void robotDetection::trackFilteredObject(cv::Mat threshold, cv::Mat &originalFrame) {
    cv::Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    cv::findContours(temp,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE );
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
                if(area>100) {
                    for(int i =0;i<robotLocationManager.robots.size(); i++) {
                        RobotLocation* ptr = robotLocationManager.robots.at(i);
                        if(ptr->type == RobotLocation::RobotType::REAL) {
                            if(ptr->sharedData.status == 1) {
                                if (ptr->x >= (moment.m10/area - 30) && ptr->x <= (moment.m10/area + 30)) {
                                    if(ptr->y >= (moment.m01/area -30) && ptr->y <= (moment.m01/area + 30)) {
                                        ptr->x=moment.m10/area;
                                        ptr->y=moment.m01/area;
                                        objectFound = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                } else objectFound = false;
            }
            if(objectFound ==true) {
                drawObjects(originalFrame);
            }
        }
    }
}

cv::Mat robotDetection::detectColors(cv::Mat frame, QString color) {
    if(color == "Red") {
        cv::Mat redDetectedColor;
        cv::Mat low;
        cv::Mat high;
        inRange(frame, cv::Scalar(robotDetectionSettings.redLowerBHue, robotDetectionSettings.redLowerBSaturation, robotDetectionSettings.redLowerBValue),
                cv::Scalar(robotDetectionSettings.redLowerBHue2, robotDetectionSettings.redLowerBSaturation2, robotDetectionSettings.redLowerBValue2), low);
        inRange(frame, cv::Scalar(robotDetectionSettings.redHigherBHue, robotDetectionSettings.redHigherBSaturation, robotDetectionSettings.redHigherBValue),
                cv::Scalar(robotDetectionSettings.redHigherBHue2, robotDetectionSettings.redHigherBSaturation2, robotDetectionSettings.redHigherBValue2), high);
        cv::addWeighted(low, 1.0, high, 1.0, 0.0, redDetectedColor);
        return redDetectedColor;
    } else if(color == "Green") {
        cv::Mat greenDetectedColor;
        cv::Mat low;
        cv::Mat high;
//        inRange(frame, cv::Scalar(robotDetectionSettings.greenLowerBHue, robotDetectionSettings.greenLowerBSaturation, robotDetectionSettings.greenLowerBValue),
//                cv::Scalar(robotDetectionSettings.greenHigherBHue, robotDetectionSettings.greenHigherBSaturation, robotDetectionSettings.greenHigherBValue), greenColorFrame);
        return greenDetectedColor;
    } else if(color == "Blue") {
        cv::Mat blueDetectedColor;
        cv::Mat low;
        cv::Mat high;
//        inRange(frame, cv::Scalar(robotDetectionSettings.blueLowerBHue, robotDetectionSettings.blueLowerBSaturation, robotDetectionSettings.blueLowerBValue),
//                cv::Scalar(robotDetectionSettings.blueHigherBHue, robotDetectionSettings.blueHigherBSaturation, robotDetectionSettings.blueHigherBValue), blueColorFrame);
        return blueDetectedColor;
    }
}

void robotDetection::morphOps(cv::Mat &thresh) {
    cv::Mat erodeElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2,2));
    cv::Mat dilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(8,8));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
}

void robotDetection::drawObjects(cv::Mat &frame) {
    for(int i =0; i<robotLocationManager.robots.size(); i++) {
        RobotLocation* ptr = robotLocationManager.robots.at(i);
        if(ptr->type == RobotLocation::RobotType::REAL) {
            cv::circle(frame,cv::Point(ptr->x,ptr->y),10,cv::Scalar(0,0,255));
            cv::putText(frame,std::to_string(ptr->x)+ " , " + std::to_string(ptr->y),
                        cv::Point(ptr->x,ptr->y+10),1,1,cv::Scalar(0,255,0));
            std::string str =std::to_string(i);
            cv::putText(frame,str,cv::Point(ptr->x,ptr->y-15),1,2,cv::Scalar(0,0,255));
        }
    }
}
