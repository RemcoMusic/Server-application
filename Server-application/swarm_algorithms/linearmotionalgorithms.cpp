#include "linearmotionalgorithms.h"
#include "swarmalgorithmssettings.h"

LinearMotionAlgorithms::LinearMotionAlgorithms()
{
}

#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )

inline uint16_t distanceBetweenPoints(int x1, int y1, int x2, int y2)
{
    int deltaX = x1 - x2;//pytagoras A
    int deltaY = y1 - y2;//pytagoras b
    return sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
}

double map(double x, double x1, double x2, double y1, double y2)
{
 return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}
bool isMoving(RobotLocation* robot)
{
    if(distanceBetweenPoints(robot->x,robot->y,robot->destinationX, robot->destinationY) < 50)
    {
        return false;
    }
    if(robot->speed < 0.5)
    {
        return false;
    }
    return true;
}

void LinearMotionAlgorithms::update()
{
    connectDestinationsToRobots();
    runCollisionAvoidance();
}
void LinearMotionAlgorithms::generateRobotList()
{
    data.swarmRobots.clear();
    QListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->group == robotGroup)
        {
            if(currentRobot->type == RobotLocation::RobotType::SIMULATED){
                data.swarmRobots.append(currentRobot);
            }
        }

    }
}
void LinearMotionAlgorithms::runCollisionAvoidance()
{
    //connectDestinationsToRobots must run before this, otherwise data.swarmRobots is empty

    QListIterator<RobotLocation*> robotIterator1(data.swarmRobots);
    while (robotIterator1.hasNext())
    {
        RobotLocation *robot1 = robotIterator1.next();
        QListIterator<RobotLocation*> robotIterator2(data.swarmRobots);
        while (robotIterator2.hasNext())
        {
            RobotLocation *robot2 = robotIterator2.next();

            //don't compare the same robots, don't compare robots 2 times
            if(robot1 == robot2)break;

            //calculate distance from center to center
            int distance = distanceBetweenPoints(robot1->x, robot1->y, robot2->x, robot2->y);
            if(distance < 130)//collision
            {
                robot1->myColor = Qt::green;
                robot2->myColor = Qt::green;
                //calculate the angle between both robots
                double robot1Angle = atan2(robot2->y - robot1->y, robot2->x - robot1->x);
                if(robot1Angle < 0) robot1Angle += 2*M_PI;

                //also calculate it seen from the other robot
                double robot2Angle = robot1Angle - M_PI;
                if(robot2Angle < 0) robot2Angle += 2*M_PI;

                //calculate how much the robot angle differs from the angle between the robots
                double robot1AngleDifference = robot1->angle - robot1Angle;
                if(robot1AngleDifference < 0) robot1AngleDifference += 2 * M_PI;
                if(robot1AngleDifference >  M_PI) robot1AngleDifference -= 2 * M_PI ;

                //calculate it also for the other robot
                double robot2AngleDifference = robot2->angle - robot2Angle;
                if(robot2AngleDifference < 0) robot2AngleDifference += 2 * M_PI;
                if(robot2AngleDifference >  M_PI) robot2AngleDifference -= 2 * M_PI;

                //std::cout << robot1Angle * 57 << "           " <<  robot1AngleDifference *57<< "   "<<robot2AngleDifference *57 << "         "<<robot2Angle * 57<< std::endl;

                if(isMoving(robot1) && (!isMoving(robot2)))
                {
                    robot1->myColor = Qt::blue;
                    if(abs(robot1AngleDifference) < 0.6*M_PI)
                    {
                        int sign = sign(robot1AngleDifference);
                        double robot1AngleGoal = robot1Angle + sign * 0.6*M_PI;
                        robot1->destinationY = robot1->y + sin(robot1AngleGoal) * 1000.0;
                        robot1->destinationX = robot1->x + cos(robot1AngleGoal) * 1000.0;
                    }
                }
                if(isMoving(robot2) && (!isMoving(robot1)))
                {
                    robot2->myColor = Qt::blue;
                    if(abs(robot2AngleDifference) < 0.6*M_PI)
                    {
                        int sign = sign(robot2AngleDifference);
                        double robot2AngleGoal = robot2Angle + sign * 0.6*M_PI;
                        robot2->destinationY = robot2->y + sin(robot2AngleGoal) * 1000.0;
                        robot2->destinationX = robot2->x + cos(robot2AngleGoal) * 1000.0;
                    }
                }
                if(isMoving(robot1) && (isMoving(robot2)))
                {
                    if(abs(robot1AngleDifference)+abs(robot2AngleDifference ) < 1.2*M_PI)
                    {
                        robot1->myColor = Qt::cyan;
                        robot2->myColor = Qt::cyan;
                        int sign = sign(robot1AngleDifference);
                        double robot1AngleGoal = robot1Angle + sign * 0.6*M_PI;
                        robot1->destinationY = robot1->y + sin(robot1AngleGoal) * 1000.0;
                        robot1->destinationX = robot1->x + cos(robot1AngleGoal) * 1000.0;

                        double robot2AngleGoal = robot2Angle + sign * 0.6*M_PI;
                        robot2->destinationY = robot2->y + sin(robot2AngleGoal) * 1000.0;
                        robot2->destinationX = robot2->x + cos(robot2AngleGoal) * 1000.0;
                    }
                }

            }
            else {
                robot1->myColor = Qt::yellow;
                robot2->myColor = Qt::yellow;
            }
        }

    }
}



void LinearMotionAlgorithms::allocateTable()
{
    //the array is 2 demensional, allocate it on the heap
    data.distanceTable = (uint16_t**) malloc(data.amountOfRobots*sizeof(uint16_t*));
    for(int i=0;i<data.amountOfRobots;i++)
        data.distanceTable[i]= (uint16_t *) malloc(data.amountOfDestinations*sizeof(uint16_t));

    //and rowResultIndex
    data.rowResultIndex = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));
    //and lastfoundResultIndex
    data.lastfoundResultIndex = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));

    data.locked = false;
}
void LinearMotionAlgorithms::freeTable()
{
    //delete the 2 dimensional array from the heap
    for(int i=0;i<data.amountOfRobots;i++)
        free(data.distanceTable[i]);
    free(data.distanceTable);
    data.distanceTable = nullptr;

    //rowResultIndex
    free(data.rowResultIndex);
    data.rowResultIndex = nullptr;
    //lastfoundResultIndex
    free(data.lastfoundResultIndex);
    data.lastfoundResultIndex = nullptr;

}
void LinearMotionAlgorithms::calculateTable()
{
    //build a table/matrix with the distance between robots and destinations, destinations on the x-axis, robots on the y-axis
    int robotIndex=0;
    QListIterator<RobotLocation*> robotIterator(data.swarmRobots);
    while (robotIterator.hasNext())
    {
        RobotLocation *currentRobot = robotIterator.next();
        int destinationIndex = 0;
        QListIterator<Destination*> destinationIterator(destinations);
        while (destinationIterator.hasNext())
        {
            Destination *currentDestination = destinationIterator.next();
            data.distanceTable[robotIndex][destinationIndex] = distanceBetweenPoints(currentDestination->x, currentDestination->y, currentRobot->x, currentRobot->y);
            destinationIndex++;
        }
        robotIndex++;
    }
}
void LinearMotionAlgorithms::optimizeEmptyDestinations()
{
    bool destinationUsed[data.amountOfDestinations];
    for(int destination=0;destination<data.amountOfDestinations;destination++)
    {
        destinationUsed[destination] = false;
    }
    for(int row=0;row<data.amountOfRobots;row++)
    {
        destinationUsed[data.rowResultIndex[row]] = true;
    }

    for(int row=0;row<data.amountOfRobots;row++)
    {
        int currentDistance = data.distanceTable[row][data.rowResultIndex[row]];
        for(int i=0;i<data.amountOfDestinations;i++)
        {
            if(destinationUsed[i] == false)
            {
                if(currentDistance > data.distanceTable[row][i])
                {
                    destinationUsed[i] = true;
                    destinationUsed[data.rowResultIndex[row]] = false;
                    data.rowResultIndex[row] = (uint8_t)i;
                }
            }
        }
    }

}
bool LinearMotionAlgorithms::swapOptimize()
{
    //unfortunetly the perfect solution will not alwast be found in the given amount of computing power
    //as result sometimes lines will cross
    //this method is a optimalisation to optimze and find that crossing lines
    //by simply comparing every row to every row, when swapping the 2 rows is better it will swap

    if(swarmAlgorithmsSettings.useAllDestinationsWhenLessRobots)
    {
        if(data.amountOfRobots < data.amountOfDestinations)
        {
            optimizeEmptyDestinations();
        }
    }

    bool succes = false;
    for(int row1=0;row1<data.amountOfRobots;row1++)
    {
        for(int row2=row1;row2<data.amountOfRobots;row2++)
        {
            if(row1 != row2)
            {
                uint16_t row1Result = data.distanceTable[row1][data.rowResultIndex[row1]];
                uint16_t row1Alternative = data.distanceTable[row1][data.rowResultIndex[row2]];
                uint16_t row2Result = data.distanceTable[row2][data.rowResultIndex[row2]];;
                uint16_t row2Alternative = data.distanceTable[row2][data.rowResultIndex[row1]];

                int maxNow = std::max(row1Result, row2Result);
                int maxAlternative = std::max(row1Alternative,row2Alternative);

                if(maxAlternative < maxNow)
                {
                    int temp = data.rowResultIndex[row1];
                    data.rowResultIndex[row1] = data.rowResultIndex[row2];
                    data.rowResultIndex[row2] = temp;
                    if(swarmAlgorithmsSettings.debugLinearMotionVerbose)
                    {
                        std::cout << "swap optimize" << std::endl;
                    }
                    succes = true;
                    row2--;
                }
                else if(maxAlternative == maxNow)
                {
                    int totalNow = row1Result + row2Result;
                    int totalAlternative = row1Alternative + row2Alternative;
                    if(totalAlternative < totalNow)
                    {
                        int temp = data.rowResultIndex[row1];
                        data.rowResultIndex[row1] = data.rowResultIndex[row2];
                        data.rowResultIndex[row2] = temp;
                        if(swarmAlgorithmsSettings.debugLinearMotionVerbose)
                        {
                            std::cout << "swap optimize2" << std::endl;
                        }
                        succes = true;
                        row2--;
                    }
                }
            }
        }
    }

    return succes;
}

void LinearMotionAlgorithms::printTable()
{

    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        for(int destinationIndex = 0; destinationIndex < data.amountOfDestinations; destinationIndex++)
        {
            if(data.distanceTable[robotIndex][destinationIndex] == UINT16_MAX)
            {
                if(data.rowResultIndex[robotIndex] == destinationIndex)
                {
                    std::cout << "\033[1;31m" <<  std::setw(7) << "x" << "\033[0m";
                }
                else {
                    std::cout <<  std::setw(7) << "x";
                }
            }
            else {
                if(data.rowResultIndex[robotIndex] == destinationIndex)
                {
                    std::cout  << "\033[1;31m" <<  std::setw(7)<<data.distanceTable[robotIndex][destinationIndex] << "\033[0m";
                }
                else {
                    std::cout <<  std::setw(7) << data.distanceTable[robotIndex][destinationIndex];
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int LinearMotionAlgorithms::getHighestDistance()
{
    int highest = 0;
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        if(data.distanceTable[robotIndex][data.rowResultIndex[robotIndex]] > highest)
        {
                highest = data.distanceTable[robotIndex][data.rowResultIndex[robotIndex]];
        }
    }
    data.lastHighestDistance = highest;
    return highest;
}
int LinearMotionAlgorithms::getHighestDistanceIndex()
{
    int highest = 0;
    int highestIndex = 0;
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        if(data.distanceTable[robotIndex][data.rowResultIndex[robotIndex]] > highest)
        {
           highest = data.distanceTable[robotIndex][data.rowResultIndex[robotIndex]];
           highestIndex = robotIndex;
        }
    }
    data.lastHighestDistance = highest;
    return highestIndex;
}
void LinearMotionAlgorithms::connectDestinationsToRobots()
{
    //std::cout << "connect destinations to robots algorithm" << std::endl;
    //complex algorithm to connect the destination points to the robots with the shortest maximal path
    //brute force algorithm has o(n!) complexity, this algorithm works with taking a random combination and optimizing it by swapping combinations




    data.amountOfRobots = data.swarmRobots.size();
    //if there are more robots than destinations the application may crash, this is a fix for that, points are added if needed
    //this problem should be handled by the derrived class, this is a second protection
    int index = 0;
    while(data.amountOfRobots > destinations.size())
    {
        Destination* newDestination = new Destination;
        newDestination->x = swarmAlgorithmsSettings.distanceBetweenRobots/2;
        newDestination->y = swarmAlgorithmsSettings.distanceBetweenRobots * index;
        destinations.append(newDestination);
        index++;
    }
    data.amountOfDestinations = destinations.size();

    //make a table with the distances between robots and points
    //this table caches the distances, adding a item from a other thread may cause problems
    allocateTable();

    if(swarmAlgorithmsSettings.debugLinearMotionVerbose)
    {
        std::cout << "robots:" << data.amountOfRobots << " destinations:" << data.amountOfDestinations << std::endl;
    }
    //generate the table of distances between all combinations of robots and points
    calculateTable();

    for(int i = 0;i < std::min(data.amountOfRobots,data.amountOfDestinations);i++)
    {
        data.rowResultIndex[i] = i;
    }

    int lowestHighest=UINT16_MAX;
    for(int i=0;i<5;i++)
    {
        while(swapOptimize());

        int highestIndex = getHighestDistanceIndex();
        int highest = data.lastHighestDistance;
        if(highest < lowestHighest)
        {
            memcpy(data.lastfoundResultIndex, data.rowResultIndex, data.amountOfRobots * sizeof(uint8_t));
            lowestHighest = highest;
        }
        data.distanceTable[highestIndex][data.rowResultIndex[highestIndex]] = UINT16_MAX;


        while(swapOptimize());
        if(swarmAlgorithmsSettings.debugLinearMotion)
        {
            std::cout << highest << "  "<< getHighestDistance()<< std::endl;
        }
    }
    if(swarmAlgorithmsSettings.debugLinearMotion)
    {
        printTable();
    }
    data.lastHighestDistance = lowestHighest;

    int destinationIndex=0;
    QListIterator<Destination*> destinationIterator(destinations);
    while (destinationIterator.hasNext())
    {
        Destination *currentDestination = destinationIterator.next();
        for(int i=0;i<data.amountOfRobots;i++)
        {
            if(data.lastfoundResultIndex[i] == destinationIndex)
            {
                currentDestination->robot = data.swarmRobots[i];

                if(swarmAlgorithmsSettings.dynamicSpeed)
                {
                    double speed;
                    speed = (double)distanceBetweenPoints(currentDestination->x, currentDestination->y,currentDestination->robot->x,currentDestination->robot->y)/data.lastHighestDistance;
                    if(speed >1)
                    {
                        speed = 1;
                    }
                    currentDestination->robot->speed = speed * 6 + 1;
                }
                else {
                    currentDestination->robot->speed = 6;
                }

                currentDestination->robot->destinationX = currentDestination->x;
                currentDestination->robot->destinationY = currentDestination->y;
            }
        }
        destinationIndex++;
    }
    //needed for deleting all allocated memory, don't forget this line otherwise we have a memory leak
    freeTable();

}
