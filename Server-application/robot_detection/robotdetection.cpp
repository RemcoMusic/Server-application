#include "robotdetection.h"




robotDetection::robotDetection()
{
    //detectSomething();


}

void robotDetection::run()
{
    detectSomething(); //make sure it has an infinite loop
}

int robotDetection::detectSomething()
{
    cv::VideoCapture cap(0);
    cv::Mat imgTmp;
    cap.read(imgTmp);
    cv::Mat imgLines = cv::Mat::zeros(imgTmp.size(),CV_8UC3);
    int lastX = -1;
    int lastY = -1;

    if(!cap.isOpened()) {
        return -1;
    }

    for(;;) {
        cv::Mat originalFrame;
        cv::Mat hsvFrame;
        cv::Mat thresholdedFrame;

        cap >> originalFrame;

        cvtColor(originalFrame, hsvFrame, cv::COLOR_BGR2HSV);

        inRange(hsvFrame, cv::Scalar(110, 50, 50), cv::Scalar(130, 255, 255), thresholdedFrame);


        erode(thresholdedFrame, thresholdedFrame, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        dilate(thresholdedFrame, thresholdedFrame, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        erode(thresholdedFrame, thresholdedFrame, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        dilate(thresholdedFrame, thresholdedFrame, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        cv::Moments oMoments = moments(thresholdedFrame);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        if (dArea > 10000) {
          int posX = dM10 / dArea;
          int posY = dM01 / dArea;

          if (lastX >= 0 && lastY >= 0 && posX >= 0 && posY >= 0) {
           line(imgLines, cv::Point(posX, posY), cv::Point(lastX, lastY), cv::Scalar(0,0,255), 2);
          }
          lastX = posX;
          lastY = posY;
          if(lastX != 0) {
              qDebug("%s :%d","Coördinates X", lastX);
              qDebug("%s :%d","Coördinates Y", lastY);
          }
        }

        originalFrame = originalFrame + imgLines;
        imshow("Color detection", originalFrame);

        emit newFrameFinished();
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;
}
