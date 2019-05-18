#include "linearmotionalgorithms.h"

LinearMotionAlgorithms::LinearMotionAlgorithms()
{
}
inline int distanceBetweenPoints(LinearMotionAlgorithms::Destination* destination1, double x, double y)
{
    int deltaX = abs(destination1->x - x);//pytagoras A
    int deltaY = abs(destination1->y - y);//pytagoras b
    int c = sqrt(deltaX*deltaX + deltaY*deltaY);//pytagoras C, distance between points
    return c;
}

void LinearMotionAlgorithms::update()
{
    connectDestinationsToRobots();

}
void LinearMotionAlgorithms::allocateTable()
{
    //the array is 2 demensional, allocate it on the heap
    data.distanceTable =(uint16_t**) malloc(data.amountOfRobots*sizeof(uint16_t *));
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
void LinearMotionAlgorithms::calculateAvailabilities()
{
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        int available = 0;
        for(int destinationIndex = 0; destinationIndex < data.amountOfDestinations; destinationIndex++)
        {
            if(data.distanceTable[robotIndex][destinationIndex] != UINT16_MAX)
            {
                available++;
            }
        }
        data.rowAvailabilities[robotIndex] = available;
    }
}
bool LinearMotionAlgorithms::findPath()
{
    for(int currentAmountOfAvailabilities = 1; currentAmountOfAvailabilities <= data.amountOfRobots; currentAmountOfAvailabilities++)
    {
        for(int currentOrder = 4; currentOrder >=0; currentOrder--)
        {
            int lastRobotIndex = 0;
            for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
            {

                if((data.rowAvailabilities[robotIndex] == currentAmountOfAvailabilities) && (currentOrder == data.rowOrder[robotIndex]))
                {
                    uint16_t lowest = UINT16_MAX;
                    int lowestIndex = 0;
                    int collumsOpen = 0;
                    for(int destinationIndex = 0; destinationIndex < data.amountOfDestinations; destinationIndex++)
                    {
                        if(data.collumnMask[destinationIndex] == 0)
                        {
                            collumsOpen++;
                            uint16_t distance = data.distanceTable[robotIndex][destinationIndex];
                            if(distance < lowest)
                            {
                                lowestIndex = destinationIndex;
                                lowest = distance;
                            }
                        }
                    }

                    if(lowest == UINT16_MAX)
                    {

                        if(data.rowOrder[robotIndex] >= data.rowAvailabilities[robotIndex])
                        {
                           data.locked = true;
                        }

                        for(int destinationIndex = 0; destinationIndex < data.amountOfDestinations; destinationIndex++)
                        {
                            uint16_t distance = data.distanceTable[robotIndex][destinationIndex];
                            if(distance < lowest)
                            {
                                lowestIndex = destinationIndex;
                                lowest = distance;
                            }

                        }
                        for(int i=0;i<data.amountOfRobots;i++)
                        {
                            if(data.rowResultIndex[i] == lowestIndex)
                            {
                                if(data.rowAvailabilities[i] == data.rowAvailabilities[robotIndex])
                                {
                                    data.rowOrder[robotIndex]++;
                                }
                                else {
                                    data.rowOrder[robotIndex]++;
                                    data.rowOrder[i]++;
                                }
                                break;
                            }
                        }

                        return false;
                    }
                    else if(collumsOpen==0)
                    {
                        return false;
                    }
                    else {
                        data.collumnMask[lowestIndex] = 1;
                        data.rowResult[robotIndex] = lowest;
                        data.rowResultIndex[robotIndex] = lowestIndex;
                    }
                    lastRobotIndex = robotIndex;

                }
            }
        }
    }
    return true;
}
void LinearMotionAlgorithms::optimizeTable()
{
    int longestPath = 0;
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        if(data.rowResult[robotIndex] > longestPath)
        {
            longestPath = data.rowResult[robotIndex];
        }
    }
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {

            for(int destinationIndex = 0; destinationIndex < data.amountOfDestinations; destinationIndex++)
            {
                if((data.distanceTable[robotIndex][destinationIndex] > longestPath) && (data.distanceTable[robotIndex][destinationIndex] != UINT16_MAX))
                {
                    if(data.rowAvailabilities[robotIndex] >  1)
                    {
                        data.distanceTable[robotIndex][destinationIndex] = UINT16_MAX;
                        data.rowAvailabilities[robotIndex]--;
                    }
                }
            }
            for(int destinationIndex = 0; destinationIndex < data.amountOfDestinations; destinationIndex++)
            {
                if(data.distanceTable[robotIndex][destinationIndex] == longestPath)
                {
                    if(data.rowAvailabilities[robotIndex] >  1)
                    {
                        data.distanceTable[robotIndex][destinationIndex] = UINT16_MAX;
                        data.rowAvailabilities[robotIndex]--;
                    }
                }
            }
    }
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
        std::cout <<"   |   " << data.rowResult[robotIndex] << "        "<< (int)data.rowAvailabilities[robotIndex] << "   - " << (int)data.rowOrder[robotIndex] << "    " << (int)data.rowResultIndex[robotIndex]<<std::endl;
    }
    std::cout << std::endl;
}
bool LinearMotionAlgorithms::resultIsValid()
{
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        if(data.rowResult[robotIndex] == UINT16_MAX)
        {
            return false;
        }
    }
    return true;
}
int LinearMotionAlgorithms::getHighestDistance()
{
    int highest = 0;
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        if(data.rowResult[robotIndex] > highest)
        {
            if(data.rowAvailabilities[robotIndex] > 1)
            {
                highest = data.rowResult[robotIndex];
            }
        }
    }
    return highest;
}
int LinearMotionAlgorithms::getHighestDistanceOverAll()
{
    int highest = 0;
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        if(data.rowResult[robotIndex] > highest)
        {
            highest = data.rowResult[robotIndex];
        }
    }
    return highest;
}
bool LinearMotionAlgorithms::optimalisationPossible()
{
    int highest = getHighestDistance();
    for(int robotIndex = 0; robotIndex < data.amountOfRobots; robotIndex++)
    {
        if(data.rowResult[robotIndex] == highest)
        {
            if(data.rowAvailabilities[robotIndex] == 1)
            {
                return false;
            }
        }
    }
    return true;
}
void LinearMotionAlgorithms::resetTempData()
{
    //reset values after one table calculation
    //todo: make more efficient with memset

    memset(data.collumnMask,0,data.amountOfDestinations * sizeof(uint8_t));
}
void LinearMotionAlgorithms::clearOrder()
{
    memset(data.rowOrder,0,data.amountOfRobots * sizeof(uint8_t));
}
void LinearMotionAlgorithms::connectDestinationsToRobots()
{
    std::cout << "connect destinations to robots algorithm" << std::endl;
    //complex algorithm to connect the destination points to the robots with the shortest maximal path
    //brute force algorithm has o(n!) complexity, this algorithm works with elemination combinations

    //first make list of robots of this specific group
    data.swarmRobots.clear();
    QListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->group == robotGroup)
        {
            data.swarmRobots.append(currentRobot);
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

    for(int i=0;i<10;i++)
    {
        resetTempData();
        calculateAvailabilities();
        bool pathfound = findPath();
        if(pathfound)
        {
            data.lastHighestDistance = getHighestDistanceOverAll();
            memcpy(data.lastfoundResultIndex, data.rowResultIndex, data.amountOfRobots * sizeof(uint8_t));
            if(!optimalisationPossible())
            {
                break;
            }
            clearOrder();
            optimizeTable();
        }
        if(data.locked)
        {
            break;
        }
        printTable();
    }
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
                currentDestination->robot = data.swarmRobots.at(i);
                if(currentDestination->robot == nullptr)
                {
                    std::cout << "nullptr" << std::endl;
                }
                else {
                    double speed;
                    speed = (double)distanceBetweenPoints(currentDestination,currentDestination->robot->x,currentDestination->robot->y)/data.lastHighestDistance;
                    if(speed >1)
                    {
                        speed = 1;
                    }
                    moveRobotTo(currentDestination->robot,currentDestination, speed);

                }
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
    if(deltaX <= 1 && deltaY <= 1)return;
    double angle = atan2(deltaY,deltaX);
    double newX = robot->x + cos(angle) * speed * 2;
    double newY = robot->y + sin(angle) * speed * 2;
    robot->x = newX;
    robot->y = newY;
}


