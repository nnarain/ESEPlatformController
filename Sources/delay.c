#include "delay.h"

#define CYCLES_PER_SECOND 16000000UL
#define CYCLES_PER_MS     (CYCLES_PER_SECOND / 1000UL) / 1000UL

void delay_ms(unsigned long ms)
{
    unsigned long i;
    unsigned long cycles = ms * CYCLES_PER_MS;
    
    for(i = cycles; i > 0; --i);
}