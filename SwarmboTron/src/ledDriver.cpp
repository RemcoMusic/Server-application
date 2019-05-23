#include <Arduino.h>
#include "ledDriver.h"

CRGB leds[NUM_LEDS];

void LedDriver::setup()
{
	LEDS.addLeds<WS2812,PIN,GRB>(leds,NUM_LEDS);
}

void LedDriver::selectMode()
{
	switch (udpData.status) {
		case 0: off();		//all leds off
				break;
        case 1: startup();	//turn on middle led to green
				break;
		case 2: normal();	//middle led red and direction led blue
				break;
		case 3: charging();	//charging animation
				break;
		default:
				off();
    }
}

void LedDriver::charging()
{
		brightness = 0;

		for(int i = 0; i < NUM_LEDS; i++) 
		{
			leds[i] = CRGB::Orange;
		}

		for(int b = 0; b < 255; b++)
		{
			FastLED.setBrightness(b);
			FastLED.show(); 	
			delay(10);
		}

		for(int b = 255; b > 0; b++)
		{
			FastLED.setBrightness(b);
			FastLED.show(); 	
			delay(10);
		}
}

void LedDriver::off()
{
	FastLED.clear();
	FastLED.setBrightness(0);
	FastLED.show(); 	
}

void LedDriver::startup()
{
	FastLED.clear();
	FastLED.setBrightness(brightness);
	leds[middleLedPosition] = CRGB::Green;
	FastLED.show();
}

void LedDriver::normal()
{
	FastLED.clear();
	FastLED.setBrightness(brightness);
	leds[middleLedPosition] = CRGB::Red;
	leds[directionLedPostition] = CRGB::Green;
	FastLED.show();
}






