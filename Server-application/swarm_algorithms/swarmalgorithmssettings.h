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

    enum class AlgorithmInputSource
    {
        NONE = 0, //only distanceBetweenRobots as user input
        REAL_OBJECTS_CENTER_OUTER = 1, //with objects like red balls
        REAL_OBJECTS_OUTER_OUTER = 2, //with objects like red balls
        HAND_GESTURE = 3, //by hand gestures(hand object)
        ROBOT_MOVEMENT = 4, //by displacing the robot, displaced robot is the orientation for the algorithm
        ROBOT_MOVEMENT_WITH_ANGLE = 5 //by displacing the robot, displaced robot is the orientation for the algorithm
    }inputSource = AlgorithmInputSource::NONE;

    bool algorithmAllowSimulatedObject = true;    //1

    int robotSpeed = 5;//10-100  //1
    bool dynamicSpeed = true; // with dynamic robot speed depents on the other robot, they will arive on the same time //1
    bool useLineAlgorithmRotationTime = true;  //2
    int lineAlgorithmRotationWeight = 10;      //2

    bool useAllDestinationsWhenLessRobots = true;  //2

    bool enableCollisionAvoidance = true;   //1
    int collisionDistance = 100;            //1
    int collisionAggression = 5;//0-10      //1
    double collisionAvoidanceAngle = 0.6 * M_PI;
    //en verder
    //update rate
    //kiezen van algorithmes en informatie weergeven




    QList<QString> anvailableAlgoritms;
    void runNewAlgortim(QString newAlgoritm);

};
extern SwarmAlgorithmsSettings swarmAlgorithmsSettings;
