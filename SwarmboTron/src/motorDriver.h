#include <Arduino.h>
#include "globals.h"
#include <cmath>

class MotorDriver
{
    public:
        MotorDriver()
        {
            pinMode(33, OUTPUT); //Motor IN1 Motor1
            pinMode(32, OUTPUT); //Motor IN2
            ledcSetup(0,30000,10); //Motor IN1 
            ledcSetup(1,30000,10); //Motor IN2 
            ledcAttachPin(33,0); //Motor IN1 
            ledcAttachPin(32,1); //Motor IN2

            pinMode(26, OUTPUT); //Motor IN3 Motor2
            pinMode(27, OUTPUT); //Motor IN4
            ledcSetup(2,30000,10); //Motor IN3
            ledcSetup(3,30000,10); //Motor IN4
            ledcAttachPin(26,2); //Motor IN3
            ledcAttachPin(27,3); //Motor IN4
        }

        void driveMotor();

    private:  
        int angleDeadband = 30;
        int maxSpeed = 900;  
        void setMotorSpeed(int speedL, int speedR);
        void rotateAxis(int direction);
        void goToCoordinates(uint8_t speed, uint16_t desiredAngle, uint16_t currentAngle);
        bool moveToAngle(int16_t oldAngle, int16_t newAngle);
};