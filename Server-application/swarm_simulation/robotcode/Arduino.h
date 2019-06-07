#pragma once
#include <stdint.h>
#include <math.h>
#include "globalhelperfunctions.h"
#include <QObject>
#include "robotlocation.h"
#define OUTPUT 0
#define PI M_PI
#define debugE qDebug
//#define debugE
#define degrees(angleRadians) ((angleRadians) * 180.0 / M_PI)


extern void ledcWrite(int pin, int dutyCycle);

extern void pinMode(int pin,int mode);
extern void ledcSetup(int pin, int a, int b);
extern void ledcAttachPin(int pin, int mode);
extern double getLeftSpeedFromLastArduinoSimulation();
extern double getRigthSpeedFromLastArduinoSimulation();

