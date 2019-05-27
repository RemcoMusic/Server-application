#ifndef LINEARMOTIONALGORITHMS_H
#define LINEARMOTIONALGORITHMS_H

#include <QObject>
#include "swarmalgorithmbase.h"
#include "robotlocationmanager.h"
#include "math.h"
#include <iostream>
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
        double endAngle;
    };
    QList<Destination*> destinations;
    void update();

    void generateRobotList();
protected:
    void connectDestinationsToRobots();
    struct ConnectAlgorithmData
    {
        QList<RobotLocation*> swarmRobots;
        int amountOfDestinations;
        int amountOfRobots;
        uint16_t **distanceTable = nullptr;
        uint8_t *rowResultIndex;
        uint8_t *lastfoundResultIndex;
        uint16_t lastHighestDistance;
        bool locked = false;
    }data;

    void calculateTable();
    void allocateTable();
    void freeTable();
    void printTable();

    int getHighestDistance();

    int getHighestDistanceOverAll();
    void filterPointAvailabilities();
    bool swapOptimize();
    int getHighestDistanceIndex();
    void runCollisionAvoidance();

    void optimizeEmptyDestinations();
};

#endif // LINEARMOTIONALGORITHMS_H
