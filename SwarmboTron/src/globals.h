 #pragma once
 #include <Arduino.h>

#ifdef ARDUINO
        enum robotStatus{
        OFF = 0,
        STARTUP = 1,
        NORMAL = 2,
        CHARGING = 3,
        };

        struct UdpData {
        uint16_t currentX = 0;
        uint16_t currentY = 0;
        uint16_t newX = 0;
        uint16_t newY = 0;
        uint16_t currentAngle = 0;
        uint8_t speed = 0;
        uint8_t status = robotStatus::OFF;
        };
#endif
        extern UdpData udpData;

        struct GlobalData {
        bool motorsEnabled = true;
        bool targetFound = false;

        bool motorDebug = false;
        bool DriveForward = false;
        bool TurnLeft = false;
        bool TurnRight = false;
        bool Stop = false;
        uint8_t status = 0;
        bool Map = false;
        bool Led = false;
        bool fakeVoltage = false;
        };

       extern GlobalData globalData;
