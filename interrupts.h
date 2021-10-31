/*
 * interrupts.h
 *
 * Created: 10/7/2021 7:37:38 PM
 * Author : Juan Carlos Garza Sanchez
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

void initInterrupt(uint8_t selector, char *mode, void (*callback)());
void initDebounce(uint8_t selector, unsigned long debounceTime);
void enableInterrupt(uint8_t selector);
void disableInterrupt(uint8_t selector);

#endif /* INTERRUPTS_H_ */