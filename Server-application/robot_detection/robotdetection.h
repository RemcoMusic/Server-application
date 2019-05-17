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
        cv::Mat detectColors(cv::Mat frame);

    public slots:
        int detectSomething();

    signals:
        void newFrameFinished();


};

#endif // ROBOTDETECTION_H
