#ifndef SWARMSIMULATION_H
#define SWARMSIMULATION_H

#include <QObject>
#include <QDebug>
#include "robotlocation.h"
#include "robotlocationmanager.h"
#include <QThread>
extern RobotLocationManager robotLocationManager;
class SwarmSimulation: public QObject
{
    Q_OBJECT
public:
    SwarmSimulation();
public slots:
    void startSimulation();
signals:
    void simulationFinished();
};

#endif // SWARMSIMULATION_H
