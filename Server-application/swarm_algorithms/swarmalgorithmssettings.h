#ifndef SWARMALGORITHMSSETTINGS_H
#define SWARMALGORITHMSSETTINGS_H

#include <QObject>
#include "swarmalgorithmbase.h"
class SwarmAlgorithmsSettings
{
public:
    SwarmAlgorithmsSettings();

    QList<SwarmAlgorithmBase*> activeAlgorithms;

    int updateIntervalMs=100;

    bool visualisationEnabled = false;
    bool allVisualisationEnabled = false;
    bool experimentalVisualisationEnbaled = false;//for new feature testing

    bool debugLinearMotion = true;
    bool debugLinearMotionVerbose = true;
    bool debugLinearMotionSources = false;

    int distanceBetweenRobots=170;//distance between the destinations of the robots,

    enum class algorithmInputSource
    {
        NONE = 0, //no user input, just a default shape
        ALTERNATIVE_SHAPE = 1, //no user input, just a other size shape
        REAL_OBJECTS = 2, //with objects like red balls
        REAL_AND_SIMULATED_OJECTS = 3, //also allow simulated balls
        HAND_GESTURE = 4, //by hand gestures(hand object)
        ROBOT_MOVEMENT = 5 //by displacing the robot, displaced robot is the orientation for the algorithm
    }inputSource;

    int robotSpeed = 50;//10-100
    bool dynamicSpeed = true; // with dynamic robot speed depents op the other robot, they will arive on the same time
    bool useLineAlgorithmHysteresis = true;
    int lineAlgorithmPerformanceLevel = 5;//0-10;

    bool useAllDestinationsWhenLessRobots = true;

    bool enableCollisionAvoidance = true;
    int collisionDistance = 100;
    int collisionAggression = 5;//0-10

    //en verder
    //update rate
    //kiezen van algorithmes en informatie weergeven

};
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
#endif // SWARMALGORITHMSSETTINGS_H
