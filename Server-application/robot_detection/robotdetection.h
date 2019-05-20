#ifndef ROBOTDETECTION_H
#define ROBOTDETECTION_H

#include <QObject>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <QThread>
#include "robotdetectionsettings.h"
#include "globalsettings.h"


class robotDetection: public QThread
{
    Q_OBJECT

    public:
        robotDetection();
        void run();
    private:
        void trackFilteredObject(cv::Mat threshold,cv::Mat HSV, cv::Mat &originalFrame);
        void drawObjects(cv::Mat &frame);
        void morphOps(cv::Mat &thresh);
        cv::Mat detectColors(cv::Mat frame);

        QList<QString> robotList;
        QList<int> robotXcoordinates;
        QList<int> robotYcoordinates;

        cv::Mat redColorFrame;
        cv::Mat blueColorFrame;
        cv::Mat greenColorFrame;

    public slots:
        int detectSomething();

    signals:
        void newFrameFinished();
};

#endif // ROBOTDETECTION_H
