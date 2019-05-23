 #pragma once
 #include <Arduino.h>
 
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
        
        extern UdpData udpData;
