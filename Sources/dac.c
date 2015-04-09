
#include "dac.h"
#include "spi.h"

#define CS_PORT PTJ
#define CS_DDR  DDRJ
#define CS      PTJ_PTJ7_MASK

void dac_init(void)
{
    // configure SPI settings
    SPI_MASTER_MODE();
    
    SPI_MSB_FIRST();
    
    SPI_CLK_POLARITY_HIGH();
    
    SPI_CLK_PHASE_ODD();
    
    SPI_SET_BAUD(0, 2);
    
    SPI_ENABLE();
    
    // chip select
    
    SET(CS_DDR, CS);
    
}

void dac_write(DACControl c, unsigned char data)
{
    unsigned int out = 0x0000;
    
    out |= ((c & 0xFFFF) << 12) | ((data & 0xFFFF) << 4);
    
    spi_putc(out);
}