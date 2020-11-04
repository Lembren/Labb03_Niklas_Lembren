#include <avr/io.h>
#include <avr/interrupt.h> 

#include <stdio.h>
#include "adc.h"

void adc_init() {
    DIDR0 |= (1 << ADC0D); // pin 0 disabled from input
	ADMUX |= (1 << REFS0);// Select Vref=AVcc
    ADMUX |= (1 << ADLAR);  //left adjusted

    ADCSRA |= (1 << ADPS1) | (1 << ADPS0);//set prescaller to 8
    ADCSRA |= (1 << ADIE); //interrupt
    ADCSRA |= (1 << ADEN); //ENABLE ADC
}
unsigned int ADC_read(uint8_t ADCchannel)
{
    return (ADCH); //return calculated ADC value
}