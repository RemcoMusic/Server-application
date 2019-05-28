#include "swarmsimulation.h"
#include "swarmsimulationsettings.h"


#define toRad(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define toDeg(angleRadians) ((angleRadians) * 180.0 / M_PI)
SwarmSimulation::SwarmSimulation()
{

}
static double map(double x, double x1, double x2, double y1, double y2)
{
 return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}
void SwarmSimulation::moveRobot(RobotLocation *robot)
{
    double deltaX = robot->destinationX - robot->x;
    double deltaY = robot->destinationY - robot->y;

    double goalAngle;
    if((abs(deltaX) <= 10) && (abs(deltaY) <= 10))
    {
        goalAngle = robot->endAngle;
    }
    else
    {
         goalAngle = atan2(deltaY,deltaX);
    }



    if(robot->angle >  M_PI)robot->angle -= 2* M_PI;
    if(robot->angle < -M_PI)robot->angle+= 2 * M_PI;

    double difference = robot->angle - goalAngle;
    if(difference >  M_PI)difference -= 2* M_PI;
    if(difference < -M_PI)difference += 2 * M_PI;
//    if(abs(difference) > 0.6 * M_PI)//0.6 is added for hysteresis
//    {
//        robot->angle += M_PI;
//    }
    if(difference > 0.1)
    {
        robot->angle -= std::min(robot->angle - goalAngle, 0.1);
    }
    else if(difference < -0.1)
    {
        robot->angle += std::min(goalAngle - robot->angle, 0.1);
    }

    if((abs(deltaX) <= 10) && (abs(deltaY) <= 10))
    {

    }
    else {
        if(abs(difference) < 0.5)
        {
            robot->x = robot->x + std::fmin(cos(goalAngle) * robot->speed * swarmSimulationSettings.maxSpeed, abs(deltaX));
            robot->y = robot->y + std::fmin(sin(goalAngle) * robot->speed * swarmSimulationSettings.maxSpeed, abs(deltaY));
        }
    }

    while(robot->angle >= 2 * M_PI) robot->angle -=2 * M_PI;
    while(robot->angle < 0) robot->angle +=2 * M_PI;

}
void SwarmSimulation::moveRobotRealistic(RobotLocation *robot)
{
    double deltaX = robot->destinationX - robot->x;
    double deltaY = robot->destinationY - robot->y;
    double goalAngle;
    bool onLocation=false;
    double distanceFromDestination = sqrt(deltaX*deltaX + deltaY*deltaY);//pythogoras
    if((abs(deltaX) <= 10) && (abs(deltaY) <= 10))//already on location
    {
        goalAngle = robot->endAngle;
        onLocation = true;
    }
    else {
        goalAngle = atan2(deltaY,deltaX);
    }

    while(goalAngle <0) goalAngle += M_PI * 2;
    double currentAngle = robot->angle;
    while(currentAngle < 0) currentAngle += M_PI * 2;

    double difference = currentAngle - goalAngle;
    if(difference > M_PI)difference -= 2* M_PI;
    if(difference < -M_PI)difference += 2 * M_PI;
    if(!onLocation)
    {
        if(abs(difference) > 0.6 * M_PI)//0.6 is added for hysteresis
        {
            robot->angle += M_PI;
        }
    }
    while(currentAngle >= 2*M_PI) currentAngle -= M_PI * 2;

    double left = 0;
    double right = 0;
    if(onLocation)
    {
        double maxSpeed = map(difference,0,2 * M_PI,robot->speed/2,robot->speed);
        if(difference > 0)
        {
            left = maxSpeed;
            right = -maxSpeed;
        }
        else {
            left = -maxSpeed;
            right = maxSpeed;
        }
    }
    else
    {
        int maxSpeed = robot->speed;
        if(distanceFromDestination < 100)
        {
            maxSpeed = map(distanceFromDestination,0,100,maxSpeed/2,maxSpeed);
        }

        double rideAngle = 0.3*M_PI;
        if(abs(difference) < 0.1 * M_PI)
        {
            left = maxSpeed;
            right = maxSpeed;
        }
        else if(difference > 0)
        {
            left = maxSpeed;
            if(difference > rideAngle)
            {
                if(distanceFromDestination > 100)
                {
                    right = map(difference,0,rideAngle,-maxSpeed,0);
                }
                else {
                    right = map(difference,0,rideAngle,-maxSpeed,-maxSpeed/2);
                }

            }
            else {
                right = -maxSpeed;
            }
        }
        else if(difference < 0)
        {
            right = maxSpeed;
            if(difference > -rideAngle)
            {
                if(distanceFromDestination > 100)
                {
                    left = map(difference,-rideAngle,0,-maxSpeed, 0);
                }
                else {
                    left = map(difference,-rideAngle,0,-maxSpeed, -maxSpeed/2);
                }
            }
            else {
                left = -maxSpeed;
            }
        }
    }
    if(swarmSimulationSettings.acceleartionControlEnabled)
    {
        double acceleration = 5;
        if(left > robot->currentSpeedLeft)
        {
            robot->currentSpeedLeft+= std::min(acceleration,left - robot->currentSpeedLeft);
        }
        if(left < robot->currentSpeedLeft)
        {
            robot->currentSpeedLeft-= std::min(acceleration, robot->currentSpeedLeft - left);
        }
        if(right > robot->currentSpeedRight)
        {
            robot->currentSpeedRight+= std::min(acceleration,right - robot->currentSpeedRight);
        }
        if(right < robot->currentSpeedRight)
        {
            robot->currentSpeedRight-= std::min(acceleration, robot->currentSpeedRight - right);
        }
        moveWheels(robot->currentSpeedLeft, robot->currentSpeedRight, robot);
    }
    else {
         moveWheels(left, right, robot);
    }
}
void SwarmSimulation::moveWheels(double Vl, double Vr, RobotLocation* robot)
{
    //http://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdfs
    //calculations from https://www.robotc.net/wikiarchive/File:Differential_Steering_Graphic_2_wheels.png
    //https://www.robotc.net/wikiarchive/Tutorials/Arduino_Projects/Additional_Info/Turning_Calculations
    double l = globalSettings.botDistanceBetweenWheels;
    double currentAngle = robot->angle;
    if(abs(Vr - Vl) <0.5)//if there is no steering the formula doesn't work, adding 0.01 is solution to fix it, in real life the robots will never go perfectly straith
    {
        Vr += 0.01;
    }
    double r = (l/2) * (Vl + Vr) / (Vr - Vl);

    double wdt = (Vr - Vl) * deltaT * globalSettings.simulationSpeed / l;

    double ICCx = robot->x - r * sin(currentAngle);
    double ICCy = robot->y + r * cos(currentAngle);

    double values[] = {
        cos(wdt), -sin(wdt), 0,
        sin(wdt), cos(wdt), 0,
        0, 0, 1
    };
    QGenericMatrix<3,3,double> matrix(values);

    double values2[] = {
        robot->x - ICCx, robot->y - ICCy, currentAngle
    };

    QGenericMatrix<1,3,double> matrix2(values2);
    double values3[] = {
        ICCx, ICCy, wdt
    };

    QGenericMatrix<1,3,double> matrix3(values3);
    QGenericMatrix<1,3,double> result = matrix * matrix2 + matrix3;
    robot->x = result.data()[0];
    robot->y = result.data()[1];
    robot->angle = result.data()[2];
    while(robot->angle >= 2 * M_PI) robot->angle -=2 * M_PI;
    while(robot->angle < 0) robot->angle +=2 * M_PI;

}
void SwarmSimulation::startSimulation()
{
    //qDebug() << "start simulation called" << endl;
    deltaT = (double)(clock() - lastTime)/CLOCKS_PER_SEC;
    deltaT = std::fmax(deltaT, 0.1);
    lastTime = clock();
    QListIterator<RobotLocation*> i(robotLocationManager.robots);
    while (i.hasNext())
    {
        RobotLocation *currentRobot = i.next();
        if(currentRobot->type == RobotLocation::RobotType::SIMULATED)
        {
            if(swarmSimulationSettings.realisticSimulationEnabled)
            {
                moveRobotRealistic(currentRobot);
                moveRobotRealistic(currentRobot->simulatedRobot);

            }
            else {
                moveRobot(currentRobot);
                moveRobot(currentRobot->simulatedRobot);
            }
        }
    }


    emit simulationFinished();
}

