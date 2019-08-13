#pragma once

#include <QObject>
#include "swarmalgorithmbase.h"
#include "locationmanager.h"
#include "math.h"
#include <iostream>
#include <iomanip>
#include "swarmalgorithmssettings.h"
#include "globalhelperfunctions.h"
class LinearMotionAlgorithms : public SwarmAlgorithmBase
{
public:

    ~LinearMotionAlgorithms();
    //a destination where a robot should go to, the destination is given by a derrived class, this class route robots to the nearest optimal destition
    struct Destination
    {
        int x;
        int y;
        RobotLocation* robot = nullptr;
        double endAngle;
    };
    QList<Destination*> destinations;

    //update called from derrived class
    virtual void update();
    //generates a list of robots that are filtered by the robot group
    void generateRobotList();
protected:
    LinearMotionAlgorithms();

    //the algorithm that find the optimal route in many robots to many destinations routing
    void connectDestinationsToRobots();

    //data needed for the algorithm, some allocated on the heap, don't forget the allocate and free
    struct ConnectAlgorithmData
    {
        QList<RobotLocation*> swarmRobots;
        int amountOfDestinations;
        int amountOfRobots;
        uint16_t **distanceTable = nullptr;
        uint8_t *rowResultIndex;
        uint8_t *lastfoundResultIndex;
        uint16_t lastHighestDistance;
    }data;

    //calculate all distances between robots and destinations, save in in the table
    void calculateTable();

    void allocateData();
    void freeData();
    void clearDestinations();
    void printTable();

    int getHighestDistance();
    int getHighestDistanceOverAll();//uses lastFoundResultIndex
    int getHighestDistanceIndex();

    bool swapOptimize();
    void optimizeEmptyDestinations();

    void runCollisionAvoidance();

private:
    bool swap2Rows(int row1, int row2);
    void collisionAvoidance(Object *object);
};
