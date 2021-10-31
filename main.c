/*
 * Interrupts_Atmega328p.c
 *
 * Created: 10/7/2021 3:01:26 PM
 * Author : Juan Carlos Garza Sanchez
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include "interrupts.h"

unsigned long treshold = 200;
uint8_t selector = 0;

void initLed()
{
	//Output on
	DDRB = (1 << PORTB4);
	PORTB &= (0 << PORTB4);
}

void toggleLed()
{
	PORTB ^= (1 << PORTB4);
}

int main(void)
{
	initLed();

	initInterrupt(selector, "rising", toggleLed);
	initDebounce(selector, treshold);
	enableInterrupt(selector);

    /* Replace with your application code */
    while (1) 
    {
		
    }
}