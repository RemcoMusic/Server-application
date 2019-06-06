#include "Arduino.h"

int simulatedLeftSpeed;
int simulatedRightSpeed;
void ledcWrite(int pin, int dutyCycle)
{
    if(dutyCycle == 0)return;
    int devider = 50;
    if(pin == 2)
    {
        simulatedLeftSpeed = dutyCycle/devider;
    }
    if(pin == 3)
    {
        simulatedLeftSpeed = -dutyCycle/devider;
    }
    if(pin == 0)
    {
        simulatedRightSpeed = dutyCycle/devider;
    }
    if(pin == 1)
    {
        simulatedRightSpeed = -dutyCycle/devider;
    }
}


void pinMode(int pin,int mode){}
void ledcSetup(int pin, int a, int b){}
void ledcAttachPin(int pin, int mode){}


