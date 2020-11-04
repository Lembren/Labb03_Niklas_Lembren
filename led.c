#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h> 
#include "led.h"
static bool Fade = true;
static uint8_t Brightness = 0;
static uint8_t Period = 255;

void LED_init() {
	DDRD |= (1 << PD6); /*arduino digital pin 6 output*/
}
uint8_t simple_ramp() // fade up and down
{
    if (Brightness <= Period && Fade == true) {
        Brightness++;
    }
    else if (Brightness <= Period && Fade == false) {
        Brightness--;
    }
    if (Brightness == 255) {
        Fade = false;
    }
    else if (Brightness == 0) {
        Fade = true;
    }
    return Brightness;
}