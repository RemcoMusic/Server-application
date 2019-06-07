#include <Arduino.h>
#include "motorDriver.h"

int motorSpeed = map(udpData.speed, 0, 100, 0, 1024);

void MotorDriver::driveMotor()
{
    if(udpData.status == NORMAL)
    {
        if (udpData.newX > udpData.currentX - 10 && udpData.newX < udpData.currentX + 10 && udpData.newY > udpData.currentY - 10 && udpData.newY < udpData.currentY + 10) 
        {
            setMotorSpeed(0,0); //destination reached
        }
        else
        {
            if(udpData.currentX != udpData.newX || udpData.currentY != udpData.newY)
            {
                int16_t deltaX = udpData.newX - udpData.currentX;   
                int16_t deltaY = udpData.newY - udpData.currentY;

                int16_t angleRad = atan2(deltaY, deltaX);
                int16_t angleDeg = angleRad * 180 / PI;

                if(angleDeg < 0)
                {
                    angleDeg = 360 + angleDeg; 
                }

                if(moveToAngle(udpData.currentAngle, angleDeg))
                {
                    goToCoordinates(udpData.speed, angleDeg, udpData.currentAngle);    
                } 
            }
        }
    }
    else
    {
        setMotorSpeed(0,0);
    }
    
}

void MotorDriver::goToCoordinates(uint8_t speed, uint16_t desiredAngle, uint16_t currentAngle)
{  
    int speedL = map(currentAngle, desiredAngle - angleDeadband, desiredAngle + angleDeadband, motorSpeed, maxSpeed); 
    int speedR = map(currentAngle, desiredAngle - angleDeadband, desiredAngle + angleDeadband, maxSpeed, motorSpeed);

    setMotorSpeed(speedL, speedR);
}

void MotorDriver::setMotorSpeed(int speedL, int speedR) 
{
    if(speedL >= 0)
    {
    ledcWrite(0, speedL);
    ledcWrite(1, 0);
    }
    else
    {
    ledcWrite(0, 0);
    ledcWrite(1, speedL * -1);
    }
    
    if(speedR >= 0)
    {
    ledcWrite(2, speedR);
    ledcWrite(3, 0);  
    }
    else
    {
    ledcWrite(2, 0);
    ledcWrite(3, speedR * -1);  
    }
}

void MotorDriver::rotateAxis(int direction)
{
    if(direction == 1) //Turn right
    {
        ledcWrite(0, 0);
        ledcWrite(1, motorSpeed);

        ledcWrite(2, motorSpeed);
        ledcWrite(3, 0);
    }
    else //Turn left
    {
        ledcWrite(0, motorSpeed);
        ledcWrite(1, 0);

        ledcWrite(2, 0);
        ledcWrite(3, motorSpeed);  
    }
}


bool MotorDriver::moveToAngle(int16_t oldAngle, int16_t newAngle)
{
    int16_t angleDelta = newAngle - oldAngle;

    if(angleDelta < 0) //if number is negative
    {
        angleDelta = angleDelta * (-1);

        if(angleDelta > angleDeadband) //if angle > angleDeadband rotate around axis
        {
            rotateAxis(1); 
        }
        else
        {
            return true;
        }   
    }
    else
    {
        if(angleDelta > angleDeadband) //if angle > angleDeadband rotate around axis
        {
            rotateAxis(2); 
        }
        else
        {
            return true;
        }
    }
}