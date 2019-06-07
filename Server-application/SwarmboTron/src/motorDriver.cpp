#include <Arduino.h>
#include "motorDriver.h"

void MotorDriver::driveMotor()
{
    if(udpData.status == NORMAL && globalData.motorsEnabled)
    {
        if ((udpData.newX > udpData.currentX - 10) && (udpData.newX < udpData.currentX + 10) && (udpData.newY > udpData.currentY - 10) && (udpData.newY < udpData.currentY + 10)) 
        {
            setMotorSpeed(0,0); //destination reached
            debugE("Target found!");
            globalData.targetFound = true;
        }
        else //move te new coordinates
        {
            globalData.targetFound = false; //set target found to false for debug purposes
            
            int16_t deltaX = udpData.newX - udpData.currentX; //calculate difference in Y and X   
            int16_t deltaY = udpData.newY - udpData.currentY;

            double angleRad = atan2(deltaY, deltaX); //calculate new angle
            int16_t angleDeg = ((angleRad * 180) / PI); //angle degree has a value between 180 and -180 0 == facing right 

            angleDeg = map(angleDeg, -180, 180, 360, 0); //convert to 0 till 360
            angleDeg = (angleDeg + 270)%360;


            //debugE("* Current Angle: %u", udpData.currentAngle);
            debugE("* Desired Angle: %u", angleDeg);

            MappedMotorSpeed = map(udpData.speed, 0, 255, 400, 1024); //map speed from server to MappedMotorSpeed

            if(moveToAngle(angleDeg)) //if disired angle is reached
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

void MotorDriver::goToCoordinates(uint8_t speed, uint16_t desiredAngle, uint16_t currentAngle)
{  
    // int speedR = map(currentAngle, desiredAngle - angleDeadband, desiredAngle + angleDeadband, speed, maxSpeed);
    // int speedL = map(currentAngle, desiredAngle - angleDeadband, desiredAngle + angleDeadband, maxSpeed, speed);

    int speedR = 800;
    int speedL = 800;

    //set motorspeed based on the desired angle, the desired speed and the defined maximum speed.
    //debugE("* speedL: %u", speedL);
    //debugE("* speedR: %u", speedR);

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
        debugE("Rotating to the right");

        ledcWrite(0, MappedMotorSpeed);
        ledcWrite(1, 0);

        ledcWrite(2, 0);
        ledcWrite(3, MappedMotorSpeed); 
    }
    else //Turn left
    {
        debugE("Rotating to the left");

        ledcWrite(0, 0);
        ledcWrite(1, MappedMotorSpeed);

        ledcWrite(2, MappedMotorSpeed);
        ledcWrite(3, 0);
    }
}


bool MotorDriver::moveToAngle(int16_t newAngle)
{
    int16_t angleDelta = (newAngle - udpData.currentAngle); //calculate the difference in angle

    //debugE("* degrees till destination: %u", angleDelta);

    if(angleDelta < 0) //if number is negative move right
    {
        angleDelta = abs(angleDelta);

        if(angleDelta > angleDeadband) //if angle > angleDeadband rotate around axis
        {
            //debugE("* AngleDelta: %u", angleDelta);
            rotateAxis(1); //turn right
        }
        else
        {
            //debugE("* Angle reached!: %u", angleDelta);
            return true; //ready   
        }  
    }
    else
    {
        if(angleDelta > angleDeadband) //if angle > angleDeadband rotate around axis
        {
            //debugE("* AngleDelta: %u", angleDelta);
            rotateAxis(2); //turn left
        }
        else
        {
            //debugE("* Angle reached!: %u", angleDelta);
            return true; //ready
        }
    }
    return false;
}