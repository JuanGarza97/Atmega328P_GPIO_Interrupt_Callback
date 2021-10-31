/*
 * timers.c
 *
 * Created: 10/7/2021 4:47:03 PM
 * Author : Juan Carlos Garza Sanchez
 */ 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "timers.h"

 long debounce_timer = 0;

 void initTimer()
 {
	TCCR1B |= (1 << WGM12); //set ctc bit
	OCR1A = 250;
	TIMSK1 |= (1 << OCIE1A);
	//sei();
 }

 void enableTimer()
 {
	TCCR1B |= (1 << CS11) | (1 << CS10); //64 preescaler
 }

 unsigned long getTime()
 {
	return debounce_timer;
 }

 void increaseTimer()
 {
	debounce_timer++;
 }

 void resetTime()
 {
	 debounce_timer = 0;
 }

 ISR(TIMER1_COMPA_vect)
 {
	 debounce_timer++;
 }