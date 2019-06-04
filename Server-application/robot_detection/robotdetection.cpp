#include "robotdetection.h"

robotDetection::robotDetection()
{
        Hsv* temporaryRL = new Hsv();
        temporaryRL->c = ColorNames::RED_LOW;
        temporaryRL->h = 160;
        temporaryRL->s = 100;
        temporaryRL->v = 100;
        robotDetectionSettings.HSVColorValues.append(temporaryRL);

        Hsv* temporaryRH = new Hsv();
        temporaryRH->c = ColorNames::RED_HIGH;
        temporaryRH->h = 179;
        temporaryRH->s = 255;
        temporaryRH->v = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryRH);

        Hsv* temporaryBL = new Hsv();
        temporaryBL->c = ColorNames::BLUE_LOW;
        temporaryBL->h = 75;
        temporaryBL->s = 100;
        temporaryBL->v = 40;
        robotDetectionSettings.HSVColorValues.append(temporaryBL);

        Hsv* temporaryBH = new Hsv();
        temporaryBH->c = ColorNames::BLUE_HIGH;
        temporaryBH->h = 130;
        temporaryBH->s = 255;
        temporaryBH->v = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryBH);

        Hsv* temporaryGL = new Hsv();
        temporaryGL->c = ColorNames::GREEN_LOW;
        temporaryGL->h = 30;
        temporaryGL->s = 100;
        temporaryGL->v = 100;
        robotDetectionSettings.HSVColorValues.append(temporaryGL);

        Hsv* temporaryGH = new Hsv();
        temporaryGH->c = ColorNames::GREEN_HIGH;
        temporaryGH->h = 75;
        temporaryGH->s = 255;
        temporaryGH->v = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryGH);
}

void robotDetection::run() {
    startDetecting();
}


int robotDetection::startDetecting() {
    cv::VideoCapture cap(0);
    cv::Mat originalFrame;
    cv::Mat threshold;
    cv::Mat HSV;
    cv::Mat RGB;
    cv::Mat R;
    cv::Mat G;
    cv::Mat B;

//    cap.set(cv::CAP_PROP_FRAME_WIDTH, globalSettings.cameraX);
//    cap.set(cv::CAP_PROP_FRAME_HEIGHT, globalSettings.cameraY);

    if(!cap.isOpened()) {
        return -1;
    }

    for(;;) {
        cap >> originalFrame;
        cv::cvtColor(originalFrame,HSV,cv::COLOR_BGR2HSV);

        threshold = detectColors(HSV,"Blue");
        morphOps(threshold);
        cv::cvtColor(threshold,B, cv::COLOR_BGR2RGB);
        robotDetectionSettings.processedBlueFrame = B;
        detectBlueDots(threshold,originalFrame);

        threshold = detectColors(HSV, "Green");
        morphOps(threshold);
        cv::cvtColor(threshold,G, cv::COLOR_BGR2RGB);
        robotDetectionSettings.processedGreenFrame = G;
        detectNewRobots(threshold,originalFrame);

        threshold = detectColors(HSV, "Red");
        morphOps(threshold);
        cv::cvtColor(threshold,R, cv::COLOR_BGR2RGB);
        robotDetectionSettings.processedRedFrame = R;
        trackFilteredObject(threshold,originalFrame);

        cv::cvtColor(originalFrame,RGB, cv::COLOR_BGR2RGB);
        robotDetectionSettings.processedFrame = RGB;

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
            double resizeXFactor = double(globalSettings.fieldSizeX)/double(globalSettings.cameraX);
            double resizeYFactor = double(globalSettings.fieldSizeY)/double(globalSettings.cameraY);
            double calibratedX = ((moment.m10/area) * resizeXFactor);
            double calibratedY = ((moment.m01/area) * resizeYFactor);
            if(area>100) {
                for(int i =0;i<locationManager.robots.size(); i++) {
                    RobotLocation* ptr = locationManager.robots.at(i);
                    if(ptr->type == Object::Type::REAL){
                        if (ptr->x >= (calibratedX - 30) && ptr->x <= (calibratedX + 30)) {
                            if(ptr->y >= (calibratedY - 30) && ptr->y <= (calibratedY + 30)) {
                                newRobot = false;
                                ptr->x=calibratedX;
                                ptr->y=calibratedY;
                                break;
                            }
                        }
                    }
                }
                if (newRobot) {
                    if (robotDetectionSettings.enableDetection) {
                        emit makeANewRobot(calibratedX,calibratedY);
                        newRobot = true;
                    }
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
        if(numObjects<50)
        {
            for (int index = 0; index >= 0; index = hierarchy[index][0])
            {
                cv::Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;
                double resizeXFactor = double(globalSettings.fieldSizeX)/double(globalSettings.cameraX);
                double resizeYFactor = double(globalSettings.fieldSizeY)/double(globalSettings.cameraY);
                double calibratedX = ((moment.m10/area) * resizeXFactor);
                double calibratedY = ((moment.m01/area) * resizeYFactor);
                if(area>100) {
                    for(int i =0;i<locationManager.robots.size(); i++) {
                        RobotLocation* ptr = locationManager.robots.at(i);
                        if(ptr->type == Object::Type::REAL) {
                            if(ptr->sharedData.status == robotStatus::NORMAL) {
                                if (ptr->x >= (calibratedX - robotDetectionSettings.xyDeviationMilimeter) && ptr->x <= (calibratedX + robotDetectionSettings.xyDeviationMilimeter)) {
                                    if(ptr->y >= (calibratedY - robotDetectionSettings.xyDeviationMilimeter) && ptr->y <= (calibratedY + robotDetectionSettings.xyDeviationMilimeter)) {
                                        ptr->x=calibratedX;
                                        ptr->y=calibratedY;
                                        calculateAngle();
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

void robotDetection::detectBlueDots(cv::Mat threshold, cv::Mat &originalFrame) {
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
            double resizeXFactor = double(globalSettings.fieldSizeX)/double(globalSettings.cameraX);
            double resizeYFactor = double(globalSettings.fieldSizeY)/double(globalSettings.cameraY);
            double calibratedX = ((moment.m10/area) * resizeXFactor);
            double calibratedY = ((moment.m01/area) * resizeYFactor);
            if(area>100) {
                for(int i =0;i<bluePoints.size(); i++) {
                    if (bluePoints.at(i).x() >= (calibratedX - 30) && bluePoints.at(i).x() <= (calibratedX + 30)) {
                        if(bluePoints.at(i).y() >= (calibratedY -30) && bluePoints.at(i).y() <= (calibratedY + 30)) {
                            newRobot = false;
                            bluePoints[i].setX(calibratedX);
                            bluePoints[i].setY(calibratedY);
                            break;
                        }
                    }
                }
                if (newRobot) {
                    if (robotDetectionSettings.enableDetection) {
                        bluePoints.append(QPoint(calibratedX,calibratedY));
                        qDebug() << "Size of Bluepoints" << bluePoints.size();
                        newRobot = true;
                    }
                }
                objectFound = true;
            }
            else objectFound = false;
        }
//        if(objectFound)
//        {
//            drawObjects(originalFrame);
//        }
    }
}

cv::Mat robotDetection::detectColors(cv::Mat frame, QString color) {
    if(color == "Red") {
        cv::Mat redDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::RED_LOW)->h, robotDetectionSettings.HSVColorValues.at(ColorNames::RED_LOW)->s,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::RED_LOW)->v),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::RED_HIGH)->h, robotDetectionSettings.HSVColorValues.at(ColorNames::RED_HIGH)->s,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::RED_HIGH)->v), redDetectedColor);
        return redDetectedColor;
    } else if(color == "Green") {
        cv::Mat greenDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN_LOW)->h, robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN_LOW)->s,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN_LOW)->v),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN_HIGH)->h, robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN_HIGH)->s,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN_HIGH)->v), greenDetectedColor);
        return greenDetectedColor;
    } else if(color == "Blue") {
        cv::Mat blueDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE_LOW)->h, robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE_LOW)->s,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE_LOW)->v),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE_HIGH)->h, robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE_HIGH)->s,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE_HIGH)->v), blueDetectedColor);
        return blueDetectedColor;
    }
}

void robotDetection::calculateAngle() {
    for (int i =0;i<locationManager.robots.size(); i++) {
        RobotLocation* ptr = locationManager.robots.at(i);
        if(ptr->type == Object::Type::REAL) {
            if(ptr->sharedData.status == robotStatus::NORMAL) {
                for (int i = 0; i<bluePoints.size(); i++) {
                    int deltaX = ptr->x - bluePoints.at(i).x();
                    int deltaY = ptr->y - bluePoints.at(i).y();
                    double distance = sqrt(deltaX*deltaX + deltaY*deltaY);
                    if(distance <= 55) {
                        double goalAngle = atan2(deltaY,deltaX) + M_PI;
                        if(goalAngle >= 2 *M_PI) {
                            goalAngle -= 2*M_PI;
                        }
                        ptr->angle = goalAngle;
                    }
                }
            }
        }
    }
}

void robotDetection::morphOps(cv::Mat &thresh) {
    cv::Mat erodeElement = getStructuringElement(cv::MORPH_RECT, cv::Size(robotDetectionSettings.erodeObject,robotDetectionSettings.erodeObject));
    cv::Mat dilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(robotDetectionSettings.dilateObject,robotDetectionSettings.dilateObject));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
}

void robotDetection::drawObjects(cv::Mat &frame) {
    for(int i =0; i<locationManager.robots.size(); i++) {
        RobotLocation* ptr = locationManager.robots.at(i);
        double uncalibratedXCordinate = ptr->x / (double(globalSettings.fieldSizeX)/double(globalSettings.cameraX));
        double uncalibratedYCordinate = ptr->y / (double(globalSettings.fieldSizeY)/double(globalSettings.cameraY));
        if(ptr->type == Object::Type::REAL) {
            cv::circle(frame,cv::Point(uncalibratedXCordinate,uncalibratedYCordinate),10,cv::Scalar(0,0,255));
            cv::putText(frame,std::to_string(int(uncalibratedXCordinate))+ " , " + std::to_string(int(uncalibratedYCordinate)),
                        cv::Point(uncalibratedXCordinate,uncalibratedYCordinate),1,1,cv::Scalar(0,255,0));
            std::string str =std::to_string(i);
            cv::putText(frame,str,cv::Point(uncalibratedXCordinate,uncalibratedYCordinate),1,2,cv::Scalar(0,0,255));
        }
    }
}
