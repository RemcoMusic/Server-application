#include <Arduino.h>
#include "globals.h"
#include <cmath>
#include "debug.h"

class MotorDriver
{ 
    public:
        MotorDriver()
        {
            pinMode(32, OUTPUT); //Motor IN1 Motor1
            pinMode(33, OUTPUT); //Motor IN2
            ledcSetup(0,30000,10); //Motor IN1 
            ledcSetup(1,30000,10); //Motor IN2 
            ledcAttachPin(32,0); //Motor IN1 
            ledcAttachPin(33,1); //Motor IN2

            pinMode(26, OUTPUT); //Motor IN3 Motor2
            pinMode(27, OUTPUT); //Motor IN4
            ledcSetup(2,30000,10); //Motor IN3
            ledcSetup(3,30000,10); //Motor IN4
            ledcAttachPin(26,2); //Motor IN3
            ledcAttachPin(27,3); //Motor IN4
        }

        void driveMotor();
        void setMotorSpeed(int speedL, int speedR);
    private:  
        int angleDeadband = 30; //deadband for moving around axis
        int maxSpeed = 900; //maximum speed at wich the motors are able to turn  
        int MappedMotorSpeed = 0;
        void rotateAxis(int direction);
        void goToCoordinates(uint8_t speed, uint16_t desiredAngle, uint16_t currentAngle);
        bool moveToAngle(int16_t newAngle);
};