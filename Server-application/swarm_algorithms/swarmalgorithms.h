#pragma once

#include <QObject>

#include "algrorithmvisualisation.h"
#include "robotdisplacementdetection.h"
#include "swarmalgorithmssettings.h"
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;

class SwarmAlgorithms: public QObject
{
    Q_OBJECT
public:
    SwarmAlgorithms();
private:
    RobotDisplacementDetection robotDisplacementDetection;
public slots:
    void update();
signals:
    void algoritmFinished();
};

