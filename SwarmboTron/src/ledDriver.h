#include <Arduino.h>
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "globals.h"
#include "debug.h"

class LedDriver
{
    public:
        void setup();
        void selectMode();
    private:
        #define PIN 19
        #define NUM_LEDS 27       
        #define DELAYVAL 500 

        int brightness = 75; 
        int middleLedPosition = 24;
        int directionLedPostition = 12; //calibrate so the led is facing forward
        int currentMode = 200;

        void off();
        void startup();
        void normal();
        void charging();
        void targetFound();
};