#ifndef CONFETTI_H
#define CONFETTI_H
#include "Master.h"

unsigned int new_led_delay = 1500;
unsigned int fade_delay = 30;

class Confetti: public Master
{
	public:
	Confetti(){};
	~Confetti(){};
	virtual void loop()
	{
		// fade to black
		fadeToBlackBy( leds, NUM_LEDS, 20);
		if (millis()-last_start > new_led_delay)
		{
			// pick a random led from the string
			int x = random16(NUM_LEDS);
			
			// check if the led is off
			if (!leds[x])
			{
				// if the led was off, set a random hue at full saturation and value
				leds[ x ] += CHSV( random8(),random8( 128, 255), 255);
			}
		}
		if (glitter)
		{
			addGlitter(20);
		}
		FastLED.delay (fade_delay);
	}


	virtual void modePress()
	{
		glitter = !glitter;
	};
	protected:
	
	private:
	bool glitter = false;
};
#endif