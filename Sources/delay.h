
#ifndef DELAY_H
#define DELAY_H

#include "timer.h"
#include "derivative.h"

/* Prototypes */

/**
	Delay ms milliseconds
*/
void delay_ms(word ms);

/**
	Delay us microseconds
	
	Warning: Maximum Prescaler value is 8
*/
void delay_us(word us);

#endif
