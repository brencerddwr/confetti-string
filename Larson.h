#ifndef LARSON_H
#define LARSON_H

#include "master.h"

static uint8_t larsonHue = 0;
static int InterframeDelay[] = {20,40,80};
int currentDelay = 0;
int larsonLoopCounter = 0;
bool larsonUP = true;
class Larson: public Master
{
	public:
	Larson(){currentDelay = 0;}
	~Larson(){}
	
	virtual void loop()
	{
		if (larsonLoopCounter< NUM_LEDS && larsonUP)
		{
			// Set the i'th led to red
			leds[larsonLoopCounter] = CHSV(larsonHue, 255, 255);
			// Show the leds
			FastLED.show();
			// now that we've shown the leds, reset the i'th led to black
			// leds[i] = CRGB::Black;
			fadeall();
			// Wait a little bit before we loop around and do it again
			FastLED.delay(InterframeDelay[currentDelay]);
			larsonLoopCounter++;
			if (larsonLoopCounter==NUM_LEDS)
			{
				larsonUP=!larsonUP;
				larsonHue++;
			}
			
		}
		
		if (larsonLoopCounter>-1 && !larsonUP)
		{
			// Set the i'th led to red
			leds[larsonLoopCounter] = CHSV(larsonHue, 255, 255);
			// Show the leds
			FastLED.show();
			// now that we've shown the leds, reset the i'th led to black
			// leds[i] = CRGB::Black;
			fadeall();
			// Wait a little bit before we loop around and do it again
			FastLED.delay(InterframeDelay[currentDelay]);
			larsonLoopCounter--;
			if (larsonLoopCounter==0)
			{
				larsonUP=!larsonUP;
				larsonHue++;
			}
		}
	}

	void fadeall()
	{
		for(int i = 0;i < NUM_LEDS; i++)
		{
			leds[i].nscale8(128);
		}
	}
	
	virtual void modePress()
	{
		currentDelay ++;
		if (currentDelay >= sizeof(InterframeDelay)/sizeof(int))
		{
			currentDelay = 0;
		}
	}


	protected:

	private:


	
};
#endif