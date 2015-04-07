
/**
	Pulse Width Modulation Module
	
	@author Natesh Narain
*/

#ifndef PWM
#define PWM

#include "util.h"

/* Channel Masks */

#define PWN_CHNL0_MASK BV(0)
#define PWN_CHNL1_MASK BV(1)
#define PWN_CHNL2_MASK BV(2)
#define PWN_CHNL3_MASK BV(3)
#define PWN_CHNL4_MASK BV(4)
#define PWN_CHNL5_MASK BV(5)
#define PWN_CHNL6_MASK BV(6)
#define PWN_CHNL7_MASK BV(7)

/* Enable \ Disable */

#define PWM_ENABLE(mask)  SET(PWME, (mask))
#define PWM_DISABLE(mask) CLR(PWME, (mask))

/* PWM Clock Prescaler */

#define PWM_PRESCALE_MASK 0x77

#define PWM_PRESCALE_1    0
#define PWM_PRESCALE_2    1
#define PWM_PRESCALE_4    2
#define PWM_PRESCALE_8    3
#define PWM_PRESCALE_16   4
#define PWM_PRESCALE_32   5
#define PWM_PRESCALE_64   6
#define PWM_PRESCALE_128  7

#define PWM_SET_PRESCALE(clka, clkb) ( FORCE( PWMPRCLK, PWM_PRESCALE_MASK, ( (clkb << 4) | clka ) ) )

/* PWM Clock */

#define PWM_SET_CLK_SOURCE(chnl)  CLR(PWMCLK, BV(chnl))
#define PWM_SET_SCLK_SOURCE(chnl) SET(PWMCLK, BV(chnl))

/* PWM Polarity */

#define PWM_POLARITY_HIGH 1
#define PWM_POLARITY_LOW  0

#define PWM_SET_POLARITY(chnl, pol) ( FORCE(PWMPOL, BV(chnl), (pol << chnl)) )

/* PWM Centre Align */

#define PWM_CENTER_ALIGN 1
#define PWM_LEFT_ALIGN   0

#define PWM_SET_ALIGN(chnl, align) ( FORCE(PWMCAE, BV(chnl), (align << chnl)) )

/* PWM Duty */

#define PWM_DTY_CHNL(chnl) EVAL(PWMDTY, chnl)

/* PWM Period */

#define PWM_PER_CHNL(chnl) EVAL(PWMPER, chnl)

#endif













