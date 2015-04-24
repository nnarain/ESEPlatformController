
/**
    Digital to Analog Converter Module
    
    @author Natesh Narain
*/

#ifndef DAC_H
#define DAC_H

/* Types */

//! DAC Control Bits
typedef enum
{
    DAC_NOP      = 0x00, // No Operation
    
    DAC_LDIA     = 0x01, // Load input register A, output unchanged
    DAC_LDIB     = 0x02, // Load input register B, output unchnaged
    
    DAC_LDOAB    = 0x80, // Load output register A and B, output changed

    DAC_LDIOAB   = 0x09, // Load input A and B, update output A and B
    DAC_LDIOBA   = 0x0A, // Load input B and A, update output B and A
    
    DAC_SHUTDOWN = 0x0C, 
    DAC_WAKE     = 0x0D, // Enter Normal Operation
    
    DAC_HIGH_Z   = 0x0E

}DACControl;

typedef enum
{
	DAC_VREF_1214 = 0x00, // 1.214 V
	DAC_VREF_1940 = 0x40, // 1.940 V
	DAC_VREF_2425 = 0x80, // 2.425 V
	DAC_VREF_3885 = 0xC0  // 3.885 V

}DACVREF;

/**
	Initialize SPI communication with the DAC 
*/
void dac_init(void);

void dac_wake(DACVREF vref);
void dac_setOutput(unsigned char a, unsigned char b);

void dac_cmd(DACControl c, unsigned char data);

#endif