#include "Arduino.h"

double simulatedLeftSpeed;
double simulatedRightSpeed;

int pinSpeed[4] = {0,0,0,0};
void ledcWrite(int pin, int dutyCycle)
{
    pinSpeed[pin] = dutyCycle;
    double devider = 50;

    if(pinSpeed[0]==0)
    {
        simulatedRightSpeed = -pinSpeed[1]/devider;
    }
    else {
        simulatedRightSpeed = pinSpeed[0]/devider;
    }

    if(pinSpeed[2]==0)
    {
        simulatedLeftSpeed = -pinSpeed[3]/devider;
    }
    else {
        simulatedLeftSpeed = pinSpeed[2]/devider;
    }
}


void pinMode(int pin,int mode){}
void ledcSetup(int pin, int a, int b){}
void ledcAttachPin(int pin, int mode){}

void debugE(va_list args)
{
    if(swarmSimulationSettings.enableArduinoLogging)
    {
        qDebug(args);
    }
}


double getLeftSpeedFromLastArduinoSimulation()
{
    return simulatedLeftSpeed;
}

double getRigthSpeedFromLastArduinoSimulation()
{
    return simulatedRightSpeed;
}
