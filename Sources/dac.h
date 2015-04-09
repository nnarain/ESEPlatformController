
/**
    Digital to Analog Converter Module
    
    @author Natesh Narain
*/

#ifndef DAC_H
#define DAC_H

/* Types */

typedef enum
{
    DAC_NOP    = 0x00, // No Operation
    
    DAC_LDIA   = 0x01, // Load input register A, output unchanged
    DAC_LDIB   = 0x02, // Load input register B, output unchnaged
    
    DAC_LDOAB  = 0x80, // Load output register A and B, output changed

    DAC_LDIOAB = 0x09, // Load input A and B, update output A and B
    DAC_LDIOBA = 0x0A, // Load input B and A, update output B and A
    
    DAC_NORMAL = 0x0D  // Enter Normal Operation

}DACControl;

void dac_init(void);

void dac_write(DACControl c, unsigned char data);

#endif
