#include "robotdetection.h"

robotDetection::robotDetection()
{
        Hsv* temporaryRL = new Hsv();
        temporaryRL->c = ColorNames::RED;
        temporaryRL->h_low = 160;
        temporaryRL->s_low = 100;
        temporaryRL->v_low = 100;
        temporaryRL->h_high = 179;
        temporaryRL->s_high = 255;
        temporaryRL->v_high = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryRL);

        Hsv* temporaryBL = new Hsv();
        temporaryBL->c = ColorNames::BLUE;
        temporaryBL->h_low = 75;
        temporaryBL->s_low = 160;
        temporaryBL->v_low = 75;
        temporaryBL->h_high = 130;
        temporaryBL->s_high = 255;
        temporaryBL->v_high = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryBL);

        Hsv* temporaryGL = new Hsv();
        temporaryGL->c = ColorNames::GREEN;
        temporaryGL->h_low = 30;
        temporaryGL->s_low = 100;
        temporaryGL->v_low = 100;
        temporaryGL->h_high = 75;
        temporaryGL->s_high = 255;
        temporaryGL->v_high = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryGL);

        Hsv* temporaryOL = new Hsv();
        temporaryOL->c = ColorNames::ORANGE;
        temporaryOL->h_low = 0;
        temporaryOL->s_low = 120;
        temporaryOL->v_low = 180;
        temporaryOL->h_high = 22;
        temporaryOL->s_high = 255;
        temporaryOL->v_high = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryOL);

        Hsv* temporaryPL = new Hsv();
        temporaryPL->c = ColorNames::PINK;
        temporaryPL->h_low = 130;
        temporaryPL->s_low = 100;
        temporaryPL->v_low = 100;
        temporaryPL->h_high = 160;
        temporaryPL->s_high = 255;
        temporaryPL->v_high = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryPL);

        Hsv* temporaryYL = new Hsv();
        temporaryYL->c = ColorNames::YELLOW;
        temporaryYL->h_low = 22;
        temporaryYL->s_low = 150;
        temporaryYL->v_low = 130;
        temporaryYL->h_high = 38;
        temporaryYL->s_high = 255;
        temporaryYL->v_high = 255;
        robotDetectionSettings.HSVColorValues.append(temporaryYL);

        listCameras();

}
void robotDetection::listCameras()
{
   robotDetectionSettings.availableCameras.clear();
   cv::VideoCapture temp_camera;
   int maxTested = 10;
   for (int i = 0; i < maxTested; i++){
     cv::VideoCapture temp_camera(i);
     bool state = (temp_camera.isOpened());
     temp_camera.release();
     if (state)
     {
       qDebug("camera nr %d",i);
       robotDetectionSettings.availableCameras.append(i);
     }
   }
   robotDetectionSettings.selectCamera = robotDetectionSettings.availableCameras.last();
   oldCameraInput = robotDetectionSettings.selectCamera;
    qDebug("selected camera %d",robotDetectionSettings.selectCamera);
}
void robotDetection::run() {
    startDetecting();
}

void robotDetection::startDetecting() {
    cv::VideoCapture cap(robotDetectionSettings.selectCamera);
    cv::Mat originalFrame;
    cv::Mat threshold;
    cv::Mat HSV;
    cv::Mat RGB;
    cv::Mat R;
    cv::Mat G;
    cv::Mat B;
    cv::Mat O;

    for(;;) {
        if (robotDetectionSettings.selectCamera != oldCameraInput){
            cap.release();
            cap.open(robotDetectionSettings.selectCamera);
            oldCameraInput = robotDetectionSettings.selectCamera;
        }
        if(!cap.isOpened()) {
            qDebug() << "There is no camera detected";
        } else {
            cap >> originalFrame;
            cv::cvtColor(originalFrame,HSV,cv::COLOR_BGR2HSV);

            threshold = detectColors(HSV,"Blue");
            morphOps(threshold);
            cv::cvtColor(threshold,B, cv::COLOR_BGR2RGB);
            robotDetectionSettings.processedBlueFrame = B;
            detectBlueDots(threshold);

            threshold = detectColors(HSV, "Green");
            morphOps(threshold);
            cv::cvtColor(threshold,G, cv::COLOR_BGR2RGB);
            robotDetectionSettings.processedGreenFrame = G;
            detectNewRobots(threshold);

            threshold = detectColors(HSV, "Red");
            morphOps(threshold);
            cv::cvtColor(threshold,R, cv::COLOR_BGR2RGB);
            robotDetectionSettings.processedRedFrame = R;
            trackFilteredObject(threshold,originalFrame);

            threshold = detectColors(HSV,robotDetectionSettings.objectColorTracking);
            morphOps(threshold);
            cv::cvtColor(threshold,O, cv::COLOR_BGR2RGB);
            robotDetectionSettings.processedOrangeFrame = O;
            detectBall(threshold, originalFrame);

            cv::cvtColor(originalFrame,RGB, cv::COLOR_BGR2RGB);
            robotDetectionSettings.processedFrame = RGB;
            deleteUndetectedObject();
            emit newFrameFinished();
        }
    }
}

void robotDetection::detectNewRobots(cv::Mat threshold) {
    bool newRobot = true;
    cv::Mat temp;
    threshold.copyTo(temp);
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(temp,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE );
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
            }
        }
    }
}

void robotDetection::trackFilteredObject(cv::Mat threshold, cv::Mat &originalFrame) {
    cv::Mat temp;
    threshold.copyTo(temp);
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(temp,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE );
    bool objectFound = false;
    if (hierarchy.size() > 0 && hierarchy.size() < 50) {
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
            drawRobots(originalFrame);
        }
    }
}

void robotDetection::detectBlueDots(cv::Mat threshold) {
    bool newRobot = true;
    cv::Mat temp;
    threshold.copyTo(temp);
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(temp,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE );
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
                    if(bluePoints.at(i).x() >= (calibratedX - 30) && bluePoints.at(i).x() <= (calibratedX + 30)) {
                        if(bluePoints.at(i).y() >= (calibratedY -30) && bluePoints.at(i).y() <= (calibratedY + 30)) {
                            newRobot = false;
                            bluePoints[i].setX(calibratedX);
                            bluePoints[i].setY(calibratedY);
                            break;
                        }
                    }
                }
                if (newRobot) {
                        bluePoints.append(QPoint(calibratedX,calibratedY));
                        newRobot = true;
                }
            }
        }
    }
}

void robotDetection::detectBall(cv::Mat threshold, cv::Mat &originalFrame) {
    bool newBall = true;
    bool objectFound = false;
    cv::Mat temp;
    threshold.copyTo(temp);
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(temp,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE );
    if (hierarchy.size() > 0 && hierarchy.size()<50) {
        for (int index = 0; index >= 0; index = hierarchy[index][0]) {
            cv::Moments moment = moments((cv::Mat)contours[index]);
            double area = moment.m00;
            double resizeXFactor = double(globalSettings.fieldSizeX)/double(globalSettings.cameraX);
            double resizeYFactor = double(globalSettings.fieldSizeY)/double(globalSettings.cameraY);
            double calibratedX = ((moment.m10/area) * resizeXFactor);
            double calibratedY = ((moment.m01/area) * resizeYFactor);
            if(area>100) {
                for(int i =0;i<locationManager.objects.size(); i++) {
                    Object* ptr = locationManager.objects.at(i);
                    if (ptr->type == Object::Type::REAL && ptr->x >= (calibratedX - 100) && ptr->x <= (calibratedX + 100) && ptr->y >= (calibratedY -100) && ptr->y <= (calibratedY + 100)) {
                        newBall = false;
                        objectFound = true;
                        ptr->x = calibratedX;
                        ptr->y = calibratedY;
                        ptr->lastUpdated = (clock()/CLOCKS_PER_SEC);
                        break;
                    }
                }
                if (newBall) {
                    long startTime = clock()/CLOCKS_PER_SEC;
                    emit makeObject(calibratedX, calibratedY, startTime);
                    newBall = true;
                }
            } else objectFound = false;
        }
        if(objectFound) {
            drawObjects(originalFrame);
        }
    }
}

cv::Mat robotDetection::detectColors(cv::Mat frame, QString color) {
    if(color == "Red") {
        cv::Mat redDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::RED)->h_low, robotDetectionSettings.HSVColorValues.at(ColorNames::RED)->s_low,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::RED)->v_low),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::RED)->h_high, robotDetectionSettings.HSVColorValues.at(ColorNames::RED)->s_high,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::RED)->v_high), redDetectedColor);
        return redDetectedColor;
    } else if(color == "Green") {
        cv::Mat greenDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN)->h_low, robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN)->s_low,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN)->v_low),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN)->h_high, robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN)->s_high,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::GREEN)->v_high), greenDetectedColor);
        return greenDetectedColor;
    } else if(color == "Blue") {
        cv::Mat blueDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE)->h_low, robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE)->s_low,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE)->v_low),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE)->h_high, robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE)->s_high,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::BLUE)->v_high), blueDetectedColor);
        return blueDetectedColor;
    } else if(color == "Orange") {
        cv::Mat orangeDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::ORANGE)->h_low, robotDetectionSettings.HSVColorValues.at(ColorNames::ORANGE)->s_low,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::ORANGE)->v_low),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::ORANGE)->h_high, robotDetectionSettings.HSVColorValues.at(ColorNames::ORANGE)->s_high,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::ORANGE)->v_high), orangeDetectedColor);
        return orangeDetectedColor;
    } else if(color == "Pink") {
        cv::Mat orangeDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::PINK)->h_low, robotDetectionSettings.HSVColorValues.at(ColorNames::PINK)->s_low,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::PINK)->v_low),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::PINK)->h_high, robotDetectionSettings.HSVColorValues.at(ColorNames::PINK)->s_high,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::PINK)->v_high), orangeDetectedColor);
        return orangeDetectedColor;
    } else if(color == "Yellow") {
        cv::Mat orangeDetectedColor;
        inRange(frame, cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::YELLOW)->h_low, robotDetectionSettings.HSVColorValues.at(ColorNames::YELLOW)->s_low,
                                  robotDetectionSettings.HSVColorValues.at(ColorNames::YELLOW)->v_low),
                cv::Scalar(robotDetectionSettings.HSVColorValues.at(ColorNames::YELLOW)->h_high, robotDetectionSettings.HSVColorValues.at(ColorNames::YELLOW)->s_high,
                           robotDetectionSettings.HSVColorValues.at(ColorNames::YELLOW)->v_high), orangeDetectedColor);
        return orangeDetectedColor;
    }
}

void robotDetection::calculateAngle() {
    for (int i =0;i<locationManager.robots.size(); i++) {
        RobotLocation* ptr = locationManager.robots.at(i);
        if(ptr->type == RobotLocation::Type::REAL) {
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
                        break;  // when multiple blue point are present at a robot. only take the first one
                    }
                }
            }
        }
    }
    bluePoints.clear();
}

void robotDetection::morphOps(cv::Mat &thresh) {
    cv::Mat erodeElement = getStructuringElement(cv::MORPH_RECT, cv::Size(robotDetectionSettings.erodeObject,robotDetectionSettings.erodeObject));
    cv::Mat dilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(robotDetectionSettings.dilateObject,robotDetectionSettings.dilateObject));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
}

void robotDetection::drawRobots(cv::Mat &frame) {
    for(int i =0; i<locationManager.robots.size(); i++) {
        RobotLocation* ptr = locationManager.robots.at(i);
        double uncalibratedXCordinate = ptr->x / (double(globalSettings.fieldSizeX)/double(globalSettings.cameraX));
        double uncalibratedYCordinate = ptr->y / (double(globalSettings.fieldSizeY)/double(globalSettings.cameraY));
        if(ptr->type == RobotLocation::Type::REAL) {
            cv::circle(frame,cv::Point(uncalibratedXCordinate,uncalibratedYCordinate),10,cv::Scalar(0,0,255));
            cv::putText(frame,std::to_string(int(uncalibratedXCordinate))+ " , " + std::to_string(int(uncalibratedYCordinate)),
                        cv::Point(uncalibratedXCordinate,uncalibratedYCordinate),1,1,cv::Scalar(0,255,0));
            std::string str =std::to_string(i);
            cv::putText(frame,str,cv::Point(uncalibratedXCordinate,uncalibratedYCordinate),1,2,cv::Scalar(0,0,255));
        }
    }
}

void robotDetection::drawObjects(cv::Mat &frame) {
    for (int i =0; i<locationManager.objects.size(); i++) {
        Object* ptr = locationManager.objects.at(i);
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

void robotDetection::deleteUndetectedObject() {
    long expiredTime;
    for (int i = 0; i<locationManager.objects.size(); i++) {
        Object* ptr = locationManager.objects.at(i);
        if(ptr->type == Object::Type::REAL)
        {
            expiredTime = ((clock()/CLOCKS_PER_SEC) - ptr->lastUpdated);
            if (expiredTime >= 0.1) {
                locationManager.deleteRealObject(ptr);
                break;
            }
        }
    }
}
