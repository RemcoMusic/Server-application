#pragma once
#include <Arduino.h>

#include "robotlocation.h"


       extern UdpData udpData;

       struct GlobalData {
       bool motorsEnabled = true;
       bool targetFound = false;

       bool motorDebug = false;
       bool DriveForward = false;
       bool TurnLeft = false;
       bool TurnRight = false;
       uint8_t status = 0;
       };

      extern GlobalData globalData;
