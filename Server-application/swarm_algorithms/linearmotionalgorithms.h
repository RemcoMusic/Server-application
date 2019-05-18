#ifndef LINEARMOTIONALGORITHMS_H
#define LINEARMOTIONALGORITHMS_H

#include <QObject>
#include "swarmalgorithmbase.h"
#include "robotlocationmanager.h"
#include "math.h"
#include <QDebug>
#include <iostream>
#include <QTextStream>
#include <iomanip>
class LinearMotionAlgorithms : public SwarmAlgorithmBase
{
public:

    LinearMotionAlgorithms();
    struct Destination
    {
        int x;
        int y;
        RobotLocation* robot;
    };
    QList<Destination*> destinations;
    void update();

private:
    void connectDestinationsToRobots();
    struct ConnectAlgorithmData
    {
        QList<RobotLocation*> swarmRobots;
        int amountOfDestinations;
        int amountOfRobots;
        uint16_t **distanceTable = nullptr;
        uint8_t *collumnMask;
        uint16_t *rowResult;
        uint8_t *rowResultIndex;
        uint8_t *lastfoundResultIndex;
        uint8_t* rowAvailabilities;
        uint8_t* rowOrder;
        uint16_t lastHighestDistance;
        bool locked = false;
    }data;

    void calculateTable();
    void allocateTable();
    void freeTable();
    bool findPath();
    void resetTempData();
    void printTable();

    void optimizeTable();
    void calculateAvailabilities();
    bool resultIsValid();
    void clearOrder();
    bool optimalisationPossible();
    int getHighestDistance();
    void moveRobotTo(RobotLocation *robot, Destination *destination, double speed);

    int getHighestDistanceOverAll();
};

#endif // LINEARMOTIONALGORITHMS_H
