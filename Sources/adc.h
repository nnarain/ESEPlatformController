/**
	Analog to Digital
	
	@author Natesh Narain
*/

#ifndef ADC_H
#define ADC_H

#include "util.h"
#include "derivative.h"

/* Set AD Port to digital input or analog input */

#define ADC_SET_DIGITAL(chnl) SET(ATDDIEN, BV(chnl))
#define ADC_SET_ANALOG (chnl) CLR(ATDDIEN, BV(chnl))

/* Power Down */

#define ATD_ON()  SET(ATDCTL2, ATDCTL2_ADPU_MASK)
#define ATD_OFF() CLR(ATDCTL2, ATDCTL2_ADPU_MASK)

/* Fast Clear */

#define ATD_FAST_FLAG_CLEAR_ON()  SET(ATDCTL2, ATDCTL2_AFFC_MASK)
#define ATD_FAST_FLAG_CLEAR_OFF() CLR(ATDCTL2, ATDCTL2_AFFC_MASK)

/* Sequence Complete Interrupt */

#define ATD_COMPLETE_INT_ENABLE()  SET(ATDCTL2, ATDCTL2_ASCIE)
#define ATD_COMPLETE_INT_DISABLE() SET(ATDCTL2, ATDCTL2_ASCIE)

/* FIFO */

#define ATD_FIFO_ON()  SET(ATDCTL3, ATDCTL3_FIFO_MASK)
#define ATD_FIFO_OFF() CLR(ATDCTL3, ATDCTL3_FIFO_MASK)

/* Number of Conversions */

#define ATD_8_CONVERSIONS 0x00
#define ATD_1_CONVERSIONS 0x01
#define ATD_2_CONVERSIONS 0x02
#define ATD_3_CONVERSIONS 0x03
#define ATD_4_CONVERSIONS 0x04
#define ATD_5_CONVERSIONS 0x05
#define ATD_6_CONVERSIONS 0x06
#define ATD_7_CONVERSIONS 0x07

#define ATD_NUM_CONVERSIONS(num) FORCE(ATDCTL3, 0x78, ((num) << 3)) 

/* ATD Resolution */

#define ATD_8BIT_RESOLUTION()  SET(ATDCTL4, ATDCTL4_SRES8_MASK)
#define ATD_10BIT_RESOLUTION() CLR(ATDCTL4, ATDCTL4_SRES8_MASK)

/* ATD Sample Time */

#define ATD_2CLK_PER  0x00
#define ATD_4CLK_PER  0x01
#define ATD_8CLK_PER  0x02
#define ATD_16CLK_PER 0x03

#define ATD_SAMPLE_TIME(smp) FORCE(ATDCTL4, 0x60, (((smp) & 0x03) << 5))

/* ATD Prescaler */

#define ATD_SET_PRESCALER(pre) FORCE(ATDCTL4, 0x1F, pre)

/* Starting a conversion */

#define ATD_RIGHT_JUSTIFIED BV(7)
#define ATD_LEFT_JUSTIFIED  0

#define ATD_DATA_SIGNED     BV(6)
#define ATD_DATA_UNSIGNED  0

#define ATD_CONTINUOUS      BV(5)
#define ATD_ONCE            0

#define ATD_MULTI_CHANNEL   BV(4)
#define ATD_SINGLE_CHANNEL  0

#define ATD_START(opt, chnl) FORCE(ATDCTL5, 0xFF, ((opt) | ((chnl) & 0x07)))

#define ATD_EVENT() IS_SET(ATDSTAT0, ATDSTAT0_SCF_MASK)

/* Prototypes */

typedef unsigned char channel_t;

void adc_init(void);

unsigned int analogRead(channel_t chnl);

#endif
























