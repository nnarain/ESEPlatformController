#include "delay.h"

void delay_ms(word ms)
{
	int i;
	
	// set 1 ms into future
	TC0 = TCNT + 125;
	
	// enable TCO for OC
	TIMER_CHNL_MAKE_OC(0);
	
	for(i = ms; i >= 0; --i)
	{
		// wait for timer channel 0 event
		while(!TIMER_CHNL_EVENT(0));
		TC0 += 125;
	}

	// turn off OC on TC0
	CLR_BIT(TIOS, 0);
}