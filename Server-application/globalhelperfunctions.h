#pragma once
#include "robotlocation.h"
#include <stdint.h>
#include <math.h>
#include <objectsbase.h>

extern double map(double x, double x1, double x2, double y1, double y2);
extern double distanceBetweenPoints(int x1, int y1, int x2, int y2);
extern double distanceBetweenPoints(Object* object1, Object* object2);
extern bool isMoving(RobotLocation* robot);
