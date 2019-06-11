#pragma once
#include <stdint.h>
#include <math.h>
#include "globalhelperfunctions.h"
#include <QObject>
#include "robotlocation.h"
#include"swarmsimulationsettings.h"
#define OUTPUT 0
#define PI M_PI

#define degrees(angleRadians) ((angleRadians) * 180.0 / M_PI)


extern void ledcWrite(int pin, int dutyCycle);

extern void pinMode(int pin,int mode);
extern void ledcSetup(int pin, int a, int b);
extern void ledcAttachPin(int pin, int mode);
extern void debugE(va_list args);
extern double getLeftSpeedFromLastArduinoSimulation();
extern double getRigthSpeedFromLastArduinoSimulation();

