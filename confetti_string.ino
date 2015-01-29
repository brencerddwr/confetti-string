#include "FastLED.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Confetti
//
//////////////////////////////////////////////////

// Change this to reflect the number of LEDS in your string
#define NUM_LEDS 29

// Data pin that led data will be written out over
#define DATA_PIN 11

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// Create array for the leds
CRGB leds[NUM_LEDS];

void setup() {
	// sanity check delay - allows reprogramming if accidentally blowing power w/leds
	delay(2000);

	// setup LED strip with the array
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
	
	// set initial master brightness of LEDS
	FastLED.setBrightness(255);

}

void loop() {
	// fade to black
	fadeToBlackBy( leds, NUM_LEDS, 10);
	
	// pick a random led from the string
	int x = random16(NUM_LEDS);
	
	// check if the led is off
	if (!leds[x])
	{
		// if the led was off, set a random hue at full saturation and value
		leds[ x ] += CHSV( random8(), 255, 255);
	}
	FastLED.show();
	FastLED.delay(20);

}

