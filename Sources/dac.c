
/**
	DAC Module
	
	@author Natesh Narain
*/

#include "dac.h"
#include "spi.h"

#define CS_PORT PTJ
#define CS_DDR  DDRJ
#define CS      PTJ_PTJ7_MASK

// select the dac device
#define SPI_SS_ON()  CLR(CS_PORT, CS)
// unselect the dac device
#define SPI_SS_OFF() SET(CS_PORT, CS)

void dac_init(void)
{
    // configure SPI settings
    SPI_MASTER_MODE();
    
    SPI_MSB_FIRST();
    
    SPI_CLK_POLARITY_HIGH();
    
    SPI_CLK_PHASE_ODD();
    
    SPI_SET_BAUD(0, 2);
    
    SPI_ENABLE();
    
    // chip select DDR as output
    SET(CS_DDR, CS);
}

void dac_wake(DACVREF vref)
{
	dac_cmd(DAC_WAKE, vref);
}

void dac_setOutput(unsigned char a, unsigned char b)
{
	dac_cmd(DAC_LDIA, a);
	dac_cmd(DAC_LDIB, b);
	dac_cmd(DAC_LDOAB, 0);
}

void dac_cmd(DACControl c, unsigned char data)
{
    unsigned int out = 0x0000;
    
    out |= ((c & 0xFFFF) << 12) | ((data & 0xFFFF) << 4);
    
    SPI_SS_ON();
    spi_putc((out & 0xFF00) >> 8);
    spi_putc(out & 0x00FF);
    SPI_SS_OFF();
}