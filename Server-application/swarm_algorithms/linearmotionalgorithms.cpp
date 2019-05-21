#include "linearmotionalgorithms.h"

LinearMotionAlgorithms::LinearMotionAlgorithms()
{
}
inline int distanceBetweenPoints(LinearMotionAlgorithms::Destination* destination1, double x, double y)
{
    int deltaX = destination1->x - x;//pytagoras A
    int deltaY = destination1->y - y;//pytagoras b
    return sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
}

void LinearMotionAlgorithms::update()
{
    connectDestinationsToRobots();
}
void LinearMotionAlgorithms::allocateTable()
{
    //the array is 2 demensional, allocate it on the heap
    data.distanceTable = (uint16_t**) malloc(data.amountOfRobots*sizeof(uint16_t*));
    for(int i=0;i<data.amountOfRobots;i++)
        data.distanceTable[i]= (uint16_t *) malloc(data.amountOfDestinations*sizeof(uint16_t));
    //also allocate collumn mask array
    data.collumnMask = (uint8_t*)malloc(data.amountOfDestinations * sizeof (uint8_t));
    //and rowResult
    data.rowResult = (uint16_t*)malloc(data.amountOfRobots * sizeof (uint16_t));
    //and rowResultIndex
    data.rowResultIndex = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));
    //and lastfoundResultIndex
    data.lastfoundResultIndex = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));
    //and row availablitities
    data.rowAvailabilities = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));

    //and rowOrder
    data.rowOrder = (uint8_t*)malloc(data.amountOfRobots * sizeof (uint8_t));
    for(int i=0;i<data.amountOfRobots;i++)
    {
        data.rowOrder[i] = 0;
    }
    data.locked = false;
}
void LinearMotionAlgorithms::freeTable()
{
    //delete the 2 dimensional array from the heap
    for(int i=0;i<data.amountOfRobots;i++)
        free(data.distanceTable[i]);
    free(data.distanceTable);
    data.distanceTable = nullptr;
    //also free collumn mask array
    free(data.collumnMask);
    data.collumnMask = nullptr;
    //and rowResult
    free(data.rowResult);
    data.rowResult = nullptr;
    //rowResultIndex
    free(data.rowResultIndex);
    data.rowResultIndex = nullptr;
    //lastfoundResultIndex
    free(data.lastfoundResultIndex);
    data.lastfoundResultIndex = nullptr;

    //and rowAvailabilities
    free(data.rowAvailabilities);
    data.rowAvailabilities = nullptr;

    //row order
    free(data.rowOrder);
    data.rowOrder = nullptr;

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
            data.distanceTable[robotIndex][destinationIndex] = distanceBetweenPoints(currentDestination, currentRobot->x, currentRobot->y);
            std::cout <<  std::setw(7) << data.distanceTable[robotIndex][destinationIndex];

            destinationIndex++;
        }
        std::cout << std::endl;
        robotIndex++;
    }
    std::cout << std::endl;
}


bool LinearMotionAlgorithms::swapOptimize()
{
    //unfortunetly the perfect solution will not alwast be found in the given amount of computing power
    //as result sometimes lines will cross
    //this method is a optimalisation to optimze and find that crossing lines
    //by simply comparing every row to every row, when swapping the 2 rows is better it will swap

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
                    std::cout << "swap optimize" << std::endl;
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
                        std::cout << "swap optimize" << std::endl;
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
    std::cout << "connect destinations to robots algorithm" << std::endl;
    //complex algorithm to connect the destination points to the robots with the shortest maximal path
    //brute force algorithm has o(n!) complexity, this algorithm works with elemination combinations

    //first make list of robots of this specific group
    data.swarmRobots.clear();
    {
        QListIterator<RobotLocation*> i(robotLocationManager.robots);
        while (i.hasNext())
        {
            RobotLocation *currentRobot = i.next();
            if(currentRobot->group == robotGroup)
            {
                data.swarmRobots.append(currentRobot);
            }
        }
        QListIterator<Destination*> destinationIterator(destinations);
        while (destinationIterator.hasNext())
        {
            destinationIterator.next()->robot = nullptr;
        }
    }
    //make a table with the distances between robots and points
    //this table caches the distances, adding a item from a other thread may cause problems
    data.amountOfDestinations = destinations.size();
    data.amountOfRobots = data.swarmRobots.size();

    allocateTable();

    std::cout << "size" << data.amountOfRobots << " " << data.amountOfDestinations << std::endl;

    //generate the table of distances between all combinations of robots and points
    calculateTable();

    for(int i=0;i<data.amountOfRobots;i++)
    {
        data.rowResultIndex[i] = i;
    }
    int lowestHighest=UINT16_MAX;
    for(int i=0;i<5;i++)
    {
        std::cout << i << std::endl;
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
        std::cout << highest << "  "<< getHighestDistance()<< std::endl;
        if(getHighestDistance() <= highest)
        {

        }
        else {

        }
    }

    printTable();
    data.lastHighestDistance = lowestHighest;


    std::cout << "best path found" << std::endl;
    for(int i=0;i<data.amountOfRobots;i++)
    {
        std::cout << (int)data.lastfoundResultIndex[i] << "  ";
    }std::cout << std::endl << data.lastHighestDistance << std::endl;

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

                double speed;
                speed = (double)distanceBetweenPoints(currentDestination,currentDestination->robot->x,currentDestination->robot->y)/data.lastHighestDistance;
                if(speed >1)
                {
                    speed = 1;
                }
                moveRobotTo(currentDestination->robot,currentDestination, speed);
            }
        }
        destinationIndex++;
    }
    //needed for deleting all allocated memory, don't forget this line otherwise we have a memory leak
    freeTable();

}
void LinearMotionAlgorithms::moveRobotTo(RobotLocation *robot,Destination *destination, double speed)
{
    double deltaX = destination->x - robot->x;
    double deltaY = destination->y - robot->y;
    if((abs(deltaX) <= 1) && (abs(deltaY) <= 1))return;
    double angle = atan2(deltaY,deltaX);
    robot->x = robot->x + std::fmin(cos(angle) * speed * 4, abs(deltaX));
    robot->y = robot->y + std::fmin(sin(angle) * speed * 4, abs(deltaY));
    robot->setRotation(angle*57 + 90);
}


