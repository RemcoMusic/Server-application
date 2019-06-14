#pragma once
#include <QObject>
#include "swarmalgorithmbase.h"
#include <math.h>
#include <QList>
#include <QString>


class SwarmAlgorithmsSettings
{
public:
    SwarmAlgorithmsSettings();

    QList<SwarmAlgorithmBase*> activeAlgorithms;

    int updateIntervalMs=100;  //3

    bool visualisationEnabled = false;  // 2
    bool allVisualisationEnabled = false;  //2
    bool experimentalVisualisationEnbaled = false;//for new feature testing  //2

    bool debugLinearMotion = false;  //2
    bool debugLinearMotionVerbose = false; //2
    bool debugLinearMotionSources = false; //2

    int distanceBetweenRobots = 120;//distance between the destinations of the robots, //1

    //can be chosen in the ui, when changing this list the ui list must also be changed
    enum class AlgorithmInputSource
    {
        NONE = 0, //only distanceBetweenRobots as user input
        OBJECTS = 1, //with objects like red balls
        ROBOT_MOVEMENT = 2, //by displacing the robot, displaced robot is the orientation for the algorithm
        ROBOT_MOVEMENT_WITH_ANGLE = 3 //by displacing the robot, displaced robot is the orientation for the algorithm
    }inputSource = AlgorithmInputSource::NONE;

    bool algorithmAllowSimulatedObject = true;    //1

    int robotSpeed = 5;//10-100  //1
    bool dynamicSpeed = true; // with dynamic robot speed depents on the other robot, they will arive on the same time //1
    bool useLineAlgorithmRotationTime = true;  //2
    int lineAlgorithmRotationWeight = 10;      //2

    bool useAllDestinationsWhenLessRobots = true;  //2

    bool enableCollisionAvoidance = true;   //1
    int collisionDistance = 20;            //1
    int collisionAggression = 5;//0-10      //1
    double collisionAvoidanceAngle = 0.6 * M_PI;

    double batteryVoltageThreshold = 6.0;
    double batteryVoltageFull = 8.4;

    int displacementKeepTimeMS = 1000;
    double dispacementComplementeryFilter = 0.95;//0.8 - 0.99
    //en verder
    //update rate
    //kiezen van algorithmes en informatie weergeven




    QList<QString> anvailableAlgoritms;
    void runNewAlgortim(QString newAlgoritm, bool clearOthers = true);

};
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
