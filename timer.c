#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer0_init(void)
{
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);/*set fast PWM mode with none-inverting mode*/
	TCCR0B |= (1 << CS00) | (1 << CS01);	/*Sets prescaler to 64*/
}

void timer2_init(void) {
	TCCR2A |= (1 << WGM21);	//CTC
	// set up timer with prescaler = 1024 
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
	TIMSK2 = (1 << OCIE2A);
    TCNT2 = 0;
}

