#include "linearmotionalgorithms.h"

LinearMotionAlgorithms::LinearMotionAlgorithms()
{

}
LinearMotionAlgorithms::~LinearMotionAlgorithms()
{
    data.swarmRobots.clear();
    clearDestinations();
}

//helper functions
//sign returns -1 when a <0 , returns 1 when a >0
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )

void LinearMotionAlgorithms::update()
{
    connectDestinationsToRobots();
    runCollisionAvoidance();
}
void LinearMotionAlgorithms::generateRobotList()
{
    data.swarmRobots.clear();
    QListIterator<RobotLocation*> i(locationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->group == robotGroup)
        {
             data.swarmRobots.append(currentRobot);
        }

    }
}
void LinearMotionAlgorithms::runCollisionAvoidance()
{
    //generateRobotList must run before this(called from derived class), otherwise data.swarmRobots is empty

    //compare all robots with each other
    QListIterator<RobotLocation*> robotIterator1(data.swarmRobots);
    while (robotIterator1.hasNext())
    {
        RobotLocation *robot1 = robotIterator1.next();
        QListIterator<RobotLocation*> robotIterator2(data.swarmRobots);
        robot1->collision = false;
        while (robotIterator2.hasNext())
        {
            RobotLocation *robot2 = robotIterator2.next();

            //don't compare the same robots, don't compare robots 2 times
            if(robot1 == robot2)break;

            //calculate distance from center to center
            int distance = distanceBetweenPoints(robot1->x, robot1->y, robot2->x, robot2->y);
            if(distance < swarmAlgorithmsSettings.collisionDistance)//collision
            {
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

                //if one of the robots is not moved its direction doesn't matter
                if(isMoving(robot1) && (!isMoving(robot2)))
                {
                    if(abs(robot1AngleDifference) < swarmAlgorithmsSettings.collisionAvoidanceAngle)//if avoidance is needed
                    {
                        int sign = sign(robot1AngleDifference);//on which side will we pass
                        double robot1AngleGoal = robot1Angle + sign * swarmAlgorithmsSettings.collisionAvoidanceAngle;
                        robot1->destinationY = robot1->y + sin(robot1AngleGoal) * 1000.0;
                        robot1->destinationX = robot1->x + cos(robot1AngleGoal) * 1000.0;
                    }
                }
                else if(isMoving(robot2) && (!isMoving(robot1)))
                {
                    if(abs(robot2AngleDifference) < swarmAlgorithmsSettings.collisionAvoidanceAngle)//if avoidance is needed
                    {
                        int sign = sign(robot2AngleDifference);//on which side will we pass
                        double robot2AngleGoal = robot2Angle + sign * swarmAlgorithmsSettings.collisionAvoidanceAngle;
                        robot2->destinationY = robot2->y + sin(robot2AngleGoal) * 1000.0;
                        robot2->destinationX = robot2->x + cos(robot2AngleGoal) * 1000.0;
                    }
                }
                else if(isMoving(robot1) && (isMoving(robot2)))
                {
                    if(abs(robot1AngleDifference)+abs(robot2AngleDifference ) < 2*swarmAlgorithmsSettings.collisionAvoidanceAngle)//if avoidance is needed
                    {
                        int sign = sign(robot1AngleDifference);//on which side do they pass
                        double robot1AngleGoal = robot1Angle + sign * swarmAlgorithmsSettings.collisionAvoidanceAngle;
                        robot1->destinationY = robot1->y + sin(robot1AngleGoal) * 1000.0;
                        robot1->destinationX = robot1->x + cos(robot1AngleGoal) * 1000.0;

                        double robot2AngleGoal = robot2Angle + sign * swarmAlgorithmsSettings.collisionAvoidanceAngle;
                        robot2->destinationY = robot2->y + sin(robot2AngleGoal) * 1000.0;
                        robot2->destinationX = robot2->x + cos(robot2AngleGoal) * 1000.0;
                    }
                }
                robot1->collision = true;
                robot2->collision = true;

            }
        }

    }
}

void LinearMotionAlgorithms::allocateData()
{
    //allocated on the heap instead of the stack because the size of the table change

    //the array is 2 demensional, allocate it on the heap
    data.distanceTable = (uint16_t**) malloc(data.amountOfRobots*sizeof(uint16_t*));
    for(int i=0;i<data.amountOfRobots;i++)
        data.distanceTable[i]= (uint16_t *) malloc(data.amountOfDestinations*sizeof(uint16_t));

    //and rowResultIndex
    data.rowResultIndex = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));

    //and lastfoundResultIndex
    data.lastfoundResultIndex = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));
}
void LinearMotionAlgorithms::freeData()
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

void LinearMotionAlgorithms::clearDestinations()
{
    QListIterator<Destination*> destinationIterator(destinations);
    while (destinationIterator.hasNext())
    {
        Destination *currentDestination = destinationIterator.next();
        free(currentDestination);
    }
    destinations.clear();
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
            int rotationTime = 0;
            //rotation time counts the time that the robot have to rotate to the destination as distance, so the riding time will be more realistic and it also works as kind of hysteresis
            if(swarmAlgorithmsSettings.useLineAlgorithmRotationTime)
            {
                //calculate the angles and the time to rotate the robot
                double angleBetween = atan2(currentDestination->y - currentRobot->y, currentDestination->x - currentRobot->x);
                if(angleBetween < 0) angleBetween += 2*M_PI;

                double differenceInAngle = abs(currentRobot->angle - angleBetween);
                differenceInAngle = std::fmin(differenceInAngle, 2*M_PI - differenceInAngle);

                rotationTime = differenceInAngle * swarmAlgorithmsSettings.lineAlgorithmRotationWeight;
            }
            data.distanceTable[robotIndex][destinationIndex] = rotationTime + distanceBetweenPoints(currentDestination->x, currentDestination->y, currentRobot->x, currentRobot->y);
            destinationIndex++;
        }
        robotIndex++;
    }
}
void LinearMotionAlgorithms::optimizeEmptyDestinations()
{
    //when there are more destinations than robots the robots normally would use only the first destinations and let the rest open
    //this function helps to also use that open destinations when the route to them is shorter
    //note that the amount of destinations and robot should be equal because the derived class should handle that

    //first find the used and unused destinations
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
            //if its open
            if(destinationUsed[i] == false)
            {
                //and its more efficient
                if(currentDistance > data.distanceTable[row][i])
                {
                    //swap
                    destinationUsed[i] = true;
                    destinationUsed[data.rowResultIndex[row]] = false;
                    data.rowResultIndex[row] = (uint8_t)i;
                }
            }
        }
    }

}
bool LinearMotionAlgorithms::swap2Rows(int row1, int row2)
{
    bool succes = false;
    uint16_t row1Result = data.distanceTable[row1][data.rowResultIndex[row1]];
    uint16_t row1Alternative = data.distanceTable[row1][data.rowResultIndex[row2]];
    uint16_t row2Result = data.distanceTable[row2][data.rowResultIndex[row2]];;
    uint16_t row2Alternative = data.distanceTable[row2][data.rowResultIndex[row1]];

    int maxNow = std::max(row1Result, row2Result);
    int maxAlternative = std::max(row1Alternative,row2Alternative);

    if(maxAlternative < maxNow)//its more effient to swap
    {
        int temp = data.rowResultIndex[row1];
        data.rowResultIndex[row1] = data.rowResultIndex[row2];
        data.rowResultIndex[row2] = temp;
        if(swarmAlgorithmsSettings.debugLinearMotionVerbose)
        {
            std::cout << "swap optimize" << std::endl;
        }
        succes = true;
    }
    else if(maxAlternative == maxNow)
    {
        int totalNow = row1Result + row2Result;
        int totalAlternative = row1Alternative + row2Alternative;
        if(totalAlternative < totalNow)//its more effient to swap
        {
            int temp = data.rowResultIndex[row1];
            data.rowResultIndex[row1] = data.rowResultIndex[row2];
            data.rowResultIndex[row2] = temp;
            if(swarmAlgorithmsSettings.debugLinearMotionVerbose)
            {
                std::cout << "swap optimize2" << std::endl;
            }
            succes = true;
        }
    }
    if(succes)
    {
        for(int i = 0;i < data.amountOfRobots;i++)
        {
            if(row1 != i)
            {
                swap2Rows(row1, 1);
            }
            if(row2 != i)
            {
                swap2Rows(i,row2);
            }
        }
    }
    return succes;
}

bool LinearMotionAlgorithms::swapOptimize()
{
    //this method compare the distances of rows in the table and looks if its more efficient to swap 2 robots
    //with this method robots will never cross, but it will not alwast give the 100% best solution

    //simply comparing every row to every row, when swapping the 2 rows is better it will swap

    if(swarmAlgorithmsSettings.useAllDestinationsWhenLessRobots)
    {
        if(data.amountOfRobots < data.amountOfDestinations)
        {
            optimizeEmptyDestinations();
        }
    }

    bool succes = false;
    for(int row1=0;row1<data.amountOfRobots-1;row1++)
    {
        for(int row2=row1+1;row2<data.amountOfRobots;row2++)
        {
             succes = swap2Rows(row1, row2);
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
    //complex algorithm to connect the destination points to the robots with the shortest maximal path
    //brute force algorithm has o(n!) complexity, this algorithm works with taking a random combination and optimizing it by swapping combinations with results in 0(n^2)


    data.amountOfRobots = data.swarmRobots.size();
    //if there are more robots than destinations the application may crash, this is a fix for that, points are added if needed
    //this problem should be handled by the derrived class, this is a secondary protection
    int index = 1;
    int xIndex = 1;
    while(data.amountOfRobots > destinations.size())
    {
        Destination* newDestination = new Destination;
        newDestination->x = swarmAlgorithmsSettings.distanceBetweenRobots * xIndex;
        newDestination->y = swarmAlgorithmsSettings.distanceBetweenRobots * index;
        newDestination->endAngle = 0;
        destinations.append(newDestination);
        index++;
        if(index * swarmAlgorithmsSettings.distanceBetweenRobots > globalSettings.fieldSizeY)
        {
            index = 0;
            xIndex++;
        }
    }
    data.amountOfDestinations = destinations.size();


    //make a table with the distances between robots and points
    //this table caches the distances, adding a item from a other thread may cause problems
    allocateData();

    if(swarmAlgorithmsSettings.debugLinearMotionVerbose)
    {
        std::cout << "robots:" << data.amountOfRobots << " destinations:" << data.amountOfDestinations << std::endl;
    }
    //generate the table of distances between all combinations of robots and points
    calculateTable();

    //make the first route, route will be optimized later
    for(int i = 0;i < std::min(data.amountOfRobots,data.amountOfDestinations);i++)
    {
        data.rowResultIndex[i] = i;
    }
    int lowestHighest = UINT16_MAX;//the highest destinance, the lowest when compared to other searches
    for(int i = 0;i < data.amountOfRobots;i++)
    {
        swapOptimize();

        //save the current state
        int highestIndex = getHighestDistanceIndex();
        int highest = data.lastHighestDistance;
        if(highest < lowestHighest)
        {
            memcpy(data.lastfoundResultIndex, data.rowResultIndex, data.amountOfRobots * sizeof(uint8_t));
            lowestHighest = highest;
        }
        //we want to eliminate the longest distance of the found route, try what happens if its being replaced by a very large number,
        //if it fails and the route becomes even longer we have a backup of the last route
        data.distanceTable[highestIndex][data.rowResultIndex[highestIndex]] = UINT16_MAX;

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

    //now set the new destinations to the robot objects
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
                    //when dynamic speed is enables the robots will arrive at the same time
                    double speed;
                    speed = (double)distanceBetweenPoints(currentDestination->x, currentDestination->y,currentDestination->robot->x,currentDestination->robot->y)/data.lastHighestDistance;
                    if(speed >1)
                    {
                        speed = 1;
                    }
                    currentDestination->robot->speed = speed * swarmAlgorithmsSettings.robotSpeed + 1;
                }
                else {
                    currentDestination->robot->speed = swarmAlgorithmsSettings.robotSpeed;
                }

                currentDestination->robot->destinationX = currentDestination->x;
                currentDestination->robot->destinationY = currentDestination->y;
                currentDestination->robot->endAngle = currentDestination->endAngle;
            }
        }
        destinationIndex++;
    }
    //needed for deleting all allocated memory, don't forget this line otherwise we have a memory leak
    freeData();
}
