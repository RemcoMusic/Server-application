#ifndef ROBOTDETECTION_H
#define ROBOTDETECTION_H

#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "robotdetectionsettings.h"
#include "globalsettings.h"
#include "locationmanager.h"
#include "robotlocation.h"
#include <math.h>
#include <QObject>
#include <QThread>
#include <QList>
#include <QPoint>
#include <QtDebug>
#include <QTimer>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class robotDetection: public QThread
{
    Q_OBJECT

    public:
        robotDetection();
        void run();

    private:
        void detectNewRobots(cv::Mat threshold);
        void trackFilteredObject(cv::Mat threshold, cv::Mat &originalFrame);
        void detectBlueDots(cv::Mat threshold);
        void detectBall(cv::Mat threshold, cv::Mat &originalFrame);
        void calculateAngle();
        void drawRobots(cv::Mat &frame);
        void drawObjects(cv:: Mat &frame);
        void morphOps(cv::Mat &thresh);
        cv::Mat detectColors(cv::Mat frame, QString color);

        int oldCameraInput = robotDetectionSettings.selectCamera;

        QList<QPoint> bluePoints;

    public slots:
        void startDetecting();

    signals:
        void newFrameFinished();
        void makeANewRobot(int x,int y);
        void makeObject(int x, int y, int i);
};
#endif // ROBOTDETECTION_H
