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

#endif