#include "robotdetection.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

robotDetection::robotDetection()
{
    detectSomething();
}

int robotDetection::detectSomething()
{
    VideoCapture cap(0);
    Mat imgTmp;
    cap.read(imgTmp);
    Mat imgLines = Mat::zeros(imgTmp.size(),CV_8UC3);
    int lastX = -1;
    int lastY = -1;

    if(!cap.isOpened()) {
        return -1;
    }

    for(;;) {
        Mat originalFrame;
        Mat hsvFrame;
        Mat thresholdedFrame;

        cap >> originalFrame;

        cvtColor(originalFrame, hsvFrame, COLOR_BGR2HSV);

        inRange(hsvFrame, Scalar(110, 50, 50), Scalar(130, 255, 255), thresholdedFrame);


        erode(thresholdedFrame, thresholdedFrame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(thresholdedFrame, thresholdedFrame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        erode(thresholdedFrame, thresholdedFrame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(thresholdedFrame, thresholdedFrame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        Moments oMoments = moments(thresholdedFrame);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        if (dArea > 10000) {
          int posX = dM10 / dArea;
          int posY = dM01 / dArea;

          if (lastX >= 0 && lastY >= 0 && posX >= 0 && posY >= 0) {
           line(imgLines, Point(posX, posY), Point(lastX, lastY), Scalar(0,0,255), 2);
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

        if(waitKey(30) >= 0) break;
    }
    return 0;
}
