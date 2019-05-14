#ifndef ROBOTDETECTION_H
#define ROBOTDETECTION_H

#include <QObject>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class robotDetection
{
    public:
        robotDetection();
        int detectSomething();
};

#endif // ROBOTDETECTION_H
