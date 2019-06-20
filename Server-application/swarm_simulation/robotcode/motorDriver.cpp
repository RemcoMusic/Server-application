#include "motorDriver.h"

void MotorDriver::driveMotor()
{
    if(udpData.status == NORMAL && globalData.motorsEnabled)
    {
        if ((udpData.newX > udpData.currentX - 10) && (udpData.newX < udpData.currentX + 10) && (udpData.newY > udpData.currentY - 10) && (udpData.newY < udpData.currentY + 10))
        {
            setMotorSpeed(0,0); //destination reached
            globalData.targetFound = true;
        }
        else //move to new coordinates
        {
            if ((udpData.newX > udpData.currentX - 70) && (udpData.newX < udpData.currentX + 70) && (udpData.newY > udpData.currentY - 70) && (udpData.newY < udpData.currentY + 70))
            {
                angleDeadband = 5;
                maxSpeed = minSpeed + 200;
            }
            else
            {
                angleDeadband = oldAngleDeadband;
                maxSpeed = oldMaxSpeed;
            }
            
            globalData.targetFound = false; //set target found to false
            
            int16_t deltaX = udpData.currentX - udpData.newX; //calculate difference in Y and X
            int16_t deltaY = udpData.currentY - udpData.newY;

            double angleRad = atan2(deltaY, deltaX); //calculate new angle angleRad has a value between 180 and -180 -pi to pi
            int16_t angleDeg = degrees(angleRad) + 180; //angle degree has a value between 180 and -180 0 == facing right 90 = top

            if(udpData.speed == 0)
            {
                MappedMotorSpeed = 0;
            }
            else
            {
                int speed = udpData.speed;
                int distanceFromDestination = sqrt(deltaX*deltaX + deltaY*deltaY);
                if(distanceFromDestination < 100)
                {
                    MappedMotorSpeed = map(distanceFromDestination,0,100,0,speed);
                }
                MappedMotorSpeed = map(speed, 0, 255, minSpeed, maxSpeed); //map speed from server to MappedMotorSpeed

            }
            
            if(moveToAngle(angleDeg)) //if angle is within deadband
            {
                goToCoordinates(MappedMotorSpeed, angleDeg, udpData.currentAngle); //move towards the coordinates
            }
        }
    }
    else
    {
        setMotorSpeed(0,0);  //do nothing
    }
    
}
//void MotorDriver::moveRobotRealistic()
//{
//    double deltaX = udpData.newX - udpData.currentX;
//    double deltaY = udpData.newY - udpData.currentY;
//    double goalAngle;
//    bool onLocation=false;
//    double distanceFromDestination = sqrt(deltaX*deltaX + deltaY*deltaY);//pythogoras
//    if((abs(deltaX) <= 10) && (abs(deltaY) <= 10))//already on location
//    {
//        goalAngle = 0;
//        onLocation = true;
//    }
//    else {
//        goalAngle = atan2(deltaY,deltaX);
//    }

//    while(goalAngle <0) goalAngle += M_PI * 2;
//    double currentAngle = radians(udpData.currentAngle);
//    while(currentAngle < 0) currentAngle += M_PI * 2;

//    double difference = currentAngle - goalAngle;
//    if(difference > M_PI)difference -= 2* M_PI;
//    if(difference < -M_PI)difference += 2 * M_PI;
////    if(!onLocation)
////    {
////        if(abs(difference) > 0.6 * M_PI)//0.6 is added for hysteresis
////        {
////            robot->angle += M_PI;
////        }
////    }
//    while(currentAngle >= 2*M_PI) currentAngle -= M_PI * 2;

//    double left = 0;
//    double right = 0;
//    if(onLocation)
//    {
//        double maxSpeed = map(difference,0,2 * M_PI,udpData.speed/2,udpData.speed);
//        if(difference > 0)
//        {
//            left = maxSpeed;
//            right = -maxSpeed;
//        }
//        else {
//            left = -maxSpeed;
//            right = maxSpeed;
//        }
//    }
//    else
//    {
//        int maxSpeed = udpData.speed;
//        if(distanceFromDestination < 100)
//        {
//            maxSpeed = map(distanceFromDestination,0,100,maxSpeed/2,maxSpeed);
//        }

//        double rideAngle = 0.3*M_PI;
//        if(abs(difference) < 0.1 * M_PI)
//        {
//            left = maxSpeed;
//            right = maxSpeed;
//        }
//        else if(difference > 0)
//        {
//            left = maxSpeed;
//            if(difference < rideAngle)
//            {

//                    right = map(difference,0,rideAngle,-maxSpeed,0);
//            }
//            else {
//                right = -maxSpeed;
//            }
//        }
//        else if(difference < 0)
//        {
//            right = maxSpeed;
//            if(difference > -rideAngle)
//            {

//                    left = map(difference,-rideAngle,0,-maxSpeed, 0);

//            }
//            else {
//                left = -maxSpeed;
//            }
//        }
//    }
//    setMotorSpeed(right,left);
//}
void MotorDriver::goToCoordinates(uint8_t speed, uint16_t desiredAngle, uint16_t currentAngle)
{
    // int speedL = map(currentAngle, desiredAngle - angleDeadband, desiredAngle + angleDeadband, speed, maxSpeed);
    // int speedR = map(currentAngle, desiredAngle - angleDeadband, desiredAngle + angleDeadband, maxSpeed, speed);

    //currentAngle = 100
    //desiredAngle = 70

    //lower = 40
    //upper = 100

    //left motor should be faster

    //set motorspeed based on the desired angle, the desired speed and the defined maximum speed.
    //debugE("* speedL: %u", speedL);
    //debugE("* speedR: %u", speedR);

    int speedL = 0;
    int speedR = 0;

    
    if(globalData.Map)
    {
        speedL = map(currentAngle, desiredAngle - angleDeadband, desiredAngle + angleDeadband, minSpeed, MappedMotorSpeed);
        speedR = map(currentAngle, desiredAngle + angleDeadband, desiredAngle - angleDeadband, minSpeed, MappedMotorSpeed);
    }
    else
    {
        speedR = MappedMotorSpeed;
        speedL = MappedMotorSpeed;
    }

    // debugW("* speedL: %d", speedL);
    // debugW("* speedR: %d", speedR);

    setMotorSpeed(speedL, speedR);
}

void MotorDriver::setMotorSpeed(int speedL, int speedR) 
{
    if(speedL >= 0) //turn forward 
    {
    ledcWrite(0, speedL);
    ledcWrite(1, 0);
    }
    else //turn backward
    {
    ledcWrite(0, 0);
    ledcWrite(1, abs(speedL));
    }
    
    if(speedR >= 0) //turn forward
    {
    ledcWrite(2, speedR);
    ledcWrite(3, 0);  
    }
    else //turn backward
    {
    ledcWrite(2, 0);
    ledcWrite(3, abs(speedR));  
    }
}

void MotorDriver::rotateAxis(int direction)
{
    if(direction == 1) //Turn right
    {
        ledcWrite(0, MappedMotorSpeed);
        ledcWrite(1, 0);

        ledcWrite(2, 0);
        ledcWrite(3, MappedMotorSpeed); 
    }
    else //Turn left
    {
        ledcWrite(0, 0);
        ledcWrite(1, MappedMotorSpeed);

        ledcWrite(2, MappedMotorSpeed);
        ledcWrite(3, 0);
    }
}


bool MotorDriver::moveToAngle(int16_t newAngle)
{
    int16_t angleDelta = newAngle - udpData.currentAngle;

    //debugE("* currentAngle: %u", udpData.currentAngle);
    //debugE("* newAngle: %u", newAngle);


    if(angleDelta > 180)
    {
        angleDelta = angleDelta - 360;
    }
    if(angleDelta < -180)
    {
        angleDelta = angleDelta + 360;
    }

    //debugE("* current delta: %d", angleDelta);

    //debugE("* degrees till destination: %u", angleDelta);
    
    if(angleDelta < 0) //if number is negative move right
    {
        angleDelta = abs(angleDelta);

        if(angleDelta > angleDeadband) //if angle > angleDeadband rotate around axis
        {
            MappedMotorSpeed = map(angleDelta,0,angleDeadband,minSpeed,MappedMotorSpeed);
            rotateAxis(2); //turn left
        }
        else
        {  
            return true; //ready   
        }  
    }   
    else
    {
        if(angleDelta > angleDeadband) //if angle > angleDeadband rotate around axis
        {
            rotateAxis(1); //turn right
        }
        else
        {
            return true; //ready
        }
    }
    return false;
}
