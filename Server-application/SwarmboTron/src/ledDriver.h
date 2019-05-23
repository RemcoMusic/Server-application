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
        #define NUM_LEDS 90       
        #define DELAYVAL 500 

        int brightness = 100; 
        int middleLedPosition = 0;
        int directionLedPostition = 15;
     
        void off();
        void startup();
        void charging();
        void normal();
};