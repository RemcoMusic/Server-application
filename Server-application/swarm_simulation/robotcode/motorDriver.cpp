#include "motorDriver.h"

#define DEADBAND 0.20*PI
#define P 0.7
double mapDouble(double x, double x1, double x2, double y1, double y2)
{
 return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}
void MotorDriver::driveMotor()
{
    if(udpData.status == NORMAL && globalData.motorsEnabled)
    {
        int16_t deltaX = udpData.newX - udpData.currentX;
        int16_t deltaY = udpData.newY - udpData.currentY;
        int distanceFromDestination = sqrt(deltaX*deltaX + deltaY * deltaY);

        globalData.targetFound = false; //set target found to false

        double desiredAngle = atan2(deltaY, deltaX); //calculate new angle angleRad has a value between 180 and -180 -pi to pi
        double currentAngle = udpData.currentAngle / 57.29;

        double angleDelta = desiredAngle - currentAngle;
        if(angleDelta > PI)
        {
            angleDelta = angleDelta - 2 * PI;
        }
        if(angleDelta < -PI)
        {
            angleDelta = angleDelta + 2 * PI;
        }

        if (distanceFromDestination < 10)
        {
            turnMotorsOff();
            globalData.targetFound = true;
            debugE("targed found");
        }
        else if(distanceFromDestination < 40)
        {
              turnMotorsOff();
              int maxSpeed = 30;
              if(abs(angleDelta) < 0.15 * PI)
              {
                  double error = mapDouble(abs(angleDelta) ,0,DEADBAND , 0.5, 1);
                  if(angleDelta > 0) //if number is negative move right
                  {
                    setMotorSpeed(maxSpeed*error,-maxSpeed*error);
                  }
                  else
                  {
                    setMotorSpeed(-maxSpeed*error,maxSpeed*error);
                  }
                  inRightDirection = false;
              }
              else
              {
                if(inRightDirection)
                {
                  setMotorSpeed(50, 50);
                  inRightDirection = false;
                }
                else
                {
                  inRightDirection = true;
                }
              }
        }
        else //move to new coordinates
        {
            inRightDirection = false;
            int maxSpeed = 150;
            if(abs(angleDelta) > DEADBAND)
            {
                debugE("rotate");
                if(angleDelta < 0) //if number is negative move right
                {
                    rotateAxis(2); //turn left
                }
                else
                {
                    rotateAxis(1); //turn right
                }
            }
            else
            {
                debugE("straigth");
                double error = mapDouble(abs(angleDelta),0,DEADBAND,P,1);
                if(angleDelta < 0)
                {
                    setMotorSpeed(maxSpeed*error, maxSpeed);
                }
                else
                {
                    setMotorSpeed(maxSpeed, maxSpeed*error);
                }
            }
        }
    }
    else
    {
        setMotorSpeed(0,0);  //do nothing
    }

}

void MotorDriver::turnMotorsOff()
{
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}
void MotorDriver::setMotorSpeed(int speedL, int speedR)
{
    int mappedSpeedL = 0;
    int mappedSpeedR = 0;
    if(udpData.speed != 0)
    {
        mappedSpeedL = map(abs(speedL), 0, 255, minSpeed, maxSpeed); //map speed from server to MappedMotorSpeed
        mappedSpeedR = map(abs(speedR), 0, 255, minSpeed, maxSpeed); //map speed from server to MappedMotorSpeed
    }
    if(speedL >= 0) //turn forward
    {
      ledcWrite(0, mappedSpeedL);
      ledcWrite(1, 0);
    }
    else //turn backward
    {
      ledcWrite(0, 0);
      ledcWrite(1, mappedSpeedL);
    }

    if(speedR >= 0) //turn forward
    {
      ledcWrite(2, mappedSpeedR);
      ledcWrite(3, 0);
    }
    else //turn backward
    {
      ledcWrite(2, 0);
      ledcWrite(3, mappedSpeedR);
    }
}

void MotorDriver::rotateAxis(int direction)
{
  int speed = map(udpData.speed, 0, 255, minSpeed, maxSpeed);
    if(direction == 1) //Turn right
    {
        ledcWrite(0, speed);
        ledcWrite(1, 0);

        ledcWrite(2, 0);
        ledcWrite(3, speed);
    }
    else //Turn left
    {
        ledcWrite(0, 0);
        ledcWrite(1, speed);

        ledcWrite(2, speed);
        ledcWrite(3, 0);
    }
}
