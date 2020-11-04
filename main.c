#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "adc.h"
#include "button.h"
#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
uint8_t buttonstate = 0;
volatile uint8_t duty = 0;
ISR(ADC_vect) { 
	duty = ADC_read(0);  // Save ADC value
}

ISR(TIMER2_COMPA_vect)
{
	ADMUX = (ADMUX & 0xF0) | (0 & 0x0F); //select ADC channel with safety mask
	ADCSRA |= (1 << ADSC); //start conversion
	OCR0A = duty;
	//printf("%d\n", OCR0A);
}

int main(void) {
	uart_init();
	//LED_init();
	//timer0_init();
	//timer2_init();
	//adc_init();
	//sei();
	DDRD &= ~(1 << PD2);
		int Pressed = 1;
		int Released_Confidence_Level = 0; //Measure button press cofidence
		int Pressed_Confidence_Level = 0; //Measure button release confidence
		int buttonstate = 0;

		while (1)
		{
			if (bit_is_clear(PIND, PD2))
			{
				Released_Confidence_Level++; //Increase Pressed Conficence
				Pressed_Confidence_Level = 0; //Reset released button confidence since there is a button press
				if (Released_Confidence_Level > 500) //Indicator of good button press
				{
					if (Pressed == 0)
					{
						printf_P(PSTR("released\r\n"));
						Pressed = 1;
						buttonstate = 0;

					}
					Released_Confidence_Level = 0;//resetso a new pressed condition can be evaluated
				}
			}
			else
			{
				Pressed_Confidence_Level++; //This works just like the pressed
				Released_Confidence_Level = 0; //Reset pressed button confidence since the button is released
				if (Pressed_Confidence_Level > 500)
				{
					Pressed = 0;
					Pressed_Confidence_Level = 0;
					if (buttonstate == 0) {
						printf_P(PSTR("pushed\r\n"));
						buttonstate = 1;
					}
				}
			}
		}
		return 0;
}

