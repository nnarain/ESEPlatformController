
/**
    SPI Module
    
    @author Natesh Narain
*/

#include "spi.h"

void spi_putc(char c)
{
    // wait to write
    while(!(SPISR & SPISR_SPTEF_MASK));
    
    SPIDR = c;
    
    // wait while transmitting
    while(!(SPISR & SPISR_SPIF_MASK));
}

char spi_getc(void)
{
    // wait to write 
    while(!(SPISR & SPISR_SPTEF_MASK));
    
    // trigger write
    SPIDR = 0;
    
    //
    while(!(SPISR & SPISR_SPIF_MASK));
    
    return SPIDR;
}