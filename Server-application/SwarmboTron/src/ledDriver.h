#include <Arduino.h>
#include <FastLED.h>
#include "globals.h"

class LedDriver
{
    public:
        void setup();
        void selectMode();
    private:
        #define PIN 19
        #define NUM_LEDS 25       
        #define DELAYVAL 500 

        int brightness = 100; 
        int middleLedPosition = 24;
        int directionLedPostition = 12; //calibrate so the led is facing forward
        int currentMode = 0;


        void off();
        void startup();
        void normal();

        void charging();
        void connectingWifi();
        void targetFound();
};