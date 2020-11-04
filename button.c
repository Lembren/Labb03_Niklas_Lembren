#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "button.h"
#define BIT_IS_SET(byte, bit) (byte & (1 << bit))

void button_init() {
	DDRD &= ~(1 << PD2);
}

void button() {
	int Pressed = 0;
	int Pressed_Confidence_Level = 0; //Measure button press cofidence
	int Released_Confidence_Level = 0; //Measure button release confidence
	int buttonstate = 0;

	while (1)
	{
		if (bit_is_clear(PIND, PD2))
		{
			Pressed_Confidence_Level++; //Increase Pressed Conficence
			Released_Confidence_Level = 0; //Reset released button confidence since there is a button press
			if (Pressed_Confidence_Level > 500) //Indicator of good button press
			{
				if (Pressed == 0)
				{
					printf_P(PSTR("released\r\n"));
					Pressed = 1;
					buttonstate = 0;

				}
				Pressed_Confidence_Level = 0;//resetso a new pressed condition can be evaluated
			}
		}
		else
		{
			Released_Confidence_Level++; //This works just like the pressed
			Pressed_Confidence_Level = 0; //Reset pressed button confidence since the button is released
			if (Released_Confidence_Level > 500)
			{
				Pressed = 0;
				Released_Confidence_Level = 0;
				if (buttonstate == 0) {
					printf_P(PSTR("pushed\r\n"));
					buttonstate = 1;
				}
			}
		}
	}
}