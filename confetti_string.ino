#include <FastLED.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
//
// multi-function light string
//
//////////////////////////////////////////////////

// Change this to reflect the number of LEDS in your string
#define NUM_LEDS 29

// Data pin that led data will be written out over
#define DATA_PIN 11

// setup switches
const int Left_SW = 2;
const int Right_SW =3;

// misc variables
unsigned long last_start;
int masterBrightness = 128;

// switch initialization
bool LeftFirst = false;
bool RightFirst = false;
bool LeftSecond = false;
bool RightSecond = false;

// Create array for the leds
//CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;
//include modules
#include "master.h"
#include "confetti.h"
#include "RainbowChase.h"
#include "Larson.h"
#include "antialias.h"

// setup instance of each mode class
Confetti confetti;
RainbowChase rainbowchase;
Larson larson;
AntiAlias antialias;

int currentModule = 0;
Master* modules[] = {
	&confetti,
	&rainbowchase,
	&larson,
	&antialias,
};


void setup() {
	//setup switch pins
	pinMode(Left_SW, INPUT);
	pinMode(Right_SW, INPUT);
	randomSeed(analogRead (0));
	// sanity check delay - allows reprogramming if accidentally blowing power w/leds
	delay(2000);

	// setup LED strip with the array
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
	
	// set initial master brightness of LEDS
	FastLED.setBrightness(masterBrightness);
	last_start = millis();

}

void loop() {
	// first check state of switches
	LeftFirst = digitalRead(Left_SW);
	RightFirst = digitalRead(Right_SW);
	FastLED.delay (10);
	
	modules[currentModule]->loop ();
	
	if (currentModule==2)
	{
		FastLED.setBrightness(254);
	}
	else
	{
		FastLED.setBrightness(masterBrightness);
	}
	
	FastLED.show();
	
	// second check state of switches
	LeftSecond = digitalRead(Left_SW);
	RightSecond = digitalRead(Right_SW);
	
	if (LeftFirst && !LeftSecond) {
		// Turn off all the pixels when entering new mode.
		FastLED.clear();
		FastLED.show();
		// Increment the current demo (looping back to zero if at end).
		currentModule += 1;
		if (currentModule >= (sizeof(modules)/sizeof(Master*))) {
			currentModule = 0;
		}
	}

	if (RightFirst && !RightSecond)
	{
		modules[currentModule]->modePress();
	}
}
