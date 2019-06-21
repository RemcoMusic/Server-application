#include <Arduino.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <iostream>
#include "globals.h"
#include "debug.h"

class serverCommunication
{
    public:
        void listen();
        //void send(uint8_t msg);
        void sendVoltage(uint16_t msg);
        void setup();

    private:
        unsigned int localUdpPort = 4210;  // local port to listen on
        const char* serverIP = "192.168.137.1";
        uint16_t serverPort = 4210;
        uint8_t rx_buffer[sizeof(udpData)];
        unsigned long startMillis;
        unsigned long currentMillis;
        unsigned long timeoutPeriod = 5000;
};
