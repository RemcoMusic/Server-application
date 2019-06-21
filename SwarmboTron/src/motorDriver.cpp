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
            if ((udpData.newX > udpData.currentX - 40) && (udpData.newX < udpData.currentX + 40) && (udpData.newY > udpData.currentY - 40) && (udpData.newY < udpData.currentY + 40)) 
            {
                angleDeadband = 10;
                maxSpeed = minSpeed + 50;
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
                if(distanceFromDestination < 200)
                {
                    MappedMotorSpeed = map(distanceFromDestination,0,200,0,speed);
                }
                MappedMotorSpeed = map(speed, 0, 255, minSpeed, maxSpeed); //map speed from server to MappedMotorSpeed
            }

            moveToAngle(angleDeg);
    
        }
    }
    else
    {
        setMotorSpeed(0,0);  //do nothing
    }
    
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

    if(angleDelta > 180)
    {
        angleDelta = angleDelta - 360;
    }
    if(angleDelta < -180)
    {
        angleDelta = angleDelta + 360;
    }

    if(angleDelta < 0) //if number is negative move right
    {
        angleDelta = abs(angleDelta);

        if(angleDelta > angleDeadband) //if angle > angleDeadband rotate around axis
        {
            rotateAxis(2); //turn left
        }
        else
        {  
            int speedL = map(angleDelta, 0, angleDeadband, minSpeed, MappedMotorSpeed);
            int speedR = map(angleDelta, 0, angleDeadband, MappedMotorSpeed, minSpeed); 

            setMotorSpeed(speedL,speedR);

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
            int speedL = map(angleDelta, 0, angleDeadband, minSpeed, MappedMotorSpeed);
            int speedR = map(angleDelta, 0, angleDeadband, MappedMotorSpeed, minSpeed); 

            setMotorSpeed(speedL,speedR);

            return true; //ready
        }
    }
    return false;
}