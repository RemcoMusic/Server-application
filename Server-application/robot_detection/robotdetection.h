#ifndef ROBOTDETECTION_H
#define ROBOTDETECTION_H

#include <QObject>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <QThread>


class robotDetection: public QThread
{
    Q_OBJECT

    public:
        robotDetection();
        void run();

    public slots:
        int detectSomething();

    signals:
        void newFrameFinished();


};

#endif // ROBOTDETECTION_H
