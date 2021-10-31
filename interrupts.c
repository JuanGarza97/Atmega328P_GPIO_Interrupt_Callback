/*
 * interrupts.c
 *
 * Created: 10/7/2021 7:38:01 PM
 * Author : Juan Carlos Garza Sanchez
 */ 

 #include <string.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "interrupts.h"
 #include "timers.h"

 void (*callback0)() = NULL;
 void (*callback1)() = NULL;
 unsigned long debounce0 = 0;
 unsigned long debounce1 = 0;
 uint8_t debounce_flag0 = 0;
 uint8_t debounce_flag1 = 0;
 unsigned long start_time0 = 0;
 unsigned long start_time1 = 0;

 void initInterrupt(uint8_t selector, char *mode, void (*callback)())
 {
	switch(selector)
	{
		case 0:
			if(strcmp(mode,"low"))
			{
				EICRA &= ~(1 << ISC01) & ~(1 << ISC00);
			}
			else if(strcmp(mode,"any"))
			{
				EICRA |= (1 << ISC00);
				EICRA &= ~(1 << ISC01);
			}
			else if(strcmp(mode,"falling"))
			{
				EICRA |= (1 << ISC01);
				EICRA &= ~(1 << ISC00);
			}
			else if(strcmp(mode,"rising"))
			{
				EICRA |= (1 << ISC01) | (1 << ISC00);
			}
			callback0 = callback;
		break;
		case 1:
			if(strcmp(mode,"low"))
			{
				EICRA &= ~(1 << ISC11) & ~(1 << ISC10);
			}
			else if(strcmp(mode,"any"))
			{
				EICRA |= (1 << ISC10);
				EICRA &= ~(1 << ISC11);
			}
			else if(strcmp(mode,"falling"))
			{
				EICRA |= (1 << ISC11);
				EICRA &= ~(1 << ISC10);
			}
			else if(strcmp(mode,"rising"))
			{
				EICRA |= (1 << ISC11) | (1 << ISC10);
			}
			callback1 = callback;
		break;
	}
 }

 void initDebounce(uint8_t selector, unsigned long debounceTime)
 {
	 switch(selector)
	 {
		case 0:
			debounce0 = debounceTime;
		break;
		case 1:
			debounce1 = debounceTime;
		break;
	 }
	 initTimer();
	 enableTimer();
 }

void enableInterrupt(uint8_t selector)
{
	switch(selector)
	{
		case 0:
			EIMSK |= (1 << INT0);
		break;
		case 1:
			EIMSK |= (1 << INT1);
		break;
	}
	sei();
}

void disableInterrupt(uint8_t selector)
{
	switch(selector)
	{
		case 0:
			EIMSK &= ~(1 << INT0);
		break;
		case 1:
			EIMSK &= ~(1 << INT1);
		break;
	}
}

ISR(INT0_vect)
{
	if(debounce_flag0 && (getTime() - start_time0 >= debounce0))
	{
		debounce_flag0 = 0;
	}

	if(!debounce_flag0)
	{
		callback0();
		debounce_flag0 = 1;
		start_time0 = getTime();
	}
	
}

ISR(INT1_vect)
{
	if(debounce_flag1 && (getTime() - start_time1 >= debounce1))
	{
		debounce_flag1 = 0;
	}

	if(!debounce_flag1)
	{
		callback1();
		debounce_flag1 = 1;
		start_time1 = getTime();
	}
	
}
