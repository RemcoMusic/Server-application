#ifndef ROBOTDETECTION_H
#define ROBOTDETECTION_H

#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "robotdetectionsettings.h"
#include "globalsettings.h"
#include "robotlocationmanager.h"
#include "robotlocation.h"
#include <QObject>
#include <QThread>
#include <QtDebug>
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
        void detectNewRobots(cv::Mat threshold, cv::Mat &originalFrame);
        void trackFilteredObject(cv::Mat threshold, cv::Mat &originalFrame);
        void drawObjects(cv::Mat &frame);
        void morphOps(cv::Mat &thresh);
        cv::Mat detectColors(cv::Mat frame, QString color);

    public slots:
        int startDetecting();

    signals:
        void newFrameFinished();
        void makeANewRobot(int x,int y);
};
#endif // ROBOTDETECTION_H
